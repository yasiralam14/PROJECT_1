#include "SearchEngine.hpp"

// Function to build histograms from a set of descriptors for each file
void SearchEngine::buildHistograms(const std::vector<cv::Mat>& fileDescriptors,
                                   const cv::Mat& vocabulary) {
    int numFiles = fileDescriptors.size();
    int numWords = vocabulary.rows;
    histograms = cv::Mat::zeros(numFiles, numWords, CV_32S);

    // Create a FLANN index for fast nearest neighbor search
    cv::flann::Index flannIndex(vocabulary, cv::flann::KDTreeIndexParams(4));

    for (int fileIdx = 0; fileIdx < numFiles; ++fileIdx) {
        const cv::Mat& descriptors = fileDescriptors[fileIdx];

        // Find the nearest vocabulary word for each descriptor
        for (int i = 0; i < descriptors.rows; ++i) {
            std::vector<int> indices(1);
            std::vector<float> dists(1);
            flannIndex.knnSearch(descriptors.row(i), indices, dists, 1,
                                 cv::flann::SearchParams(64));

            // Increment the histogram count for the corresponding word
            if (indices[0] < numWords) {
                histograms.at<int>(fileIdx, indices[0])++;
            }
        }
    }

    std::cout << "Histograms built for all files." << std::endl;
}

// Function to normalize histograms using TF-IDF
void SearchEngine::normalize(const cv::Mat& counts) {
    int numFiles = histograms.rows;
    int numWords = histograms.cols;
    normalized_histograms = cv::Mat::zeros(numFiles, numWords, CV_32F);

    float N = counts.at<int>(0, 1);  // Total number of files, same for all rows

    for (int fileIdx = 0; fileIdx < numFiles; ++fileIdx) {
        float nd = static_cast<float>(cv::sum(histograms.row(
                fileIdx))[0]);  // Total word count in the histogram (row)

        for (int wordIdx = 0; wordIdx < numWords; ++wordIdx) {
            int nid = histograms.at<int>(
                    fileIdx, wordIdx);  // Count of word i in histogram d
            int ni = counts.at<int>(wordIdx,
                                    0);  // Number of files containing word i

            if (nid > 0 && ni > 0) {
                float tf = static_cast<float>(nid) / nd;
                float idf = std::log(N / static_cast<float>(ni));
                normalized_histograms.at<float>(fileIdx, wordIdx) = tf * idf;
            }
        }
    }

    std::cout << "Histograms normalized using TF-IDF." << std::endl;
}

// Function to recommend similar images based on descriptors
void SearchEngine::recommend(const std::string& imagePath,
                             const cv::Mat& vocabulary) {
    // Extract SIFT descriptors from the input image
    cv::Ptr<cv::SIFT> sift = cv::SIFT::create();
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cerr << "Error: Could not read the image at " << imagePath
                  << std::endl;
        return;
    }
    std::vector<cv::KeyPoint> keypoints;
    cv::Mat descriptors;
    sift->detectAndCompute(image, cv::noArray(), keypoints, descriptors);

    // Build histogram for the input image
    cv::Mat inputHistogram = cv::Mat::zeros(1, vocabulary.rows, CV_32S);
    cv::flann::Index flannIndex(vocabulary, cv::flann::KDTreeIndexParams(4));

    for (int i = 0; i < descriptors.rows; ++i) {
        std::vector<int> indices(1);
        std::vector<float> dists(1);
        flannIndex.knnSearch(descriptors.row(i), indices, dists, 1,
                             cv::flann::SearchParams(64));

        if (indices[0] < vocabulary.rows) {
            inputHistogram.at<int>(0, indices[0])++;
        }
    }
    const cv::Mat& counts = dict.getCounts();
    // Normalize the input histogram using the counts matrix
    cv::Mat inputNormalized;
    normalizeHistogram(inputHistogram, counts, inputNormalized);

    // Use FLANN to find the 10 closest histograms
    cv::flann::Index normalizedFlannIndex(normalized_histograms,
                                          cv::flann::KDTreeIndexParams(4));
    std::vector<int> nearestIndices(10);
    std::vector<float> distances(10);
    normalizedFlannIndex.knnSearch(inputNormalized, nearestIndices, distances,
                                   10, cv::flann::SearchParams(64));

    // Display the results
    std::cout << "Top 10 closest images:" << std::endl;
    for (int i = 0; i < nearestIndices.size(); ++i) {
        std::cout << "Image " << nearestIndices[i] << " with distance "
                  << distances[i] << std::endl;
    }
}

// Helper function to normalize a single histogram
void SearchEngine::normalizeHistogram(const cv::Mat& histogram,
                                      const cv::Mat& counts,
                                      cv::Mat& normalizedHistogram) {
    normalizedHistogram = cv::Mat::zeros(1, histogram.cols, CV_32F);
    float N = counts.at<int>(0, 1);
    float nd = static_cast<float>(cv::sum(histogram)[0]);

    for (int wordIdx = 0; wordIdx < histogram.cols; ++wordIdx) {
        int nid = histogram.at<int>(0, wordIdx);
        int ni = counts.at<int>(wordIdx, 0);

        if (nid > 0 && ni > 0) {
            float tf = static_cast<float>(nid) / nd;
            float idf = std::log(N / static_cast<float>(ni));
            normalizedHistogram.at<float>(0, wordIdx) = tf * idf;
        }
    }
}

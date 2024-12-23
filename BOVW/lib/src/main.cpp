#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>

// Declare the normalize function
void normalize(const cv::Mat& counts);

cv::Mat histograms;             // Matrix to hold histograms
cv::Mat normalized_histograms;  // Matrix to hold normalized histograms

int main() {
    // Example: Simulating histograms and counts (you can modify these)
    int numFiles = 3;  // Number of files (documents)
    int numWords = 5;  // Number of words (vocabulary size)

    // Create an example counts matrix (rows = vocabulary, columns = 2)
    // Column 0: Count of how many files contain each word
    // Column 1: Total number of files (same for all words)
    cv::Mat counts = cv::Mat::zeros(numWords, 2, CV_32S);
    counts.at<int>(0, 0) = 2;       // Word 0 appears in 2 files
    counts.at<int>(1, 0) = 1;       // Word 1 appears in 1 file
    counts.at<int>(2, 0) = 3;       // Word 2 appears in 3 files
    counts.at<int>(3, 0) = 1;       // Word 3 appears in 1 file
    counts.at<int>(4, 0) = 2;       // Word 4 appears in 2 files
    counts.col(1).setTo(numFiles);  // Set total files (N) for all words

    // Create a sample histograms matrix (rows = files, cols = vocabulary size)
    histograms = cv::Mat::zeros(numFiles, numWords, CV_32S);
    histograms.at<int>(0, 0) = 1;  // File 0 has word 0
    histograms.at<int>(0, 1) = 2;  // File 0 has word 1
    histograms.at<int>(1, 2) = 1;  // File 1 has word 2
    histograms.at<int>(1, 3) = 1;  // File 1 has word 3
    histograms.at<int>(2, 4) = 3;  // File 2 has word 4

    std::cout << "Original histograms:" << std::endl;
    std::cout << histograms << std::endl;

    // Normalize the histograms using the provided normalize function
    normalize(counts);

    // Output the normalized histograms
    std::cout << "Normalized histograms (TF-IDF):" << std::endl;
    std::cout << normalized_histograms << std::endl;

    return 0;
}

// The normalize function as defined
void normalize(const cv::Mat& counts) {
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

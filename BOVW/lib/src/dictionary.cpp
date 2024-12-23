#include "dictionary.hpp"

// Public method to access the singleton instance
Dictionary& Dictionary::getInstance() {
    static Dictionary instance;  // Guaranteed to be destroyed and
                                 // instantiated on first use
    return instance;
}

// Getter for the counts matrix
cv::Mat Dictionary::getCounts() const { return counts; }

// Build vocabulary using FLANN-based k-means clustering
void Dictionary::buildVocabulary(const std::vector<cv::Mat>& descriptors,
                                 int clusterCount) {
    // Step 1: Flatten all descriptors into a single matrix
    cv::Mat allDescriptors;
    for (const auto& descriptor : descriptors) {
        allDescriptors.push_back(descriptor);
    }

    // Step 2: Use k-means to find cluster centers (vocabulary)
    cv::Mat labels;
    cv::kmeans(
            allDescriptors, clusterCount, labels,
            cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER,
                             100, 0.2),
            3, cv::KMEANS_PP_CENTERS, vocabulary);

    std::cout << "Vocabulary built with " << vocabulary.rows << " words."
              << std::endl;

    // Step 3: Optionally, you can use FLANN index for fast nearest-neighbor
    // search
    cv::flann::Index flannIndex(vocabulary, cv::flann::KDTreeIndexParams(4));

    // We now have the vocabulary and the FLANN index set up.
}
// Fill the counts matrix based on descriptors using FLANN for nearest
// neighbor search
void Dictionary::fillCounts(const std::vector<cv::Mat>& descriptors) {
    // Initialize counts matrix with two columns:
    // First column: number of files containing each word
    // Second column: initialized to 100 for all rows
    int length = descriptors.size();
    counts = cv::Mat::zeros(vocabulary.rows, 2, CV_32S);

    // Build the FLANN index for the vocabulary
    cv::flann::Index flannIndex(vocabulary, cv::flann::KDTreeIndexParams(4));

    // Iterate over each descriptor set (one per file)
    for (const auto& descriptor : descriptors) {
        // Create a set to track unique vocabulary indices matched by this
        // file
        std::set<int> uniqueIndices;

        // Iterate over each descriptor in the current file
        for (int i = 0; i < descriptor.rows; ++i) {
            std::vector<int> indices(1);
            std::vector<float> dists(1);

            // Use FLANN to find the nearest vocabulary word
            flannIndex.knnSearch(descriptor.row(i), indices, dists, 1,
                                 cv::flann::SearchParams(64));

            // Add the index to the set if the distance is below the
            // threshold
            if (dists[0] < threshold) {
                uniqueIndices.insert(indices[0]);
            }
        }

        // Increment the count for each unique vocabulary word matched by
        // this file
        for (int index : uniqueIndices) {
            counts.at<int>(index, 0)++;
        }
    }

    // Fill the second column with a constant value of 100

    // Fill the second column with a constant value (100) for all rows
    counts.col(1).setTo(length);
    std::cout << "Counts filled for the descriptors." << std::endl;
}

cv::Mat& Dictionary::getVocabulary() { return vocabulary; }

// int main() {
//     // Example usage of the Singleton Dictionary class
//     Dictionary& dict = Dictionary::getInstance();

//     // Example descriptors (replace with actual data)
//     std::vector<cv::Mat> descriptors;
//     cv::Mat descriptor1 =
//             (cv::Mat_<float>(1, 128) << 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
//             0.8,
//              0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1,
//              0.2, 0.3, 0.4, 0.5, 0, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4,
//              0.5, 0.6, 0, 0.8, 0, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
//              0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
//              0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3,
//              0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0,
//              0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0, 0.8,
//              0, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1,
//              0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0);
//     cv::Mat descriptor2 =
//             (cv::Mat_<float>(1, 128) << 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
//             0.8,
//              0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1,
//              0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4,
//              0.5, 0.6, 0.7, 0.8, 0, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
//              0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8,
//              0.9, 1.0);
//     cv::Mat descriptor3 =
//             (cv::Mat_<float>(1, 128) << 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
//             0.8,
//              0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1,
//              0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4,
//              0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
//              0.8, 0.9, 1.0, 0.1, 0, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0);
//     cv::Mat descriptor4 =
//             (cv::Mat_<float>(1, 128) << 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
//             0.8,
//              0.9, 1.0, 0, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1,
//              0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4,
//              0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
//              0.8, 0.9, 1.0, 0.1, 0, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0);
//     cv::Mat descriptor5 =
//             (cv::Mat_<float>(1, 128) << 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
//             0.8,
//              0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1,
//              0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4,
//              0.5, 0, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
//              0.8, 0.9, 1.0, 0.1, 0, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0);
//     cv::Mat descriptor6 =
//             (cv::Mat_<float>(1, 128) << 0.1, 0, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8,
//              0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1,
//              0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4,
//              0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
//              0.8, 0.9, 1.0, 0.1, 0, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0);
//     cv::Mat descriptor7 =
//             (cv::Mat_<float>(1, 128) << 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
//             0.8,
//              0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1,
//              0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4,
//              0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0, 0.6, 0.7,
//              0.8, 0.9, 1.0, 0.1, 0, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0);
//     cv::Mat descriptor8 =
//             (cv::Mat_<float>(1, 128) << 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
//             0.8,
//              0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1,
//              0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4,
//              0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
//              0.8, 0.9, 1.0, 0.1, 0, 0.3, 0.4, 0.5, 0.6, 0, 0.8, 0.9, 1.0);
//     cv::Mat descriptor9 =
//             (cv::Mat_<float>(1, 128) << 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
//             0.8,
//              0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1,
//              0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4,
//              0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
//              0, 0.9, 1.0, 0.1, 0, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0);
//     cv::Mat descriptor10 =
//             (cv::Mat_<float>(1, 128) << 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
//             0.8,
//              0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1,
//              0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4,
//              0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
//              0, 0.9, 1.0, 0.1, 0, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0);
//     cv::Mat descriptor11 =
//             (cv::Mat_<float>(1, 128) << 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
//             0.8,
//              0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1,
//              0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4,
//              0.5, 0, 0.7, 0.8, 0.9, 1.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
//              0.8, 0.9, 1.0, 0.1, 0, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0);
//     descriptors.push_back(descriptor1);
//     descriptors.push_back(descriptor2);
//     descriptors.push_back(descriptor3);
//     descriptors.push_back(descriptor4);
//     descriptors.push_back(descriptor5);
//     descriptors.push_back(descriptor6);
//     descriptors.push_back(descriptor7);
//     descriptors.push_back(descriptor8);
//     descriptors.push_back(descriptor9);
//     descriptors.push_back(descriptor10);
//     descriptors.push_back(descriptor11);

//     cv::Mat before_built = dict.getVocabulary();
//     // Build vocabulary using the descriptors
//     dict.buildVocabulary(descriptors, 5);
//     cv::Mat after_built = dict.getVocabulary();
//     // Fill counts for the descriptors
//     dict.fillCounts(descriptors);

//     // Print counts matrix
//     std::cout << "Counts: " << std::endl;
//     std::cout << dict.getCounts() << std::endl;
//     std::cout << "before build: " << std::endl;
//     std::cout << before_built.size() << std::endl;
//     std::cout << "after build: " << std::endl;
//     std::cout << after_built.size() << std::endl;

//     return 0;
// }

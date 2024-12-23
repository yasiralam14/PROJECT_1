#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <mutex>
#include <opencv2/flann.hpp>
#include <opencv2/opencv.hpp>
#include <set>
#include <vector>

class Dictionary {
public:
    // Public method to access the singleton instance
    static Dictionary& getInstance();

    // Getter for the counts matrix
    cv::Mat getCounts() const;

    // Build vocabulary using FLANN-based k-means clustering
    void buildVocabulary(const std::vector<cv::Mat>& descriptors,
                         int clusterCount);

    // Fill the counts matrix based on descriptors using FLANN for nearest
    // neighbor search
    void fillCounts(const std::vector<cv::Mat>& descriptors);

    // Getter for the vocabulary matrix
    cv::Mat& getVocabulary();

private:
    // Private constructor and destructor to prevent multiple instances
    Dictionary();

    // Delete copy constructor and assignment operator to enforce Singleton
    Dictionary(const Dictionary&) = delete;
    Dictionary& operator=(const Dictionary&) = delete;

    // Private member variables
    cv::Mat vocabulary;  // Vocabulary (descriptor centers)
    cv::Mat counts;    // Counts of how many times each vocabulary word is used
    double threshold;  // Threshold for counting, adjustable
};

#endif  // DICTIONARY_H

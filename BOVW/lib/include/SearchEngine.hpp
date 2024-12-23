#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <cmath>
#include <iostream>
#include <opencv2/flann.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <string>
#include <vector>

#include "dictionary.hpp"

class SearchEngine {
public:
    cv::Mat histograms;             // Histograms for all files
    cv::Mat normalized_histograms;  // Normalized histograms (TF-IDF)

    // Function to build histograms from descriptors for each file
    void buildHistograms(const std::vector<cv::Mat>& fileDescriptors,
                         const cv::Mat& vocabulary);

    // Function to normalize histograms using TF-IDF
    void normalize(const cv::Mat& counts);

    // Function to recommend similar images based on SIFT descriptors
    void recommend(const std::string& imagePath, const cv::Mat& vocabulary);

private:
    // Helper function to normalize a single histogram
    void normalizeHistogram(const cv::Mat& histogram,
                            const cv::Mat& counts,
                            cv::Mat& normalizedHistogram);
    Dictionary& dict = Dictionary::getInstance();
};

#endif  // SEARCHENGINE_H

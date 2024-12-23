#include <filesystem>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

namespace fs = std::filesystem;

std::vector<cv::Mat> loadDataset(const std::string& binDir) {
    // Check if the bin directory exists
    if (!fs::exists(binDir)) {
        std::cerr << "Directory does not exist: " << binDir << std::endl;
        return cv::Mat();  // Return an empty matrix if the directory doesn't
                           // exist
    }

    // Initialize a vector to hold all descriptors
    std::vector<cv::Mat> descriptorsList;

    // Iterate over all files in the bin directory
    for (const auto& entry : fs::directory_iterator(binDir)) {
        // Process only .bin files
        if (entry.is_regular_file() && entry.path().extension() == ".bin") {
            std::string binFilePath = entry.path().string();

            // Open the binary file
            std::ifstream binFile(binFilePath, std::ios::binary);
            if (!binFile.is_open()) {
                std::cerr << "Error opening binary file: " << binFilePath
                          << std::endl;
                continue;
            }

            // Read the size of the descriptors matrix (rows and columns)
            int rows, cols;
            binFile.read(reinterpret_cast<char*>(&rows), sizeof(int));
            binFile.read(reinterpret_cast<char*>(&cols), sizeof(int));

            // Create a matrix to hold the descriptors
            cv::Mat descriptors(rows, cols, CV_32F);

            // Read the descriptor data
            binFile.read(reinterpret_cast<char*>(descriptors.data),
                         descriptors.total() * descriptors.elemSize());

            binFile.close();

            // Add the descriptors to the list
            descriptorsList.push_back(descriptors);
        }
    }

    // Stack all the descriptors into one cv::Mat

    return descriptorsList;
}

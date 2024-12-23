#include <filesystem>
#include <fstream>
#include <iostream>
#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

namespace fs = std::filesystem;

void convertDataset(const std::string& folderPath) {
    // Check if the folder exists
    if (!fs::exists(folderPath)) {
        std::cerr << "Directory does not exist: " << folderPath << std::endl;
        return;
    }

    // Create the bin directory if it doesn't exist
    std::string binDir = folderPath + "/bin";
    if (!fs::exists(binDir)) {
        fs::create_directory(binDir);
    }

    // Initialize SIFT detector
    cv::Ptr<cv::SIFT> sift = cv::SIFT::create();

    // Iterate over all files in the folder
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        // Process only image files
        if (entry.is_regular_file() && (entry.path().extension() == ".jpg" ||
                                        entry.path().extension() == ".png")) {
            std::string imagePath = entry.path().string();

            // Load the image
            cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
            if (image.empty()) {
                std::cerr << "Error reading image: " << imagePath << std::endl;
                continue;
            }

            // Detect keypoints and compute descriptors
            std::vector<cv::KeyPoint> keypoints;
            cv::Mat descriptors;
            sift->detectAndCompute(image, cv::noArray(), keypoints,
                                   descriptors);

            // Generate the binary file path
            std::string binFilePath =
                    binDir + "/" + entry.path().stem().string() + ".bin";

            // Save the descriptors as a binary file
            std::ofstream binFile(binFilePath, std::ios::binary);
            if (binFile.is_open()) {
                int rows = descriptors.rows;
                int cols = descriptors.cols;

                // Write the descriptor matrix size
                binFile.write(reinterpret_cast<char*>(&rows), sizeof(int));
                binFile.write(reinterpret_cast<char*>(&cols), sizeof(int));

                // Write the descriptors
                binFile.write(reinterpret_cast<char*>(descriptors.data),
                              descriptors.total() * descriptors.elemSize());

                binFile.close();
                std::cout << "Saved descriptors for " << imagePath << " to "
                          << binFilePath << std::endl;
            } else {
                std::cerr << "Error opening binary file for writing: "
                          << binFilePath << std::endl;
            }
        }
    }
}

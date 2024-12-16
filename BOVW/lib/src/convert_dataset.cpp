#include <filesystem>
#include <fstream>
#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <string>

#include "iostream"
#include "serialize.hpp"

namespace ipb::serialization::sifts {
void ConvertDataset(const std::filesystem::path& img_path) {
    if (!std::filesystem::exists(img_path)) {
        std::cerr << "Error: The directory does not exist: " << img_path
                  << std::endl;
        return;
    }

    if (!std::filesystem::is_directory(img_path)) {
        std::cerr << "Error: The path is not a directory: " << img_path
                  << std::endl;
        return;
    }

    // Check if the directory is empty
    if (std::filesystem::is_empty(img_path)) {
        std::cerr << "Error: The directory is empty: " << img_path << std::endl;
        return;
    }
    cv::Ptr<cv::SIFT> sift = cv::SIFT::create();
    for (const auto& entry : std::filesystem::directory_iterator(img_path)) {
        std::string file_name = (entry.path().parent_path().parent_path() /
                                 "bin" / entry.path().stem())
                                        .string() +
                                ".bin";

        std::filesystem::path file_path = file_name;
        // Create parent directories
        std::filesystem::create_directories(file_path.parent_path());

        cv::Mat img = cv::imread(entry.path(), cv::IMREAD_GRAYSCALE);
        if (img.empty()) {
            std::cerr << "Error: Could not read image: " << entry.path()
                      << std::endl;
            continue;
        }

        std::vector<cv::KeyPoint> keypoints;
        sift->detect(img, keypoints);
        cv::Mat descriptors;
        sift->compute(img, keypoints, descriptors);
        ipb::serialization::Serialize(descriptors, file_name);
    }
}
std::vector<cv::Mat> LoadDataset(const std::filesystem::path& bin_path) {
    std::vector<cv::Mat> mContainer;
    for (const auto& entry : std::filesystem::directory_iterator(bin_path)) {
        std::string file_path = entry.path().string();
        cv::Mat m = ipb::serialization::Deserialize(file_path);
        mContainer.push_back(m);
    }

    return mContainer;
}
}  // namespace ipb::serialization::sifts

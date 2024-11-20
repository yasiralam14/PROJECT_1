#include <filesystem>
#include <fstream>
#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <string>

#include "iostream"
#include "serialize.hpp"

namespace ipb::sterelization::sifts {
void ConvertDataset(const std::filesystem::path& img_path) {
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
}  // namespace ipb::sterelization::sifts

#include <iostream>
#include <opencv2/imgcodecs.hpp>

#include "serialize.hpp"

int main() {
    cv::Mat image = cv::imread("./../data/lenna.png", cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cerr << "Error: Could not load image." << std::endl;
        return 1;
    }

    ipb::serialization::Serialize(image, "./../data/lenna.bin");

    cv::Mat deserializedImage =
            ipb::serialization::Deserialize("./../data/lenna.bin");
    if (deserializedImage.empty()) {
        std::cerr << "Error: Could not deserialize image." << std::endl;
        return 1;
    }

    cv::imwrite("./../data/de_ser_lenna.png", deserializedImage);

    return 0;
}
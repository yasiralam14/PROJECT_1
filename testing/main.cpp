
#include <iostream>
#include <opencv2/opencv.hpp>
int main() {
    cv::Mat image = cv::imread("lenna.png", cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cerr << "image is not read properly" << std::endl;
        return 1;
    }
    std::cout << image << std::endl;
    return 0;
}

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
namespace ipb {

cv::Mat kMeans(const std::vector<cv::Mat> &descriptors, int k, int max_iter);

}
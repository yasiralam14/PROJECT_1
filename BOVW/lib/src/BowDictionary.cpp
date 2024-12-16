#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int ipb::BowDictionary::size() const { return vocab_size_; }
const std::vector<cv::Mat>& ipb::BowDictionary::descriptors() const {
    return input_data_;
}
const cv::Mat& ipd::BowDictionary::vocabulary() const { return dictionary_; }

bool ipb::BowDictionary::empty() const { return dictionary_.empty(); }

void ipb::BowDictionary::build(int max_iterations,
                               int vocab_size,
                               const std::vector<cv::Mat>& descriptors) {
    max_iterations_ = max_iterations;
    vocab_size_ = vocab_size;
    input_data_ = descriptors;
    dictionary_ = ipb::kMeans(descriptors, vocab_size, max_iterations);
}

static ipb::BowDictionary& ipb::BowDictionary::Instance() {
    static BowDictionary instance;  // Guaranteed to be created only once
    return instance;
}

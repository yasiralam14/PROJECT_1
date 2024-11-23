#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int ipb::BowDictionary::max_iterations() const { return max_iterations_; }
int ipb::BowDictionary::size() const { return vocab_size_; }
const std::vector<cv::Mat>& ipb::BowDictionary::descriptors() const {
    return input_data_;
}
const cv::Mat& ipd::BowDictionary::vocabulary() const { return dictionary_; }
int ipb::BowDictionary::total_features() const {
    int total_k = 0;
    if (!input_data_.empty()) {
        for (const auto& mat : input_data_) {
            total_k += mat.rows;
        }
    }
    return total_k;
}

bool ipb::BowDictionary::empty() const { return dictionary_.empty(); }

void ipb::BowDictionary::set_max_iterations(int iterations) {
    if (iterations < 1) {
        std::cout << "Input a valid number" << std::endl;
        return;
    }
    if (iterations < max_iterations_) {
        std::cout << "more than these iterations have taken place"
    } else {
        set_params(iterations, vocab_size_, input_data_);
    }
}
void ipb::BowDictionary::set_size(int size) {
    if (size < 1) {
        std::cout << "Input a valid number" << std::endl;
        return;
    }
    set_params(max_iterations_, size, input_data);
}
void ipb::BowDictionary::set_descriptors(
        const std::vector<cv::Mat>& descriptors) {
    if (descriptors.empty()) {
        std::cout << "Input Valid Data" << std::endl;
        return;
    }
    set_params(max_iterations_, vocab_size_, descriptors)
}

void ipb::BowDictionary::set_params(int max_iterations,
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

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

namespace ipb {

class BowDictionary {
private:
    BowDictionary();
    ~BowDictionary();
    int max_iterations_;
    int vocab_size_;
    std::vector<cv::Mat> input_data_;
    cv::Mat dictionary_;

    // Getters
public:
    BowDictionary(const BowDictionary&) = delete;
    BowDictionary& operator=(const BowDictionary&) = delete;
    static BowDictionary& Instance();
    {
        static BowDictionary instance;  // Guaranteed to be created only once
        return instance;
    }
    int max_iterations() const;
    int size() const;
    const std::vector<cv::Mat>& descriptors() const;
    const cv::Mat& vocabulary() const;
    int total_features() const;
    bool empty() const;
    // Setters
    void set_max_iterations(int iterations);
    void set_size(int size);
    void set_descriptors(const std::vector<cv::Mat>& descriptors);

    void set_params(int max_iterations,
                    int vocab_size,
                    const std::vector<cv::Mat>& descriptors);
};
}  // namespace ipb
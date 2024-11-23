#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

namespace ipb {

class BowDictionary {
private:
    BowDictionary();
    ~BowDictionary();
    int vocab_size_;
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
    int size() const;
    const cv::Mat& vocabulary() const;
    bool empty() const;
    // Setters
    void set_descriptors(const std::vector<cv::Mat>& descriptors);

    void build(int max_iterations,
               int vocab_size,
               const std::vector<cv::Mat>& descriptors);
};
}  // namespace ipb
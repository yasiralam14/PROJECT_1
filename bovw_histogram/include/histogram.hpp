#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace ipb {

class Histogram {
private:
    std::vector<int> data_;

public:
    Histogram();
    Histogram(std::vector<int> data);
    Histogram(cv::Mat descriptors, cv::Mat dictionary);
    fstream& operator<<();
    void WriteToCSV(std::string& file_name) const;
    std::vector<int> ReadFromCSV();
    // Imitate stl_vector functionality
    int operator[]() const;
    std::vector<int>& data() const;
    int size();
    bool empty();
    int begin() const;
    int cbegin() const;
    int end() const;
    int cend() const;
    friend std::ostream& operator<<(std::ostream& os, const ipb::Histogram& h);
    // data members:
};

}  // namespace ipb
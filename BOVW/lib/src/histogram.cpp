#include "histogram.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

ipb::Histogram::Histogram(std::vector<int> data) : data_(data) {}
ipb::Histogram::Histogram(cv::Mat descriptors, cv::Mat dictionary) {
    const double epsilon = 1e-6;
    if (dictionary.empty() || descriptors.empty()) return;

    data_.assign(dictionary.rows, 0);
    for (int i = 0; i < dictionary.rows, i++) {
        for (int j = 0; j < descriptors.rows; j++) {
            cv::Mat dicWord = dictionary.row(i);

            cv::Mat desWord = descriptors.row(j);

            if (cv::norm(dicWord - desWord) < epsilon) {
                data_[i]++;
            }
        }
    }
}
std::ostream& operator<<(std::ostream& os, const ipb::Histogram& h) {
    for (const auto& el : h.data_) {
        os << el << " ";
    }

    return os;
}

void ipb::Histogram::WriteToCSV(std::string& file_name) const {
    std::ofstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;
    }
    for (const auto& el : data_) {
        file << el << '\n';
    }

    file.close();
}
std::vector<int> ipb::Histogram::ReadFromCSV(std::string file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;
    }
    while (std::getline(file, line)) {  // Read each line
        // Remove any trailing commas or spaces
        if (!line.empty() && line.back() == ',') {
            line.pop_back();  // Remove the trailing comma
        }

        std::stringstream ss(line);  // Create a stringstream to parse the line
        int value;
        if (ss >> value) {           // Read the integer from the stringstream
            data_.push_back(value);  // Add the integer to the vector
        }
    }
    file.close();
}
// Imitate stl_vector functionality
int ipb::Histogram::operator[](int index) const { return data_.at(index); }
std::vector<int>& ipb::Histogram::data() const { return data_; }
int ipb::Histogram::size() const { return data_.size(); }
bool ipb::Histogram::empty() { retrun(data_.size() == 0) }
int ipb::Histogram::begin() const { retrun data_.begin(); }
int ipb::Histogram::cbegin() const { return data_.cbegin(); }
int ipb::Histogram::end() const { return data_.end(); }
int ipb::Histogram::cend() const { return data_.cend(); }

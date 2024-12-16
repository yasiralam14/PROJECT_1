#include "serialize.hpp"

#include <fstream>
#include <opencv2/opencv.hpp>
#include <string>

#include "iostream"

namespace ipb::serialization {

void Serialize(const cv::Mat& m, const std::string& filename) {
    cv::Size matSize = m.size();
    int rows = m.rows;
    int cols = m.cols;
    int type = m.type();  // Include the type of matrix to deserialize correctly
    // Open the file in binary mode
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file for writing." << std::endl;
        return;
    }

    // Write the matrix size (rows, cols, channels) and type
    file.write(reinterpret_cast<const char*>(&rows), sizeof(int));
    file.write(reinterpret_cast<const char*>(&cols), sizeof(int));
    file.write(reinterpret_cast<const char*>(&type), sizeof(int));
    // Write the matrix data (ensure you correctly handle the element size)
    file.write(reinterpret_cast<const char*>(m.data), m.total() * m.elemSize());

    file.close();  // Explicitly close the file
}

cv::Mat Deserialize(const std::string& filename) {
    cv::Mat m;
    int rows;
    int cols;
    int channels;
    int type;
    std::ifstream file(filename, std::ios::binary);
    if (file) {
        file.read(reinterpret_cast<char*>(&rows), sizeof(int));
        file.read(reinterpret_cast<char*>(&cols), sizeof(int));
        file.read(reinterpret_cast<char*>(&type), sizeof(int));
        m.create(rows, cols, type);
        file.read(reinterpret_cast<char*>(m.data), m.total() * m.elemSize());
    } else {
        std::cerr << "no file found" << std::endl;
    }
    return m;
}
}  // namespace ipb::serialization
#include <cmath>
#include <iostream>
#include <vector>

template <typename T>
using vec = std::vector<T>;

class Image {
private:
    int rows_;
    int cols_;
    vec<uint8_t> data_;

public:
    Image() = default;
    Image(int rows, int cols) : rows_(rows), cols_(cols) {}
    Image(const Image&) = default;

    // Copy assignment operator
    Image& operator=(const Image&) = default;

    // Move constructor
    Image(Image&&) = default;

    // Move assignment operator
    Image& operator=(Image&&) = default;

    // Destructor
    ~Image() = default;

    const int& rows() const { return rows_; }
    const int& columns() const { return cols_; }
    uint8_t& at(int rows, int cols) {
        if (rows < 1 || rows > rows_ || cols < 1 || cols > cols_) {
            std::cerr << "IndexOutOfBoundError" << std::endl;
            // Optionally throw an exception or return a sentinel value
            throw std::out_of_range("Index out of bounds");
        }
        int index = ((rows - 1) * cols_) +
                    (cols - 1);  // Correct 2D to 1D conversion
        return data_[index];
    }

    bool FillFromPgm(const std::string& file_name) {
        igg::io_tools::ImageData imageData = ReadFromPgm(file_name);
        rows_ = imageData.rows;
        cols_ = imageData.cols;
        data_ = imageData.data;
        if (data_.size() == 0) {
            return false;
        }
        return true;
    }

    void WriteToPgm(const std::string& file_name) {
        igg::io_tools::ImageData image_data = {rows_, cols_, data_};
        WriteToPgm(image_data, file_name);
    }

    std::vector<float> ComputeHistogram(int bins) const {
        std::vector<float> histogram(bins, 0);
        int max_value = 255;

        for (auto& pixel : data_) {
            int bin_index = std::floor(pixel / (float)(max_value + 1) * bins);
            histogram[bin_index]++;
        }
        int total_count = 0;
        for (int count : histogram) {
            total_count += count;
        }
        for (int i = 0; i < histogram.size(); ++i) {
            histogram[i] = histogram[i] / (static_cast<float>(total_count));
        }

        return histogram;
    }

    void DownScale(int scale) {
        // Calculate new dimensions
        int downSizedRows = std::floor(rows_ / scale);
        int downSizedCols = std::floor(cols_ / scale);

        // Initialize downsized data
        vec<uint8_t> downsized_data;

        // Iterate over the downsized image pixels
        for (int i = 0; i < downSizedRows; ++i) {
            for (int j = 0; j < downSizedCols; ++j) {
                // Map downsized pixel to original pixel
                downsized_data.push_back(this->at(i * scale, j * scale));
            }
        }

        // Update the image with downsized data
        rows_ = downSizedRows;
        cols_ = downSizedCols;
        data_ = std::move(downsized_data);
    }
};
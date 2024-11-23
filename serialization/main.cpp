#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <string>

#include "convert_dataset.hpp"
#include "serialize.hpp"

int main() {
    std::string img_path = "../data/freiburg/images/";
    ipb::serialization::sifts::ConvertDataset(img_path);

    return 0;
}
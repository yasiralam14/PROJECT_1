#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

void showHTML(const std::vector<std::string>& imagePaths) {
    // Start the HTML structure
    std::cout << "<html>\n";
    std::cout << "<head>\n";
    std::cout << "<title>Image Gallery</title>\n";
    std::cout << "</head>\n";
    std::cout << "<body>\n";
    std::cout << "<h1>Image Gallery</h1>\n";

    // Iterate through each image path and create an <img> tag for it
    for (const auto& imagePath : imagePaths) {
        std::cout << "<div style='margin: 10px; display: inline-block;'>\n";
        std::cout << "<img src='" << imagePath
                  << "' alt='Image' style='width: 300px; height: auto;'>\n";
        std::cout << "</div>\n";
    }

    // End the HTML structure
    std::cout << "</body>\n";
    std::cout << "</html>\n";
}
std::vector<std::string> getAllFilePaths(const std::string& dirPath) {
    std::vector<std::string> filePaths;

    // Check if the directory exists
    if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
        std::cerr << "Directory does not exist or is not a directory: "
                  << dirPath << std::endl;
        return filePaths;
    }

    // Iterate through the directory
    for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {
        // If the entry is a regular file, add it to the vector
        if (fs::is_regular_file(entry)) {
            filePaths.push_back(entry.path().string());
        }
    }

    return filePaths;
}

int main() {
    // Example image paths (replace these with actual file paths)
    std::vector<std::string> imagePaths = getAllFilePaths("../data/images");

    // Call the showHTML function to generate and print the HTML
    showHTML(imagePaths);

    return 0;
}

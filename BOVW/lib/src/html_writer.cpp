#include <filesystem>
#include <iomanip>
#include <iostream>
#include <istream>
#include <string>

#include "./api/html_writer.hpp"

namespace html_writer {

void OpenDocument() {
    using std::cout;
    using std::endl;
    cout << "<!DOCTYPE html>" << endl;
    cout << "<html>" << endl;
}

void CloseDocument() {
    using std::cout;
    using std::endl;
    cout << "</html>" << endl;
}

void AddCSSStyle(const std::string& stylesheet) {
    using std::cout;
    using std::endl;
    cout << "<link rel =\"stylesheet\" type = \"text/css\" href=" << "\""
         << stylesheet << "\" />" << endl;
}

void OpenHead() { std::cout << "<head>" << std::endl; }
void CloseHead() { std::cout << "</head>" << std::endl; }
void AddTitle(const std::string& title) {
    std::cout << "<title>" << title << "</title>" << std::endl;
}
void OpenBody() { std::cout << "<body>" << std::endl; }
void CloseBody() { std::cout << "</body>" << std::endl; }
void OpenRow() { std::cout << "<div class = \"row\" >" << std::endl; }
void CloseRow() { std::cout << "</div>" << std::endl; }
void AddImage(const std::string& img_path, float score, bool highlight) {
    using std::cout;
    using std::endl;
    std::filesystem::path filepathobject(img_path);
    std::string img_name = filepathobject.filename();
    std::string img_ext = filepathobject.extension();

    if (img_ext != ".png" && img_ext != ".jpg") {
        throw std::invalid_argument("You can only add .png or .jpg images.");
    }
    if (highlight) {
        cout << "<div class=\"column\" style=\"border: 5px solid green;\">"
             << endl;
        cout << "<h2>" << img_name << "</h2>" << endl;
        cout << "<img src=" << img_path << " />" << endl;
        cout << std::setprecision(2) << std::fixed << "<p>score = " << score
             << "</p>" << endl;
        cout << "</div>" << endl;
    } else {
        cout << "<div class=\"column\">" << endl;
        cout << "<h2>" << img_name << "</h2>" << endl;
        cout << "<img src=" << img_path << " />" << endl;
        cout << "<p>score =" << score << "</p>" << endl;
        cout << "</div>" << endl;
    }
}

}  // namespace html_writer
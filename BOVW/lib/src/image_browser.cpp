#include <filesystem>
#include <iomanip>
#include <iostream>
#include <istream>
#include <string>

#include "./api/html_writer.hpp"
#include "./api/image_browser.hpp"

namespace image_browser {

void AddFullRow(const ImageRow& row, bool first_row) {
    html_writer::OpenRow();
    for (int i = 0; i < row.size(); i++) {
        const auto& [imagepath, score] = row[i];
        bool highlight = (i == 0 && first_row);
        html_writer::AddImage(imagepath, score, highlight);
    }

    html_writer::CloseRow();
}

void CreateImageBrowser(const std::string& title,
                        const std::string& stylesheet,
                        const std::vector<ImageRow>& rows) {
    html_writer::OpenDocument();
    html_writer::AddCSSStyle(stylesheet);
    html_writer::AddTitle(title);
    html_writer::OpenBody();
    for (int i = 0; i < rows.size(); i++) {
        AddFullRow(rows[i]);
    }
    html_writer::CloseBody();
    html_writer::CloseDocument();
}

}  // namespace image_browser
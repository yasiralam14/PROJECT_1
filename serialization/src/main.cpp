#include <fstream>
#include <iostream>
#include <string>
using std::cout;
using std::endl;

int main() {
    cout << "hello program" << endl;
    std::ofstream file("testfile.bin", std::ios::binary);
    if (file) {
        cv::Size matSize = mat.size();
        rows = matSize.height;
        columns = matSize.width;

        file.write(reinterpret_cast<const char*>(data.data()),
                   data.size() * sizeof(float))
    }

    return 0;
}
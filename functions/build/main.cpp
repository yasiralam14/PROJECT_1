#include <iostream>
#include <variant>

int main() {
    std::variant<int, float> v1;
    v1 = 12;  // v1 contains int
    std::cout << std::get<int>(v1) << std::endl;

    std::variant<int, float> v2{3.14F};
    std::cout << std::get<float>(v2) << std::endl;

    v2 = std::get<int>(v1);  // assigns v1's int value to v2

    // Alternatively, using index-based access
    v2 = std::get<0>(v1);  // same as previous line, accessing int by index

    std::cout << std::get<int>(v2) << std::endl;

    return 0;
}

#include <cstdlib>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

// executable should be named task_1
// have a look at what random device is in c++
// have a look at what cin.fail() is in c++
// right the code that takes in a number from you it already has a guess with it
// and compare your number with its guess and then gives you three outputs the
// standard ones you can guess. the main thing is the cin should flow until the
// guess has been made

int main() {
    std::string input;
    std::getline(std::cin, input);
    std::cout << input << std::endl;

    std::istringstream iss(input);
    std::vector<std::string> args;
    std::string arg;

    while (iss >> arg) {
        args.push_back(arg);
    }

    if (args.size() != 2) {
    std:
        std::cerr << "You did not give the right amount of arguments";
        EXIT_FAILURE;
    }
    std::string ext1;
    std::string ext2;
    int file_name1;
    int file_name2;

    std::size_t dot_pos_1 = args[0].find_last_of('.');
    if (dot_pos_1 != std::string::npos) {
        ext1 = args[0].substr(dot_pos_1 + 1);
        file_name1 = std::stoi(args[0].substr(0, dot_pos_1));
    } else {
        std::cout << "Wrong Input" << std::endl;
        EXIT_FAILURE;
    }
    std::size_t dot_pos_2 = args[1].find_last_of('.');
    if (dot_pos_2 != std::string::npos) {
        ext2 = args[1].substr(dot_pos_2 + 1);
        file_name2 = std::stoi(args[1].substr(0, dot_pos_2));
    } else {
        std::cout << "Wrong Input" << std::endl;
        EXIT_FAILURE;
    }

    if (ext1 == "txt" && ext2 == "txt") {
        std::cout << (file_name1 + file_name2) / 2 << std::endl;
    } else if (ext1 == "png" && ext2 == "png") {
        std::cout << file_name1 + file_name2 << std::endl;
    } else if (ext1 == "txt" && ext2 == "png") {
        std::cout << file_name1 % file_name2 << std::endl;
    } else {
        std::cerr << "Wrong input format" << std::endl;
        EXIT_FAILURE;
    }

    EXIT_SUCCESS;
}

#include <iostream>
#include <random>
#include <cstdlib> 


int main() {
    std::random_device random_device;
    std::mt19937 gen(random_device());
    std::uniform_int_distribution<> dist(1, 99);

    int guess = dist(gen);
    std::cout << "Please enter an integer " << std::endl;
    int inputnumber;  
    std::cin >> inputnumber;

    do {
        
        
        if (std::cin.fail()){
            std::cerr << "“Error encountered, exiting..." << std::endl;
            std::cin.clear();
            std::cin.ignore();
            return EXIT_FAILURE;
        }
        if (inputnumber > 99 || inputnumber < 0 ){
            std::cerr << "WARNING] : Number must be between 0 and 99" << std::endl;
            std::cin >> inputnumber;
        }
        else if (inputnumber == guess) {
            std::cout << "You got it right" << std::endl;
            break;

        } else if (inputnumber > guess) {
            std::cout << "Your number is bigger than the guess" << std::endl;
            std::cin >> inputnumber;

        } else {
            std::cout << "Your number is smaller than the guess" << std::endl;
            std::cin >> inputnumber;
        }

    } while (true);

    EXIT_SUCCESS;
}


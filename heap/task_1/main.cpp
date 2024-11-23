#include <array>
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
#include <cstdlib>  // For abort()
#include <iostream>

// Size of each allocation (100 KiB)
constexpr size_t ALLOCATION_SIZE = 100 * 1024;

int main() {
    size_t allocation_count = 0;

    while (true) {
        try {
            // Attempt to allocate a 100KiB array on the stack
            double arr[ALLOCATION_SIZE /
                       sizeof(double)];  // 100 KiB array of doubles

            // Initialize array with some values (e.g., index-based)
            for (size_t i = 0; i < ALLOCATION_SIZE / sizeof(double); ++i) {
                arr[i] = i;
            }

            // Calculate the sum of the array elements to prevent
            // optimization
            double sum = 0;
            for (size_t i = 0; i < ALLOCATION_SIZE / sizeof(double); ++i) {
                sum += arr[i];
            }

            // Keep track of how many allocations we made
            allocation_count++;

            // For demonstration, print the number of successful allocations
            // every 100 allocations
            if (allocation_count % 100 == 0) {
                std::cout << "Successfully allocated " << allocation_count
                          << " arrays." << std::endl;
            }

            // Optionally print the sum of the array to show that it's used
            if (allocation_count % 1000 == 0) {
                std::cout << "Sum of elements in the last array: " << sum
                          << std::endl;
            }
        }

        catch (...) {
            // Catch any exceptions (although stack overflow usually does
            // not throw exceptions)
            std::cerr << "Exception caught, exiting program." << std::endl;
            return 1;
        }
        if (allocation_count > 10000) {
            cerr << "***********************************************"
                 << "iterations doen" << endl;
            break;
        }
    }

    // If we ever break out of the loop, we didn't reach the limit
    std::cerr << "Unexpected behavior: program did not crash." << std::endl;
    return 1;
}
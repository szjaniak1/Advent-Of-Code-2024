#include <fstream>
#include <iostream>

int main(void) {
    std::fstream input{"input.txt"};
    if (!input.is_open()) {
        std::cerr << "error - file cannot be open" << std::endl;
        return 1;
    }
    int result = 0;

    std::cout << "part 1 result: " << std::endl;
    return 0;
}
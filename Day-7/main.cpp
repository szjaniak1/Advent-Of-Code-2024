#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main(void) {
    int result = 0;
    std::ifstream input{"input.txt"};
    if (!input.is_open()) {
        std::cerr << "error - file cannot be open" << std::endl;
        return 1;
    }

    std::string line;
    size_t delimiter = 0;
    while (std::getline(input, line)) {
        delimiter = line.find(':');
        long long test_value = std::stoll(line.substr(0, delimiter));

        std::istringstream iss(line.substr(delimiter + 1));
        std::vector<long long> row;
        long long value;

        while (iss >> value) {
            row.push_back(value);
        }
        std::cout << std::endl; 
    }
    
    std::cout << "part 1 result: " << result << std::endl;
    return 0;
}
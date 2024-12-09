#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>

int main(void) {
    std::fstream input{"test_input.txt"};
    if (!input.is_open()) {
        std::cerr << "error - file cannot be open" << std::endl;
        return 1;
    }

    std::string line;
    std::map<char, std::vector<std::pair<size_t, size_t>>> antennas;
    size_t row = 0;
    while (input >> line) {
        for (size_t col = 0; col < line.size(); col++) {
            if (line[col] == '.') continue;
            if (antennas.find(line[col]) != antennas.end()) {
                antennas.find(line[col])->second.push_back({col, row});
                continue;
            }
            antennas.insert({line[col], {{col, row}}});
        }
    }

    for (auto& a : antennas) {
        std::cout << a.first << " : ";
        for (auto p : a.second) {
            std::cout << "{" << p.first << ";" << p.second << "},";
        }
        std::cout << std::endl;
    }

    int result = 0;

    std::cout << "part 1 result: " << std::endl;
    return 0;
}

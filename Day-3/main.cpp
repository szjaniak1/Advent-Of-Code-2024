#include <fstream>
#include <regex>
#include <iostream>

int main(void) {
    std::ifstream input{"input.txt"};
    if (!input.is_open()) {
        std::cerr << "error - file cannot be open" << std::endl;
        return 1;
    }

    int result = 0;
    std::regex mul_pattern("mul\\((\\d+),(\\d+)\\)|don't\\(\\)|do\\(\\)");
    std::string line;
    std::smatch match;
    bool mul_enabled = true;
    while (input >> line) {
        auto matches_begin = std::sregex_iterator(line.begin(), line.end(), mul_pattern);
        auto matches_end = std::sregex_iterator();

        for (std::sregex_iterator it = matches_begin; it != matches_end; ++it) {
            match = *it;
            if (!match[0].compare("don't()")) mul_enabled = false;
            else if (!match[0].compare("do()")) mul_enabled = true;
            else if (mul_enabled) result += std::stoi(match[1]) * std::stoi(match[2]);
        }
    }

    std::cout << "result: " << result << std::endl;

    return 0;
}

#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

static int search(std::vector<std::string>& input_vec, std::string buffer) {
    std::string buffer_cp = buffer;
    int result = 0;
    for (auto& st : input_vec) {
        for (auto s : st) {
            if (s == buffer.back()) {
                buffer.pop_back();
                if (buffer.empty()) {
                    result++;
                    buffer = buffer_cp;
                }
            }
            else {
                buffer = buffer_cp;
                if (s == buffer.back()) buffer.pop_back();
            }
        }
    }
    return result;
}

static int horizontal_search(std::vector<std::string>& input_vec, std::string buffer) {
    std::string buffer_cp = buffer;
    int result = 0;
    for (size_t col = 0; col < input_vec.size(); ++col) {
        for (size_t row = 0; row < input_vec[0].size(); ++row) {
            if (input_vec[row][col] == buffer.back()) {
                buffer.pop_back();
                if (buffer.empty()) {
                    result++;
                    buffer = buffer_cp;
                }
            }
            else {
                buffer = buffer_cp;
                if (input_vec[row][col] == buffer.back()) buffer.pop_back();
            }
        }
    }
    return result;
}

static int diagonal_search(std::vector<std::string>& input_vec, std::string buffer) {
    std::string buffer_cp = buffer;
    int result = 0;

    return result;
}

int main(void) {
    std::ifstream input{"input.txt"};
    if (!input.is_open()) {
        std::cerr << "error - file cannot be open" << std::endl;
        return 1;
    }

    std::vector<std::string> input_vec;
    std::string line;
    while (input >> line) {
        input_vec.push_back(line);
    }

    int result = 0;
    result += search(input_vec, "SAMX");
    result += search(input_vec, "XMAS");
    result += horizontal_search(input_vec, "SAMX");
    result += horizontal_search(input_vec, "XMAS");
    std::cout << "result: " << result << std::endl;

    return 0;
}

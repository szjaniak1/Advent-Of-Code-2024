#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

static int horizontal_search(std::vector<std::string>& input_vec, std::string buffer) {
    std::string buffer_cp = buffer;
    int result = 0;
    for (auto& st : input_vec) {
        buffer = buffer_cp;
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

static int vertical_search(std::vector<std::string>& input_vec, std::string buffer) {
    std::string buffer_cp = buffer;
    int result = 0;
    for (size_t col = 0; col < input_vec.size(); ++col) {
        buffer = buffer_cp;
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
    size_t line_len = input_vec[0].size();
    size_t lines_num = input_vec.size();

    for (size_t col = 0; col < line_len; ++col) {
        buffer = buffer_cp;
        for (size_t j = col; j < line_len; ++j) {
            if (input_vec[j - col][j] == buffer.back()) {
                buffer.pop_back();
                if (buffer.empty()) {
                    result++;
                    buffer = buffer_cp;
                }
            }
            else {
                buffer = buffer_cp;
                if (input_vec[j - col][j] == buffer.back()) buffer.pop_back();
            }
        }
    }

    for (size_t row = 1; row < lines_num; ++row) {
        buffer = buffer_cp;
        for (size_t j = row; j < lines_num; ++j) {
            if (input_vec[j][j - row] == buffer.back()) {
                buffer.pop_back();
                if (buffer.empty()) {
                    result++;
                    buffer = buffer_cp;
                }
            }
            else {
                buffer = buffer_cp;
                if (input_vec[j][j - row] == buffer.back()) buffer.pop_back();
            }

        }
    }

    for (int col = line_len - 1; col >= 0; --col) {
        buffer = buffer_cp;
        size_t i = 0;
        for (int j = col; j >= 0; --j) {
            if (input_vec[i][j] == buffer.back()) {
                buffer.pop_back();
                if (buffer.empty()) {
                    result++;
                    buffer = buffer_cp;
                }
            }
            else {
                buffer = buffer_cp;
                if (input_vec[i][j] == buffer.back()) buffer.pop_back();
            }
            i++;
            if (i == lines_num) break;
        }
    }

    for (int row = 1; row < lines_num; ++row) {
        buffer = buffer_cp;
        size_t i = row;
        for (int j = line_len - 1; j >= 0; --j) {
            if (input_vec[i][j] == buffer.back()) {
                buffer.pop_back();
                if (buffer.empty()) {
                    result++;
                    buffer = buffer_cp;
                }
            }
            else {
                buffer = buffer_cp;
                if (input_vec[i][j] == buffer.back()) buffer.pop_back();
            }
            i++;
            if (i == lines_num) break;
        }
    }

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
    result += vertical_search(input_vec, "SAMX");
    result += vertical_search(input_vec, "XMAS");
    result += horizontal_search(input_vec, "SAMX");
    result += horizontal_search(input_vec, "XMAS");
    result += diagonal_search(input_vec, "SAMX");
    result += diagonal_search(input_vec, "XMAS");
    std::cout << "result: " << result << std::endl;

    return 0;
}

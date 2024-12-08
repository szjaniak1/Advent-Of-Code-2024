#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
        
unsigned long long try_add(unsigned long long test_value, unsigned long long tmp_res, std::vector<unsigned long long>& values, size_t idx);        
unsigned long long try_mul(unsigned long long test_value, unsigned long long tmp_res, std::vector<unsigned long long>& values, size_t idx);        

unsigned long long try_add(unsigned long long test_value, unsigned long long tmp_res, std::vector<unsigned long long>& values, size_t idx) {
    tmp_res += values[idx];
    unsigned long long next_res;
    if (tmp_res > test_value) return 0;
    if (++idx == values.size()) return tmp_res;
    next_res = try_add(test_value, tmp_res, values, idx);
    if (next_res == test_value) return test_value;
    next_res = try_mul(test_value, tmp_res, values, idx);
    if (next_res == test_value) return test_value;
    return 0;
}

unsigned long long try_mul(unsigned long long test_value, unsigned long long tmp_res, std::vector<unsigned long long>& values, size_t idx) {
    tmp_res *= values[idx];
    unsigned long long next_res;
    if (tmp_res > test_value) return 0;
    if (++idx == values.size()) return tmp_res;
    next_res = try_add(test_value, tmp_res, values, idx);
    if (next_res == test_value) return test_value;
    next_res = try_mul(test_value, tmp_res, values, idx);
    if (next_res == test_value) return test_value;
    return 0;
}

int main(void) {
    unsigned long long result = 0;
    std::ifstream input{"input.txt"};
    if (!input.is_open()) {
        std::cerr << "error - file cannot be open" << std::endl;
        return 1;
    }

    std::string line;
    size_t delimiter = 0;
    while (std::getline(input, line)) {
        delimiter = line.find(':');
        unsigned long long test_value = std::stoull(line.substr(0, delimiter));
        std::cout << test_value << std::endl;

        std::istringstream iss(line.substr(delimiter + 1));
        std::vector<unsigned long long> row;
        unsigned long long value;

        while (iss >> value) {
            row.push_back(value);
        }

        unsigned long long temp_result = row[0];
        temp_result = try_add(test_value, temp_result, row, 1);        
        if (temp_result == test_value) {
            result += test_value;
            std::cout << "FOUND: " << test_value << std::endl;
            continue;
        }
        temp_result = row[0];
        temp_result = try_mul(test_value, temp_result, row, 1);        
        if (temp_result == test_value) { 
            result += test_value;
            std::cout << "FOUND: " << test_value << std::endl;
        }
    }
    
    std::cout << "part 1 result: " << result << std::endl;
    return 0;
}
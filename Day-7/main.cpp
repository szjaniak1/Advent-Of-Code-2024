#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <inttypes.h>
        
uint64_t try_add(uint64_t test_value, uint64_t tmp_res, std::vector<uint64_t>& values, size_t idx);        
uint64_t try_mul(uint64_t test_value, uint64_t tmp_res, std::vector<uint64_t>& values, size_t idx);        
uint64_t try_con(uint64_t test_value, uint64_t tmp_res, std::vector<uint64_t>& values, size_t idx);        
uint64_t concatenate(uint64_t fvalue, uint64_t svalue);

uint64_t concatenate(uint64_t fvalue, uint64_t svalue) {
    std::string fvalue_str = std::to_string(fvalue);
    std::string svalue_str = std::to_string(svalue);
    return std::stoull(fvalue_str + svalue_str);
}

uint64_t try_con(uint64_t test_value, uint64_t tmp_res, std::vector<uint64_t>& values, size_t idx) {
    tmp_res = concatenate(tmp_res, values[idx]);
    if (tmp_res > test_value) return 0;
    if (++idx == values.size()) return tmp_res;
    uint64_t next_res;
    next_res = try_add(test_value, tmp_res, values, idx);
    if (next_res == test_value) return test_value;
    next_res = try_mul(test_value, tmp_res, values, idx);
    if (next_res == test_value) return test_value;
    next_res = try_con(test_value, tmp_res, values, idx);
    if (next_res == test_value) return test_value;
    return 0;
}

uint64_t try_add(uint64_t test_value, uint64_t tmp_res, std::vector<uint64_t>& values, size_t idx) {
    tmp_res += values[idx];
    uint64_t next_res;
    if (tmp_res > test_value) return 0;
    if (++idx == values.size()) return tmp_res;
    next_res = try_add(test_value, tmp_res, values, idx);
    if (next_res == test_value) return test_value;
    next_res = try_mul(test_value, tmp_res, values, idx);
    if (next_res == test_value) return test_value;
    next_res = try_con(test_value, tmp_res, values, idx);
    if (next_res == test_value) return test_value;
    return 0;
}

uint64_t try_mul(uint64_t test_value, uint64_t tmp_res, std::vector<uint64_t>& values, size_t idx) {
    tmp_res *= values[idx];
    uint64_t next_res;
    if (tmp_res > test_value) return 0;
    if (++idx == values.size()) return tmp_res;
    next_res = try_add(test_value, tmp_res, values, idx);
    if (next_res == test_value) return test_value;
    next_res = try_mul(test_value, tmp_res, values, idx);
    if (next_res == test_value) return test_value;
    next_res = try_con(test_value, tmp_res, values, idx);
    if (next_res == test_value) return test_value;
    return 0;
}

int main(void) {
    uint64_t result = 0;
    std::ifstream input{"input.txt"};
    if (!input.is_open()) {
        std::cerr << "error - file cannot be open" << std::endl;
        return 1;
    }

    std::string line;
    size_t delimiter = 0;
    while (std::getline(input, line)) {
        delimiter = line.find(':');
        uint64_t test_value = std::stoull(line.substr(0, delimiter));

        std::istringstream iss(line.substr(delimiter + 1));
        std::vector<uint64_t> values;
        uint64_t value;

        while (iss >> value) {
            values.push_back(value);
        }

        uint64_t temp_result = try_add(test_value, 0, values, 0);        
        if (temp_result == test_value) {
            result += test_value;
            std::cout << "FOUND: " << test_value << std::endl;
        }
    }
    
    std::cout << "result: " << result << std::endl;
    return 0;
}

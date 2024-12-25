#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;
using std::cerr;

static uint find_all_paths(std::vector<std::vector<uint>>& topo_map, size_t row, size_t col) {
    uint result = 0;

    

    return result;
}

int main(void) {
    std::fstream input{"test_input.txt"};
    if (!input.is_open()) {
        cerr << "error - cannot open the file!" << endl;
    }

    constexpr size_t width = 8, height = 8;
    std::vector<std::vector<uint>> topographic_map;
    topographic_map.reserve(height);

    std::string line;
    std::vector<uint> row;
    row.reserve(width);
    while (input >> line) {
        row.clear();
        for (char c : line) {
            row.push_back(uint(c - '0'));
        }
        topographic_map.push_back(row);
    }

    uint result = 0;
    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            if (topographic_map[row][col] != 0) continue;

            result += find_all_paths(topographic_map, row, col);
        }
    }

    // for (auto& d : topographic_map) {
    //     for (uint a : d) {
    //         cout << a;
    //     }
    //     cout << endl;
    // }

    return 0;
}

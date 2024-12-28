#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;
using std::cerr;

static uint go_next(std::vector<std::vector<uint>>& topo_map, size_t row, size_t col) {
    uint result = 0;
    int val = (int)topo_map[row][col];
    if (val == 9) {
        // topo_map[row][col] = 10; // lol uncomment to part 1 
        return 1;
    }
    if (col < topo_map[0].size() - 1 && int(topo_map[row][col + 1]) - val == 1) result += go_next(topo_map, row, col + 1);
    if (col > 0 && int(topo_map[row][col - 1]) - val == 1) result += go_next(topo_map, row, col - 1);
    if (row < topo_map.size() - 1 && int(topo_map[row + 1][col]) - val == 1) result += go_next(topo_map, row + 1, col);
    if (row > 0 && int(topo_map[row - 1][col]) - val == 1) result += go_next(topo_map, row - 1, col);

    return result;
}

static uint go_next_cp(std::vector<std::vector<uint>> topo_map, size_t row, size_t col) {
    return go_next(topo_map, row, col);
}

int main(void) {
    std::fstream input{"input.txt"};
    if (!input.is_open()) {
        cerr << "error - cannot open the file!" << endl;
    }

    constexpr size_t width = 54, height = 54;
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
            result += go_next_cp(topographic_map, row, col);
        }
    }

    // for (auto& d : topographic_map) {
    //     for (uint a : d) {
    //         cout << a;
    //     }
    //     cout << endl;
    // }

    cout << "part 1 result : " << result << endl;

    return 0;
}

#include <sys/types.h>
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <cstdlib>

struct point {
    int x;
    int y;
    bool operator<(const point& other) const {
            if (x == other.x) return y < other.y;
            return x < other.x;
        }
};

int main(void) {
    std::fstream input{"input.txt"};
    if (!input.is_open()) {
        std::cerr << "error - file cannot be open" << std::endl;
        return 1;
    }

    std::string line;
    std::map<char, std::vector<point>> antennas;
    size_t row = 0;
    while (input >> line) {
        for (size_t col = 0; col < line.size(); col++) {
            if (line[col] == '.') continue;
            if (antennas.find(line[col]) != antennas.end()) {
                antennas.find(line[col])->second.push_back({int(col), int(row)});
                continue;
            }
            antennas.insert({line[col], {{int(col), int(row)}}});
        }
        row++;
    }

    std::set<point> antinodes;
    point fa, sa;
    for (auto& c : antennas) {
        for (size_t fa_itr = 0; fa_itr < c.second.size(); fa_itr++) {
            fa = c.second[fa_itr];
            for (size_t sa_itr = fa_itr + 1; sa_itr < c.second.size(); sa_itr++) {
                sa = c.second[sa_itr];
                int x_diff = std::abs(fa.x - sa.x);
                int y_diff = std::abs(fa.y - sa.y);
                if (fa.x > sa.x) {
                    if (fa.y > sa.y) {
                        antinodes.emplace(fa.x + x_diff, fa.y + y_diff);
                        antinodes.emplace(sa.x - x_diff, sa.y - y_diff);
                    }
                    else {
                        antinodes.emplace(fa.x + x_diff, fa.y - y_diff);
                        antinodes.emplace(sa.x - x_diff, sa.y + y_diff);
                    }
                }
                else {
                    if (fa.y > sa.y) {
                        antinodes.emplace(fa.x - x_diff, fa.y + y_diff);
                        antinodes.emplace(sa.x + x_diff, sa.y - y_diff);
                    }
                    else {
                        antinodes.emplace(fa.x - x_diff, fa.y - y_diff);
                        antinodes.emplace(sa.x + x_diff, sa.y + y_diff);
                    }
                }
            }
        }
    }

    auto count_func = [&line, row](const point& a) {
        if (a.x < 0) return false;
        if (a.x >= line.size()) return false;
        if (a.y < 0) return false;
        if (a.y >= row) return false;
        return true;
    };
    long result = std::count_if(antinodes.begin(), antinodes.end(), count_func);
    std::cout << "part 1 result: " << result << std::endl;
    return 0;
}

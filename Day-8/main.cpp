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
    point() {this->x = 0; this->y = 0;}
    point(int x, int y) {
        this->x = x;
        this->y = y;
    }
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
    std::set<point> antinodes;
    size_t row = 0;
    while (input >> line) {
        for (size_t col = 0; col < line.size(); col++) {
            if (line[col] == '.') continue;
            antinodes.emplace(int(col), int(row));
            if (antennas.find(line[col]) != antennas.end()) {
                antennas.find(line[col])->second.push_back({int(col), int(row)});
                continue;
            }
            antennas.insert({line[col], {{int(col), int(row)}}});
        }
        row++;
    }

    point fa, sa;
    for (auto& c : antennas) {
        for (size_t fa_itr = 0; fa_itr < c.second.size(); fa_itr++) {
            fa = c.second[fa_itr];
            for (size_t sa_itr = fa_itr + 1; sa_itr < c.second.size(); sa_itr++) {
                sa = c.second[sa_itr];
                int x_diff = std::abs(fa.x - sa.x);
                int y_diff = std::abs(fa.y - sa.y);
                int next_fa_x, next_fa_y, next_sa_x, next_sa_y;
                if (fa.x > sa.x) {
                    if (fa.y > sa.y) {
                        next_fa_x = fa.x + x_diff;
                        next_fa_y = fa.y + y_diff;
                        while (next_fa_x < line.size() && next_fa_y < row) {
                            antinodes.emplace(next_fa_x, next_fa_y);
                            next_fa_x += x_diff;
                            next_fa_y += y_diff;
                        }
                        next_fa_x = fa.x - x_diff;
                        next_fa_y = fa.y - y_diff;
                        while (next_fa_x >= 0 && next_fa_y >= 0) {
                            antinodes.emplace(next_fa_x, next_fa_y);
                            next_fa_x -= x_diff;
                            next_fa_y -= y_diff;
                        }
                    }
                    else {
                        next_fa_x = fa.x + x_diff;
                        next_fa_y = fa.y - y_diff;
                        while (next_fa_x < line.size() && next_fa_y >= 0) {
                            antinodes.emplace(next_fa_x, next_fa_y);
                            next_fa_x += x_diff;
                            next_fa_y -= y_diff;
                        }
                        next_fa_x = fa.x - x_diff;
                        next_fa_y = fa.y + y_diff;
                        while (next_fa_x >= 0 && next_fa_y < row) {
                            antinodes.emplace(next_fa_x, next_fa_y);
                            next_fa_x -= x_diff;
                            next_fa_y += y_diff;
                        }
                    }
                }
                else {
                    if (fa.y > sa.y) {
                        next_fa_x = fa.x - x_diff;
                        next_fa_y = fa.y + y_diff;
                        while (next_fa_x >= 0 && next_fa_y < row) {
                            antinodes.emplace(next_fa_x, next_fa_y);
                            next_fa_x -= x_diff;
                            next_fa_y += y_diff;
                        }
                        next_fa_x = fa.x + x_diff;
                        next_fa_y = fa.y - y_diff;
                        while (next_fa_x < line.size() && next_fa_y >= 0) {
                            antinodes.emplace(next_fa_x, next_fa_y);
                            next_fa_x -= x_diff;
                            next_fa_y += y_diff;
                        }
                    }
                    else {
                        next_fa_x = fa.x - x_diff;
                        next_fa_y = fa.y - y_diff;
                        while (next_fa_x >= 0 && next_fa_y >= 0) {
                            antinodes.emplace(next_fa_x, next_fa_y);
                            next_fa_x -= x_diff;
                            next_fa_y -= y_diff;
                        }
                        next_fa_x = fa.x + x_diff;
                        next_fa_y = fa.y + y_diff;
                        while (next_fa_x < line.size() && next_fa_y < row) {
                            antinodes.emplace(next_fa_x, next_fa_y);
                            next_fa_x += x_diff;
                            next_fa_y += y_diff;
                        }
                    }
                }
            }
        }
    }

    std::cout << "part 1 result: " << antinodes.size() << std::endl;
    return 0;
}

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

int main(void) {
    std::fstream input{"input.txt"};
    if (!input.is_open()) {
        std::cerr << "err - couldn't open a file" << std::endl;
    }

    std::string line = "";
    input >> line;

    int64_t id = 0;
    std::vector<int64_t> disk_map{};
    for (size_t i = 0; i < line.size(); i++) {
        for (size_t j = 0; j < int64_t(line[i]) - '0'; j++) {
            disk_map.push_back(id);
        }
        id++;

        if (i + 1 < line.size()) {
            ++i;
            for (size_t j = 0; j < int64_t(line[i]) - '0'; j++) {
                disk_map.push_back(-1);
            }
        }
    }
    
    for (auto it = disk_map.begin(); it != disk_map.end(); ++it) {
        it = std::find(it, disk_map.end(), -1);
        if (it != disk_map.end()) {
            *it = disk_map.back();
            disk_map.pop_back();
            while (disk_map.back() == -1) disk_map.pop_back();
        } else break;
    }

    int64_t checksum = 0;
    for (size_t i = 0; i < disk_map.size(); i++) {
        checksum += i * disk_map[i];
    }

    std::cout << checksum << std::endl;
    return 0;
}
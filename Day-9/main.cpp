#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>

static inline int64_t calc_checksum(std::vector<int64_t>& disk_map) {
    int64_t checksum = 0;
    for (size_t i = 0; i < disk_map.size(); i++) {
        if (disk_map[i] == -1) continue;
        checksum += i * disk_map[i];
    }
    return checksum;
}

static inline std::map<std::pair<std::vector<int64_t>::iterator, std::vector<int64_t>::iterator>, size_t> map_empty_spaces(std::vector<int64_t>& disk_map) {
    std::map<std::pair<std::vector<int64_t>::iterator, std::vector<int64_t>::iterator>, size_t> empty_spaces;

    size_t block_size;
    std::vector<int64_t>::iterator it_cp;
    for (auto it = disk_map.begin(); it != disk_map.end(); it++) {
        if (*it == -1) {
            block_size = 0;
            it_cp = it;
            do {
                block_size++;
                it++;
            } while (it != disk_map.end() && *it == -1);
            empty_spaces.insert({{it_cp, it - 1}, block_size});
        }
    }

    return empty_spaces;
}

static inline void print_map(std::vector<int64_t>& map) {
    for (auto d : map) {
        std::cout << d;
    }
    std::cout << std::endl;
}

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

    /* part 1 */
    {
        std::vector<int64_t> disk_map_p1 = disk_map;
        for (auto it = disk_map_p1.begin(); it != disk_map_p1.end(); ++it) {
            it = std::find(it, disk_map_p1.end(), -1);
            if (it != disk_map_p1.end()) {
                *it = disk_map_p1.back();
                disk_map_p1.pop_back();
                while (disk_map_p1.back() == -1) disk_map_p1.pop_back();
            } else break;
        }

        std::cout << "part 1 result: " << calc_checksum(disk_map_p1) << std::endl;
    }

    size_t block_len;
    int64_t curr_id;
    auto empty_spaces = map_empty_spaces(disk_map);
    for (auto it = disk_map.rbegin(); it != disk_map.rend(); ++it) {
        curr_id = *it;
        if (curr_id == -1) continue;
        block_len = 0;
        do {
            ++it;
            block_len++;
        } while (it != disk_map.rend() && *it == curr_id);
        it--;

        auto found_block = std::find_if(empty_spaces.begin(), empty_spaces.end(),
        [it, block_len](auto& eblock) {
            return eblock.first.second <= it.base() - 1 && block_len <= eblock.second;
        });

        if (found_block != empty_spaces.end()) {
            disk_map.erase(it.base() - 1, it.base() - 1 + block_len);
            disk_map.insert(it.base() -  1, block_len, -1);
            disk_map.erase(found_block->first.first, found_block->first.first + block_len);
            disk_map.insert(found_block->first.first, block_len, curr_id);
            empty_spaces.erase(found_block);
            if (found_block->second > block_len) empty_spaces.insert({{found_block->first.first + block_len, found_block->first.second}, found_block->second - block_len});
        }
    }

    std::cout << "part 2 result: " << calc_checksum(disk_map) << std::endl;

    return 0;
}

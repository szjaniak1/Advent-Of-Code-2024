#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

static inline int64_t calc_checksum(std::vector<int64_t>& disk_map) {
    int64_t checksum = 0;
    for (size_t i = 0; i < disk_map.size(); i++) {
        checksum += i * disk_map[i];
    }
    return checksum;
}

int main(void) {
    std::fstream input{"test_input.txt"};
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

    // for (auto d : disk_map) {
    //     std::cout << d;
    // }
    std::cout << std::endl;
    size_t block_len;
    int64_t curr_id;
    auto found_block = disk_map.begin();
    for (auto it = disk_map.rbegin() + 1; it != disk_map.rend(); ++it) {
        curr_id = *it;
        block_len = 1;
        do {
            ++it;
            block_len++;
        } while (it != disk_map.rend() && *it == curr_id);

        std::vector<int64_t> pattern(block_len, -1);
        found_block = std::search(disk_map.begin(), it.base(), pattern.begin(), pattern.end());
        if (found_block != it.base()) {
            found_block = disk_map.erase(found_block, found_block + block_len);
            found_block.insert(it, )
        }

        for (auto block_itr = found_block; block_itr != found_block + block_len; block_itr++) {

        }

        while (it != disk_map.rend() && *it == -1) ++it;
        if (it == disk_map.rend()) break;
        // it = std::find(it, disk_map.end(), -1);
        // if (it != disk_map.end()) {
        //     *it = disk_map.back();
        //     disk_map.pop_back();
        //     while (disk_map.back() == -1) disk_map.pop_back();
        // } else break;
    }

    // std::cout << "part 1 result: " << calc_checksum(disk_map) << std::endl;

    return 0;
}
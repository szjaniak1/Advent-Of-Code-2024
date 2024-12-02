#include <csignal>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <inttypes.h>
#include <algorithm>
#include <map>

int main(void) {
    std::ifstream input{"input.txt"};
    if (!input.is_open()) {
        std::cerr << "error - file cannot be open" << std::endl;
        return 1;
    }

    std::vector<int32_t> list1, list2;
    int32_t num1, num2;
    while (input >> num1 >> num2) {
        list1.push_back(num1);
        list2.push_back(num2);
    }

    // part1
    {
        std::sort(std::begin(list1), std::end(list1));
        std::sort(std::begin(list2), std::end(list2));

        int64_t result = 0;
        for (std::size_t i = 0; i < std::size(list1); i++) {
            result += std::abs(list1[i] - list2[i]);
        }

        std::cout << "result: " << result << std::endl;
    }

    //part2
    int64_t similarity_score_result = 0;
    std::map<int32_t, int64_t> similarity_score_map;
    const auto& s_score_map_end_itr = similarity_score_map.end();
    int64_t num_count;
    for (std::size_t i = 0; i < std::size(list1); i++) {
        if (similarity_score_map.find(list1[i]) != s_score_map_end_itr) {
            similarity_score_result += similarity_score_map.at(list1[i]);
        }
        else {
            num_count = std::count(std::begin(list2), std::end(list2), list1[i]);
            similarity_score_result += num_count * list1[i];
            similarity_score_map.insert({list1[i], num_count * list1[1]});
        }
    }

    std::cout << "similarity score: " << similarity_score_result << std::endl;

    input.close();
    return 0;
}

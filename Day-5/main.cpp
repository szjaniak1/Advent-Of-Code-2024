#include <fstream>
#include <map>
#include <vector>
#include <iostream>
#include <string>

int check_line(std::map<int, std::vector<int>>& rules_map, std::string& line) {
    for (int num : key_list(line)) { // func start
        for (int key : key_list(line.at(key), line.end()) {
            if (num in rules_map.at(key)) {
                return 0;       
            }
        }
    }
    return line.at(line.size() / 2); // middle number
}

int main(void) {
    std::ifstream input{"input.txt"};
    if (!input.is_open()) {
        std::cerr << "error - file cannot be open" << std::endl;
        return 1;
    }
    
    std::string line;
    std::map<int, std::vector<int>> rules_map; // or set? or unordered__??
    while (input >> line && line.size() == 5) {
        int key = std::stoi(); // insert to key
        int value = ;;//
        if (rules_map.find(key)) {
            rules_map.at(key).push_back(value);
        }
        std::cout << line << std::endl;
    }

    for (auto& d : rules_map) {
        std::sort(d.second.begin(), d.second.end());
    }

    int result = 0;
    while (input >> line) {
        result += check_line(rules_map, line); // already pass transformed line?? or transform in the func scope
    }

    std::cout << "part 1 result: " << result << std::endl;
    return 0;
}

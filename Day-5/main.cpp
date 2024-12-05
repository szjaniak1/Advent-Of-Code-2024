#include <fstream>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

static int check_line(std::map<int, std::vector<int>>& rules_map, std::string& line) {
    std::stringstream ss(line);
    std::string part;

    std::vector<int> update_specification;
    while (std::getline(ss, part, ',')) {
        update_specification.push_back(std::stoi(part));
    }

    for (auto it = update_specification.begin(); it != update_specification.end(); it++) { // func start
        for (auto next_it = it + 1; next_it != update_specification.end(); next_it++) {
            if (rules_map.find(*next_it) == rules_map.end()) continue;
            auto rules = rules_map.at(*next_it);
            if (std::find(rules.begin(), rules.end(), *it) != rules.end()) {
                return 0;       
            }
        }
    }

    return update_specification[update_specification.size() / 2]; // middle number
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
        size_t delimiter = line.find('|');
        int key = std::stoi(line.substr(0, delimiter));
        int value = std::stoi(line.substr(delimiter + 1));
        if (rules_map.find(key) != rules_map.end()) {
            rules_map.at(key).push_back(value);
        } else {
            rules_map.insert({key, {value}});
        }
    }

    for (auto& d : rules_map) {
        std::sort(d.second.begin(), d.second.end());
    }

    int result = 0;
    result += check_line(rules_map, line);
    while (input >> line) {
        result += check_line(rules_map, line); // already pass transformed line?? or transform in the func scope
    }

    std::cout << "part 1 result: " << result << std::endl;
    return 0;
}

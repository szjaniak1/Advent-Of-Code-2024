#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool check_tolerance(std::vector<int> rep, const size_t itr);
std::pair<bool, size_t> check_rep(std::vector<int> rep);

std::pair<bool, size_t> check_rep(std::vector<int> rep) {
    if (rep[0] > rep[1]) {
        for (size_t i = 0; i < rep.size() - 1; i++) {
            if (rep[i] <= rep[i + 1] || std::abs(rep[i] - rep[i + 1]) > 3) return {false, i};
        }
    }
    else {
        for (size_t i = 0; i < rep.size() - 1; i++) {
            if (rep[i] >= rep[i + 1] || std::abs(rep[i] - rep[i + 1]) > 3) return {false, i};
        }
    }

    return {true, 0};
}

bool check_tolerance(std::vector<int> rep, const size_t itr) {
    std::vector<int> cp_rep = rep;
    rep.erase(rep.begin() + itr);
    if (check_rep(rep).first) {
        return true;
    }

    if (itr > 0) {
        rep = cp_rep;
        rep.erase(rep.begin() + itr - 1);
        if (check_rep(rep).first) {
            return true;
        }
    }

    if (itr != cp_rep.size()){
        rep = cp_rep;
        rep.erase(rep.begin() + itr + 1);
        if (check_rep(rep).first) {
            return true;
        }
    }

    return false;
}

int main(void) {
    std::ifstream input{"input.txt"};
    if (!input.is_open()) {
        std::cerr << "error - file cannot be open" << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> reports;
    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        std::vector<int> row;
        int value;

        while (iss >> value) {
            row.push_back(value);
        }

        reports.push_back(row);
    }
    input.close();

    int safe_rep_num = 0;
    int safe_rep_num_with_tolerance = 0;
    for (const auto& rep : reports) {
        const auto& res = check_rep(rep);
        if (res.first) safe_rep_num++;
        else if (check_tolerance(rep, res.second)) safe_rep_num_with_tolerance++;
    }

    std::cout << "part1 safe reports: " << safe_rep_num << std::endl;
    std::cout << "part2 safe reports: " << safe_rep_num  + safe_rep_num_with_tolerance << std::endl;

    return 0;
}

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

enum direction {
    horizontal = 0,
    vertical = 1
};

static uint go_up(std::vector<std::string>& map, size_t pos_x, size_t pos_y);

static uint go_left(std::vector<std::string>& map, size_t pos_x, size_t pos_y) {
    uint count = 0;
    while (map[pos_y][pos_x] != '#') {
        if (map[pos_y][pos_x] != 'X') { 
            map[pos_y][pos_x] = 'X';
            count++;
        }
        pos_x--;
        if (pos_x == 0 && map[pos_y][pos_x] != '#') return ++count;
    }
    return count + go_up(map, pos_x + 1, pos_y);
}

static uint go_down(std::vector<std::string>& map, size_t pos_x, size_t pos_y) {
    uint count = 0;
    while (map[pos_y][pos_x] != '#') {
        if (map[pos_y][pos_x] != 'X') { 
            map[pos_y][pos_x] = 'X';
            count++;
        }
        pos_y++;
        if (pos_y == map.size()) return count;
    }
    return count + go_left(map, pos_x, pos_y - 1);
}

static uint go_right(std::vector<std::string>& map, size_t pos_x, size_t pos_y) {
    uint count = 0;
    while (map[pos_y][pos_x] != '#') {
        if (map[pos_y][pos_x] != 'X') { 
            map[pos_y][pos_x] = 'X';
            count++;
        }
        pos_x++;
        if (pos_x == map[0].size()) return count;
    }
    return count + go_down(map, pos_x - 1, pos_y);
}

static uint go_up(std::vector<std::string>& map, size_t pos_x, size_t pos_y) {
    uint count = 0;
    while (map[pos_y][pos_x] != '#') {
        if (map[pos_y][pos_x] != 'X') { 
            map[pos_y][pos_x] = 'X';
            count++;
        }
        pos_y--;
        if (pos_y == 0 && map[pos_y][pos_x] != '#') return ++count;
    }
    return count + go_right(map, pos_x, pos_y + 1);
}


int main(void) {
    std::ifstream input{"input.txt"};
    if (!input.is_open()) {
        std::cerr << "error - file cannot be open" << std::endl;
        return 1;
    }
    
    std::string line;
    std::vector<std::string> map;
    while (input >> line) {
        map.push_back(line);
    }

    size_t guard_pos_x = 0;
    size_t guard_pos_y = 0;
    for (size_t row = 0; row < map.size(); row++) {
        if (map[row].find('^') != std::string::npos) {
            guard_pos_x = map[row].find('^');
            guard_pos_y = row;
            break;
        }
    }

    size_t result = go_up(map, guard_pos_x, guard_pos_y);
    // for (auto& row : map) {
    //     std::cout << row << std::endl;
    // }

    std::cout << "part 1 result: " << result << std::endl;

    return 0;
}

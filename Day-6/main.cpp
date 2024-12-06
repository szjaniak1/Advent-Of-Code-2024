#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <inttypes.h>
#include <algorithm>

enum direction {
    none = 0x0,
    up = 0x1,
    down = 0x2,
    left = 0x10, 
    right = 0x20,
    start = 0x100
};

// functions that only go and check if possible obstacle created a loop
static bool go_right_check(std::vector<std::string>& map, std::vector<std::vector<uint8_t>>& map_direction, size_t pos_x, size_t pos_y);

static bool go_up_check(std::vector<std::string>& map, std::vector<std::vector<uint8_t>>& map_direction, size_t pos_x, size_t pos_y) {
    while (map[pos_y][pos_x] != '#') {
        if (map_direction[pos_y][pos_x] & up) return true;
        map_direction[pos_y][pos_x] |= up;
        pos_y--;
        if (pos_y == 0 && map[pos_y][pos_x] != '#') return false;
    }
    return go_right_check(map, map_direction, pos_x, pos_y + 1);
}

static bool go_left_check(std::vector<std::string>& map, std::vector<std::vector<uint8_t>>& map_direction, size_t pos_x, size_t pos_y) {
    while (map[pos_y][pos_x] != '#') {
        if (map_direction[pos_y][pos_x] & left) return true;
        map_direction[pos_y][pos_x] |= left;
        pos_x--;
        if (pos_x == 0 && map[pos_y][pos_x] != '#') return false;
    }
    return go_up_check(map, map_direction, pos_x + 1, pos_y);
}

static bool go_down_check(std::vector<std::string>& map, std::vector<std::vector<uint8_t>>& map_direction, size_t pos_x, size_t pos_y) {
    while (map[pos_y][pos_x] != '#') {
        if (map_direction[pos_y][pos_x] & down) return true;
        map_direction[pos_y][pos_x] |= down;
        pos_y++;
        if (pos_y == map.size()) return false;
    }
    return go_left_check(map, map_direction, pos_x, pos_y - 1);
}

static bool go_right_check(std::vector<std::string>& map, std::vector<std::vector<uint8_t>>& map_direction, size_t pos_x, size_t pos_y) {
    while (map[pos_y][pos_x] != '#') {
        if (map_direction[pos_y][pos_x] & right) return true;
        map_direction[pos_y][pos_x] |= right;
        pos_x++;
        if (pos_x == map[0].size()) return false;
    }
    return go_down_check(map, map_direction, pos_x - 1, pos_y);
}

// functions that create obstacle
static bool try_left_obstacle_go_up(std::vector<std::string> map, std::vector<std::vector<uint8_t>> map_direction, size_t pos_x, size_t pos_y) {
    if (map_direction[pos_y][pos_x - 1] != none || map[pos_y][pos_x - 1] == '#') return false;
    map[pos_y][pos_x - 1] = '#';
    bool check = go_up_check(map, map_direction, pos_x, pos_y);
    if (!check) return false;
    std::cout << pos_y << " " << pos_x - 1 << std::endl;
    return true;
}

static bool try_down_obstacle_go_left(std::vector<std::string> map, std::vector<std::vector<uint8_t>> map_direction, size_t pos_x, size_t pos_y) {
    if (map_direction[pos_y + 1][pos_x] != none || map[pos_y + 1][pos_x] == '#') return false;
    map[pos_y + 1][pos_x] = '#';
    bool check =  go_left_check(map, map_direction, pos_x, pos_y);
    if (!check) return false;
    std::cout << pos_y + 1<< " " << pos_x << std::endl;
    return true;
}

static bool try_right_obstacle_go_down(std::vector<std::string> map, std::vector<std::vector<uint8_t>> map_direction, size_t pos_x, size_t pos_y) {
    if (map_direction[pos_y][pos_x + 1] != none || map[pos_y][pos_x + 1] == '#') return false;
    map[pos_y][pos_x + 1] = '#';
    bool check = go_down_check(map, map_direction, pos_x, pos_y);
    if (!check) return false;
    std::cout << pos_y << " " << pos_x + 1 << std::endl;
    return true;
}

static bool try_up_obstacle_go_right(std::vector<std::string> map, std::vector<std::vector<uint8_t>> map_direction, size_t pos_x, size_t pos_y) {
    if (map_direction[pos_y - 1][pos_x] != none || map[pos_y - 1][pos_x] == '#') return false;
    map[pos_y - 1][pos_x] = '#';
    bool check = go_right_check(map, map_direction, pos_x, pos_y);
    if (!check) return false;
    std::cout << pos_y - 1<< " " << pos_x << std::endl;
    return true;
}

// functions that go through route and look for every possible obstacle
static uint go_up_obs(std::vector<std::string>& map, std::vector<std::vector<uint8_t>>& map_direction, size_t pos_x, size_t pos_y);

static uint go_left_obs(std::vector<std::string>& map, std::vector<std::vector<uint8_t>>& map_direction, size_t pos_x, size_t pos_y) {
    uint count = 0;
    while (map[pos_y][pos_x] != '#') {
        map_direction[pos_y][pos_x] |= left;
        pos_x--;
        if (pos_x == 0 && map[pos_y][pos_x] != '#') return count;
        if (try_left_obstacle_go_up(map, map_direction, pos_x + 1, pos_y)) count++;
    }
    return count + go_up_obs(map, map_direction, pos_x + 1, pos_y);
}

static uint go_down_obs(std::vector<std::string>& map, std::vector<std::vector<uint8_t>>& map_direction, size_t pos_x, size_t pos_y) {
    uint count = 0;
    while (map[pos_y][pos_x] != '#') {
        map_direction[pos_y][pos_x] |= down;
        pos_y++;
        if (pos_y == map.size()) return count;
        if (try_down_obstacle_go_left(map, map_direction, pos_x, pos_y - 1)) count++;
    }
    return count + go_left_obs(map, map_direction, pos_x, pos_y - 1);
}

static uint go_right_obs(std::vector<std::string>& map, std::vector<std::vector<uint8_t>>& map_direction, size_t pos_x, size_t pos_y) {
    uint count = 0;
    while (map[pos_y][pos_x] != '#') {
        map_direction[pos_y][pos_x] |= right;
        pos_x++;
        if (pos_x == map[0].size()) return count;
        if (try_right_obstacle_go_down(map, map_direction, pos_x - 1, pos_y)) count++;
    }
    return count + go_down_obs(map, map_direction, pos_x - 1, pos_y);
}

static uint go_up_obs(std::vector<std::string>& map, std::vector<std::vector<uint8_t>>& map_direction, size_t pos_x, size_t pos_y) {
    uint count = 0;
    while (map[pos_y][pos_x] != '#') {
        map_direction[pos_y][pos_x] |= up;
        pos_y--;
        if (pos_y == 0 && map[pos_y][pos_x] != '#') return count;
        if (try_up_obstacle_go_right(map, map_direction, pos_x, pos_y + 1)) count++;
    }
    return count + go_right_obs(map, map_direction, pos_x, pos_y + 1);
}

// part 1 functions
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
    std::vector<std::vector<uint8_t>> map_direction;
    while (input >> line) {
        std::vector<uint8_t> row_flags(line.size(), 0);
        map_direction.push_back(row_flags);
        map.push_back(line);
    }
    std::vector<std::string> map_cp = map;

    size_t guard_pos_x = 0;
    size_t guard_pos_y = 0;
    for (size_t row = 0; row < map.size(); row++) {
        if (map[row].find('^') != std::string::npos) {
            guard_pos_x = map[row].find('^');
            guard_pos_y = row;
            map_direction[guard_pos_y][guard_pos_x] |= start;
            break;
        }
    }

    size_t result_part1 = go_up(map, guard_pos_x, guard_pos_y);

    /* part 2 plan:
        - get the map with additional info (direction for every taken segment of a route):
            vector of vectors with pair <character, uint8_t> [uint8_t for holding flags]
        - find the standard route of the guard
        - check possible obstacles - if we get to the segment which we passed before in the same direction - it is a loop
    */

    size_t result_part2 = go_up_obs(map_cp, map_direction, guard_pos_x, guard_pos_y);

    std::cout << "part 1 result: " << result_part1 << std::endl;
    std::cout << "part 2 result: " << result_part2 << std::endl;

    return 0;
}

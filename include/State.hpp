#ifndef STATE_HPP
#define STATE_HPP

#include <string>

struct Point {
    int row;
    int column;

    bool operator==(const Point& other) const {
        return row == other.row && column == other.column;
    }
};

struct StateInfo {
    std::string name;
    std::string message;
    Point target;
    int energyChange;
    int moodChange;
    int curiosityChange;
};

#endif

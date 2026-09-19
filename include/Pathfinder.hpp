#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include <vector>
#include "State.hpp"

class Pathfinder {
public:
    Pathfinder(int rows, int columns, const std::vector<Point>& obstacles);
    std::vector<Point> findPath(const Point& start, const Point& goal);
    int getExpandedNodes() const;
    int heuristic(const Point& first, const Point& second) const;

private:
    int rows;
    int columns;
    int expandedNodes;
    std::vector<Point> obstacles;

    bool isObstacle(const Point& point) const;
    std::vector<Point> neighbors(const Point& point) const;
};

#endif

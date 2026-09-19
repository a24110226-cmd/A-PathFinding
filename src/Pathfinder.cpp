#include "Pathfinder.hpp"
#include <algorithm>
#include <map>
#include <queue>

Pathfinder::Pathfinder(int rows, int columns, const std::vector<Point>& obstacles)
    : rows(rows), columns(columns), expandedNodes(0), obstacles(obstacles) {}

bool Pathfinder::isObstacle(const Point& point) const {
    return std::find(obstacles.begin(), obstacles.end(), point) != obstacles.end();
}

std::vector<Point> Pathfinder::neighbors(const Point& point) const {
    const std::vector<Point> candidates{
        {point.row - 1, point.column}, {point.row + 1, point.column},
        {point.row, point.column - 1}, {point.row, point.column + 1}
    };
    std::vector<Point> valid;
    for (const Point& candidate : candidates) {
        if (candidate.row >= 0 && candidate.row < rows && candidate.column >= 0 && candidate.column < columns && !isObstacle(candidate)) {
            valid.push_back(candidate);
        }
    }
    return valid;
}

int Pathfinder::heuristic(const Point& first, const Point& second) const {
    return std::abs(first.row - second.row) + std::abs(first.column - second.column);
}

std::vector<Point> Pathfinder::findPath(const Point& start, const Point& goal) {
    struct Node { Point point; int cost; int priority; };
    auto compare = [](const Node& first, const Node& second) { return first.priority > second.priority; };
    std::priority_queue<Node, std::vector<Node>, decltype(compare)> open(compare);
    std::map<std::pair<int, int>, Point> cameFrom;
    std::map<std::pair<int, int>, int> cost;
    expandedNodes = 0;
    open.push({start, 0, heuristic(start, goal)});
    cost[{start.row, start.column}] = 0;

    while (!open.empty()) {
        const Node currentNode = open.top();
        open.pop();
        const Point current = currentNode.point;
        ++expandedNodes;
        if (current == goal) {
            std::vector<Point> path{current};
            std::pair<int, int> cursor{current.row, current.column};
            while (cameFrom.count(cursor)) {
                const Point previous = cameFrom.at(cursor);
                path.push_back(previous);
                cursor = {previous.row, previous.column};
            }
            std::reverse(path.begin(), path.end());
            return path;
        }
        for (const Point& next : neighbors(current)) {
            const int newCost = cost[{current.row, current.column}] + 1;
            const std::pair<int, int> nextKey{next.row, next.column};
            if (!cost.count(nextKey) || newCost < cost[nextKey]) {
                cost[nextKey] = newCost;
                cameFrom[nextKey] = current;
                open.push({next, newCost, newCost + heuristic(next, goal)});
            }
        }
    }
    return {start};
}

int Pathfinder::getExpandedNodes() const { return expandedNodes; }

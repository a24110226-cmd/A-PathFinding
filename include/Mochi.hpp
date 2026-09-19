#ifndef MOCHI_HPP
#define MOCHI_HPP

#include <string>
#include <vector>
#include "State.hpp"

class Mochi {
public:
    Mochi();
    void setState(const StateInfo& state);
    void setRoute(const std::vector<Point>& newRoute);
    void moveOneStep();
    void applyAction(const std::string& action);
    void passTime();

    const std::string& getStateName() const;
    const std::string& getMessage() const;
    const Point& getPosition() const;
    const Point& getTarget() const;
    const std::vector<Point>& getRoute() const;
    int getEnergy() const;
    int getMood() const;
    int getCuriosity() const;
    int getTurns() const;

private:
    std::string stateName;
    std::string message;
    Point position;
    Point target;
    std::vector<Point> route;
    int energy;
    int mood;
    int curiosity;
    int turns;

    void clampNeeds();
};

#endif

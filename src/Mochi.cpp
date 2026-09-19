#include "Mochi.hpp"
#include <algorithm>

Mochi::Mochi()
    : stateName("Explorando"), message("Mochi quiere descubrir algo nuevo."), position{3, 1}, target{1, 10}, energy(78), mood(84), curiosity(66), turns(0) {}

void Mochi::setState(const StateInfo& state) {
    stateName = state.name;
    message = state.message;
    target = state.target;
}

void Mochi::setRoute(const std::vector<Point>& newRoute) { route = newRoute; }

void Mochi::moveOneStep() {
    if (route.size() > 1) {
        position = route[1];
        route.erase(route.begin());
    }
}

void Mochi::applyAction(const std::string& action) {
    if (action == "comer") { energy += 4; mood += 3; curiosity -= 2; }
    if (action == "jugar") { energy -= 10; mood += 18; curiosity += 6; }
    if (action == "dormir") { energy += 35; mood += 2; curiosity -= 5; }
    if (action == "limpiar") { mood += 5; curiosity += 1; }
    if (action == "acariciar") { mood += 7; curiosity -= 1; }
    clampNeeds();
}

void Mochi::passTime() {
    ++turns;
    energy -= 3;
    mood -= 1;
    curiosity += 1;
    clampNeeds();
}

const std::string& Mochi::getStateName() const { return stateName; }
const std::string& Mochi::getMessage() const { return message; }
const Point& Mochi::getPosition() const { return position; }
const Point& Mochi::getTarget() const { return target; }
const std::vector<Point>& Mochi::getRoute() const { return route; }
int Mochi::getEnergy() const { return energy; }
int Mochi::getMood() const { return mood; }
int Mochi::getCuriosity() const { return curiosity; }
int Mochi::getTurns() const { return turns; }

void Mochi::clampNeeds() {
    energy = std::clamp(energy, 0, 100);
    mood = std::clamp(mood, 0, 100);
    curiosity = std::clamp(curiosity, 0, 100);
}

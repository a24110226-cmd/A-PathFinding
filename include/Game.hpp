#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include <random>
#include <string>
#include <vector>
#include "Mochi.hpp"
#include "Pathfinder.hpp"

class Game {
public:
    Game();
    void run();

private:
    static constexpr int mapRows = 7;
    static constexpr int mapColumns = 12;

    std::vector<Point> obstacles;
    Mochi mochi;
    Pathfinder pathfinder;
    std::map<std::string, StateInfo> states;
    std::vector<std::string> stateOrder;
    std::mt19937 randomEngine;
    bool running;

    void processInput();
    void update();
    void render() const;
    void renderNeeds() const;
    void renderMap() const;
    void renderSearchInfo() const;
    void performAction(const std::string& action);
    void selectState();
    void chooseState(const std::string& stateName, bool announce = true);
    void automaticStateChange();
    void showHelp() const;
    void clearScreen() const;
    std::string progressBar(int value) const;
};

#endif

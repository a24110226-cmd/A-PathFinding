#include "Game.hpp"
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>

Game::Game()
    : obstacles{{0, 3}, {0, 4}, {1, 3}, {2, 3}, {3, 3}, {4, 8}, {4, 9}, {5, 8}, {6, 2}, {6, 3}, {2, 7}, {3, 7}},
      pathfinder(mapRows, mapColumns, obstacles), randomEngine(std::random_device{}()), running(true) {
    states = {
        {"Explorando", {"Explorando", "Mochi busca algo nuevo que descubrir.", {1, 10}, -1, 1, 3}},
        {"Hambriento", {"Hambriento", "Mochi busca su cuenco favorito.", {5, 1}, -2, -1, 0}},
        {"Feliz", {"Feliz", "Mochi quiere jugar contigo.", {2, 10}, -1, 3, 1}},
        {"Cansado", {"Cansado", "Mochi busca un lugar tranquilo.", {5, 10}, 4, 0, -1}},
        {"Curioso", {"Curioso", "Mochi inspecciona un rincón misterioso.", {1, 6}, -2, 1, 4}},
        {"Aburrido", {"Aburrido", "Mochi necesita un poco de atención.", {3, 6}, -1, -2, 2}},
        {"Dormido", {"Dormido", "Zzz... Mochi está recuperando energía.", {5, 6}, 7, 1, -3}}
    };
    for (const auto& state : states) stateOrder.push_back(state.first);
    chooseState("Explorando", false);
}

void Game::chooseState(const std::string& stateName, bool announce) {
    mochi.setState(states.at(stateName));
    mochi.setRoute(pathfinder.findPath(mochi.getPosition(), mochi.getTarget()));
    if (announce) std::cout << "\nMochi cambió a: " << stateName << "\n";
}

void Game::clearScreen() const { std::cout << "\033[2J\033[H"; }

std::string Game::progressBar(int value) const {
    const int width = 18;
    const int filled = value * width / 100;
    return "[" + std::string(filled, '#') + std::string(width - filled, '.') + "]";
}

void Game::renderNeeds() const {
    std::cout << "  Energía    " << progressBar(mochi.getEnergy()) << " " << std::setw(3) << mochi.getEnergy() << "%\n";
    std::cout << "  Ánimo      " << progressBar(mochi.getMood()) << " " << std::setw(3) << mochi.getMood() << "%\n";
    std::cout << "  Curiosidad " << progressBar(mochi.getCuriosity()) << " " << std::setw(3) << mochi.getCuriosity() << "%\n";
}

void Game::renderMap() const {
    const auto& route = mochi.getRoute();
    std::cout << "\n  Jardín / ruta A*\n  +------------------------+\n";
    for (int row = 0; row < mapRows; ++row) {
        std::cout << "  |";
        for (int column = 0; column < mapColumns; ++column) {
            Point cell{row, column};
            if (cell == mochi.getPosition()) std::cout << " M";
            else if (cell == mochi.getTarget()) std::cout << " *";
            else if (std::find(obstacles.begin(), obstacles.end(), cell) != obstacles.end()) std::cout << " #";
            else if (std::find(route.begin(), route.end(), cell) != route.end()) std::cout << " .";
            else std::cout << "  ";
        }
        std::cout << " |\n";
    }
    std::cout << "  +------------------------+\n";
}

void Game::renderSearchInfo() const {
    const int g = mochi.getRoute().empty() ? 0 : static_cast<int>(mochi.getRoute().size()) - 1;
    const int h = pathfinder.heuristic(mochi.getPosition(), mochi.getTarget());
    std::cout << "\n  Búsqueda informada A*: f(n) = g(n) + h(n) | g=" << g << " h=" << h << " f=" << g + h;
    std::cout << " | nodos explorados=" << pathfinder.getExpandedNodes() << "\n";
}

void Game::render() const {
    const StateInfo& state = states.at(mochi.getStateName());
    std::cout << "==============================================================\n";
    std::cout << "                       MOCHI HOME\n";
    std::cout << "==============================================================\n";
    std::cout << "  Estado: " << state.name << " | " << state.message << "\n\n";
    renderNeeds();
    renderMap();
    renderSearchInfo();
    std::cout << "\n  [1] Comer       [2] Jugar       [3] Dormir\n";
    std::cout << "  [4] Limpiar     [5] Acariciar   [6] Cambiar estado\n";
    std::cout << "  [7] Esperar     [8] Ayuda       [9] Salir\n";
    std::cout << "\n  Acción: ";
}

void Game::performAction(const std::string& action) {
    mochi.applyAction(action);
    if (action == "comer" || action == "jugar") chooseState("Feliz", false);
    if (action == "dormir") chooseState("Dormido", false);
    update();
}

void Game::automaticStateChange() {
    std::uniform_int_distribution<int> choice(0, static_cast<int>(stateOrder.size()) - 1);
    chooseState(stateOrder[choice(randomEngine)], false);
}

void Game::update() {
    mochi.passTime();
    mochi.moveOneStep();
    if (mochi.getTurns() % 4 == 0) automaticStateChange();
}

void Game::selectState() {
    std::cout << "\n  Estados disponibles:\n";
    for (size_t index = 0; index < stateOrder.size(); ++index) std::cout << "  [" << index + 1 << "] " << stateOrder[index] << "\n";
    std::cout << "  Opción: ";
    int choice;
    if (std::cin >> choice && choice >= 1 && choice <= static_cast<int>(stateOrder.size())) {
        chooseState(stateOrder[choice - 1]);
        update();
    } else {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "  Opción no válida.\n";
    }
}

void Game::showHelp() const {
    std::cout << "\n  A* usa g(n), el costo recorrido, y h(n), la heurística Manhattan.\n";
    std::cout << "  Mochi calcula una ruta evitando obstáculos y avanza un paso\n  después de cada acción. Pulsa ENTER para volver...";
    std::cin.ignore();
    std::cin.get();
}

void Game::processInput() {
    std::string choice;
    std::cin >> choice;
    if (choice == "1") performAction("comer");
    else if (choice == "2") performAction("jugar");
    else if (choice == "3") performAction("dormir");
    else if (choice == "4") performAction("limpiar");
    else if (choice == "5") performAction("acariciar");
    else if (choice == "6") selectState();
    else if (choice == "7") update();
    else if (choice == "8") showHelp();
    else if (choice == "9") running = false;
    else std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void Game::run() {
    while (running) {
        clearScreen();
        render();
        processInput();
    }
    std::cout << "\nMochi se despide. Hasta pronto.\n";
}

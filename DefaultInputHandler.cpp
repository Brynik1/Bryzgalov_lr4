#include "DefaultInputHandler.h"
#include <fstream>
#include <sstream>

using json = nlohmann::json;

DefaultInputHandler::DefaultInputHandler() {
    loadCommandMappings("commands.json");
}

void DefaultInputHandler::loadCommandMappings(const std::string& filename) {
    std::ifstream file(filename);
    json j;
    file >> j;

    for (const auto& item : j["commands"].items()) {
        commandMap[item.key()] = item.value();
    }
}

bool DefaultInputHandler::loadGameFlag() {
    std::cout << "(1 - Yes, 0 - No): ";
    std::string flag_loadGame;

    while (true) {
        std::cin >> flag_loadGame;
        if (flag_loadGame == "0" || flag_loadGame == "1") {
            return flag_loadGame == "1";
        }
        else {
            std::cout << "Wrong choice, try again: ";
        }
    }
}

int DefaultInputHandler::getActionChoice() {
    std::string actionChoiceStr;

    while (true) {
        std::cout << "Choose an action (attack ~ 0, ability ~ 1, save ~ 2, load ~ 3): ";
        std::cin >> actionChoiceStr;

        // Проверка на наличие команды в мапе
        if (commandMap.find(actionChoiceStr) != commandMap.end()) {
            return commandMap[actionChoiceStr];
        }

        // Проверка, является ли ввод числом
        int actionChoice;
        std::istringstream iss(actionChoiceStr);
        if (iss >> actionChoice && !(iss >> actionChoiceStr)) {
            return actionChoice;
        }

        std::cout << "Unknown command, try again: ";
    }
}

int DefaultInputHandler::getActionChoiceNoAbility() {
    std::string actionChoiceStr;

    while (true) {
        std::cout << "Choose an action (attack ~ 0, save ~ 2, load ~ 3): ";
        std::cin >> actionChoiceStr;

        // Проверка на наличие команды в мапе
        if (commandMap.find(actionChoiceStr) != commandMap.end()) {
            return commandMap[actionChoiceStr];
        }

        // Проверка, является ли ввод числом
        int actionChoice;
        std::istringstream iss(actionChoiceStr);
        if (iss >> actionChoice && !(iss >> actionChoiceStr)) {
            return actionChoice;
        }

        std::cout << "Unknown command, try again: ";
    }
}

std::pair<int, int> DefaultInputHandler::getAttackCoordinates() {
    std::cout << "Enter coordinates (x y): ";
    int x, y;
    while (true) {
        if (std::cin >> x >> y) {
            return { x, y };
        }
        std::cout << "Invalid coordinates, try again: ";
        std::cin.clear();  // Сбрасываем флаг ошибки
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

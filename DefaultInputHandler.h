#pragma once
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <nlohmann/json.hpp>

class DefaultInputHandler {
private:
    std::map<std::string, int> commandMap;

public:
    DefaultInputHandler();
    void loadCommandMappings(const std::string& filename);
    bool loadGameFlag();
    int getActionChoice();
    int getActionChoiceNoAbility();
    std::pair<int, int> getAttackCoordinates();
};


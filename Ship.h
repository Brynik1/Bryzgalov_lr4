#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>

class Ship {
public:
    enum class ShipState {
        Whole,
        Damaged,
        Destroyed
    };
    Ship(int length);
    void damage(int segment);
    int getLength();
    ShipState getSegmentState(int segment);
    bool isDestroyed();
    void restore();
    void writeInfo(std::ofstream& out);
    void loadInfo(const std::string& text);
    void printFile(std::ifstream& in) {
        std::string line;
        while (getline(in, line)) {
            std::cout << line << std::endl;
        }
    }

private:
    int length;
    std::vector<ShipState> state;
};



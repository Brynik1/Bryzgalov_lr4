#pragma once
#include <vector>
#include <stdexcept>
#include "ShipManager.h"
#include "InvalidShipPlacementException.h"
#include "OutOfBoundsAttackException.h"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class GameField {
public:
    enum class CellStatus {
        Unknown,
        Empty,
        Ship
    };

    struct Cell {
        CellStatus status;
        Ship* ship; // Указатель на корабль, если он есть в этой клетке
    };

    GameField(int width, int height);
    void placeShip(Ship& ship, int x, int y, bool vertical, int shipIndex);
    bool attack(int x, int y, ShipManager& manager);
    GameField(const GameField& other); // Конструктор копирования
    GameField(GameField&& other) noexcept; // Конструктор перемещения
    GameField& operator=(const GameField& other); // Оператор присваивания копированием
    GameField& operator=(GameField&& other) noexcept; // Оператор присваивания перемещением
    void printField();
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    CellStatus getCellStatus(int x, int y) const { return field[y][x].status; }
    void removeShipsLocations();
    bool damagedSegment(int x, int y);
    void writeInfo(const std::string& filename);
    void loadInfo(const std::string& filename, ShipManager& manager);
    int getState(int x, int y);


private:
    int width;
    int height;
    std::vector<std::vector<Cell>> field;
};
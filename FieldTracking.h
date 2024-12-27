#pragma once
#include "FieldRender.h"
#include "GameField.h"
#include <iostream>

template<typename Renderer>
class FieldTracking {
public:
    FieldTracking(GameField& playerField, GameField& enemyField, Renderer& renderer)
        : playerField(playerField), enemyField(enemyField), renderer(renderer) {}

    void printFields() {
        int width = playerField.getWidth();
        int height = playerField.getHeight();

        // Отрисовка заголовков
        for (int i = 0; i < width/2 + 3; ++i) {
            std::cout << " ";
        }
        std::cout << "Your field";
        for (int i = 0; i < (width); ++i) {
            std::cout << "  ";
        }
        std::cout << "Enemy field" << std::endl;

        // Отрисовка индексов столбцов
        std::cout << "    ";
        for (int i = 0; i < width; ++i) {
            std::cout << i << " ";
        }
        std::cout << "          ";
        for (int i = 0; i < width; ++i) {
            std::cout << i << " ";
        }
        std::cout << std::endl;

        // Отрисовка строк поля
        for (int y = 0; y < height; ++y) {
            std::cout << "  ";
            renderer.renderFieldLine(playerField, y, false);
            std::cout << "        ";
            renderer.renderFieldLine(enemyField, y, true);
            std::cout << std::endl;
        }
    }

private:
    GameField& playerField;
    GameField& enemyField;
    Renderer& renderer;
};




#include "FieldRender.h"





void FieldRenderer::renderFieldLine(GameField & field, int y, bool flagEnemy) {
    int width = field.getWidth();
    std::cout << y << " ";
    for (int x = 0; x < width; ++x) {
        int state = field.getState(x, y);
        switch (state) {
        case 0: std::cout << "  "; break;
        case 1: std::cout << "\033[1;30m. \033[0m"; break; // Серый цвет для .
        case 2: std::cout << (flagEnemy ? "  " : "\033[1;32mo \033[0m"); break; // Зеленый цвет для !
        case 3: std::cout << "\033[1;33mx \033[0m"; break; // Желтый цвет для x
        case 4: std::cout << "\033[1;31mX \033[0m"; break; // Оранжевый цвет для X  (рыжий в ASCII не поддерживается)
        case 5: std::cout << "\033[1;31m# \033[0m"; break; // Красный цвет для #
        }
    }
}
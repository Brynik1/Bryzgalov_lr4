#include "Scanner.h"

bool Scanner::apply(GameField& field, ShipManager& manager) {
    int x, y;
    bool flag = true;
    std::cout << "Scanner activated! (x y): ";
    std::cin >> x >> y;

    for (int i = 0; i <= 1; ++i) {
        for (int j = 0; j <= 1; ++j) {
            int scanX = x + i;
            int scanY = y + j;
            if (scanX >= 0 && scanX < field.getWidth() && scanY >= 0 && scanY < field.getHeight()) {
                if (field.getCellStatus(scanX, scanY) == GameField::CellStatus::Ship) {
                    std::cout << "Ship detected at (" << scanX << ", " << scanY << ")\n";
                    flag = false;
                }
            }
        }
    }
    if (flag) {
        std::cout << "Scanner didn't see the ships\n";
    }
    return false;
}
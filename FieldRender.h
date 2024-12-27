#pragma once
#include "GameField.h"

class FieldRenderer {
public:
    void renderFieldLine(GameField& field, int y, bool flagEnemy);
};


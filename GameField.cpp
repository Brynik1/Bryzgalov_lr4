#include "GameField.h"

GameField::GameField(int width, int height)
    : width(width), height(height), field(height, std::vector<Cell>(width, { CellStatus::Unknown, nullptr })) {}

void GameField::placeShip(Ship& ship, int x, int y, bool vertical, int shipIndex) {
    int length = ship.getLength();
    if (vertical) {
        if (y + length > height || x < 0 || x >= width || y < 0) {
            throw InvalidShipPlacementException("Ship is out of bounds.");
        }
        int y0 = y - 1;
        int y1 = y + length;
        int x0 = x - 1;
        int x1 = x + 1;
        if (y0 < 0) {
            y0 = 0;
        }
        if (y1 >= height) {
            y1 = height - 1;
        }
        if (x0 < 0) {
            x0 = 0;
        }
        if (x1 >= width) {
            x1 = width - 1;
        }
        for (int i = x0; i <= x1; ++i) {
            for (int j = y0; j <= y1; ++j) {
                if (field[j][i].status != CellStatus::Unknown) {
                    throw InvalidShipPlacementException("Ship intersects with another ship.");
                }
            }
        }
        for (int i = 0; i < length; ++i) {
            field[y + i][x] = { CellStatus::Ship, &ship };
        }
    }
    else {
        if (x + length > width || x < 0 || y >= height || y < 0) {
            throw InvalidShipPlacementException("Ship is out of bounds.");
        }
        int y0 = y - 1;
        int y1 = y + 1;
        int x0 = x - 1;
        int x1 = x + length;
        if (y0 < 0) {
            y0 = 0;
        }
        if (y1 >= height) {
            y1 = height - 1;
        }
        if (x0 < 0) {
            x0 = 0;
        }
        if (x1 >= width) {
            x1 = width - 1;
        }
        for (int i = x0; i <= x1; ++i) {
            for (int j = y0; j <= y1; ++j) {
                if (field[j][i].status != CellStatus::Unknown) {
                    throw InvalidShipPlacementException("Ship intersects with another ship.");
                }
            }
        }
        for (int i = 0; i < length; ++i) {
            field[y][x + i] = { CellStatus::Ship, &ship };
        }
    }
}


bool GameField::attack(int x, int y, ShipManager& manager) {
    if (x < 0 || x >= width || y < 0 || y >= height)
        throw OutOfBoundsAttackException();

    if (field[y][x].status == CellStatus::Ship) {
        Ship& attackedShip = *field[y][x].ship; // Получаем ссылку на корабль из клетки

        if (attackedShip.isDestroyed()) {
            std::cout << "The ship has already been destroyed!\n";
            return false;
        }

        // Определяем сегмент
        int segmentIndex = 0;

        // Ищем начало корабля по горизонтали (слева)
        int x0 = x;
        while (x0 >= 1 && field[y][x0 - 1].status == CellStatus::Ship) {
            x0--;
        }

        // Ищем начало корабля по вертикали (сверху)
        int y0 = y;
        while (y0 >= 1 && field[y0 - 1][x].status == CellStatus::Ship) {
            y0--;
        }

        // Определяем сегмент, исходя из позиции начала корабля
        if (x - x0 > 0) {
            segmentIndex = x - x0; // Горизонтально
        }
        else {
            segmentIndex = y - y0; // Вертикально
        }

        // Наносим урон
        attackedShip.damage(segmentIndex); // Урон сегменту


        // Вывод информации об атаке
        if (attackedShip.isDestroyed()) {
            std::cout << "Hit on ship " << manager.getShipIndex(attackedShip) << " at (" << x << ", " << y << "), ship destroyed\n";
            return true;
        }
        else if (attackedShip.getSegmentState(segmentIndex) == Ship::ShipState::Destroyed) {
            std::cout << "Hit on ship " << manager.getShipIndex(attackedShip) << " at (" << x << ", " << y << "), segment destroyed\n";
        }
        else {
            std::cout << "Hit on ship " << manager.getShipIndex(attackedShip) << " at (" << x << ", " << y << ")\n";
        }

    }
    else {
        std::cout << "Missed :(\n";
        field[y][x].status = CellStatus::Empty; // Помечаем клетку как пустую
    }
    return false;
}


GameField::GameField(const GameField& other)
    : width(other.width), height(other.height), field(other.height, std::vector<Cell>(other.width)) {
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            field[i][j].status = other.field[i][j].status;
            field[i][j].ship = other.field[i][j].ship; // Копируем указатель
        }
    }
}

GameField::GameField(GameField&& other) noexcept
    : width(other.width), height(other.height), field(std::move(other.field)) {
    other.width = 0;
    other.height = 0;
}

GameField& GameField::operator=(const GameField& other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        field.resize(height);
        for (size_t i = 0; i < height; ++i) {
            field[i].resize(width);
            for (size_t j = 0; j < width; ++j) {
                field[i][j].status = other.field[i][j].status;
                field[i][j].ship = other.field[i][j].ship; // Копируем указатель
            }
        }
    }
    return *this;
}

GameField& GameField::operator=(GameField&& other) noexcept {
    if (this != &other) {
        width = other.width;
        height = other.height;
        field = std::move(other.field);
        other.width = 0;
        other.height = 0;
    }
    return *this;
}


void GameField::printField() {
    // Вывод заголовка столбцов
    std::cout << "  ";
    for (int i = 0; i < width; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // Вывод поля
    for (int y = 0; y < height; ++y) {
        // Вывод номера строки
        std::cout << y << " ";

        for (int x = 0; x < width; ++x) {
            switch (getState(x, y)) {
            case 0:
                std::cout << "  ";
                break;
            case 1:
                std::cout << ". ";
                break;
            case 2:
                std::cout << "! ";
                break;
            case 3:
                std::cout << "x ";
                break;
            case 4:
                std::cout << "X ";
                break;
            case 5:
                std::cout << "# ";
                break;
            }
        }

        std::cout << std::endl;
    }
}

int GameField::getState(int x, int y) {
    int state;
    switch (field[y][x].status) {
    case CellStatus::Unknown:
        state = 0;
        break;
    case CellStatus::Empty:
        state = 1;
        break;
    case CellStatus::Ship:
        Ship& attackedShip = *field[y][x].ship; // Получаем ссылку на корабль из клетки
        if (attackedShip.isDestroyed()) {
            state = 5;
        }
        else {
            // Определяем сегмент
            int segmentIndex = 0;

            // Ищем начало корабля по горизонтали (слева)
            int x0 = x;
            while (x0 >= 1 && field[y][x0 - 1].status == CellStatus::Ship) {
                x0--;
            }

            // Ищем начало корабля по вертикали (сверху)
            int y0 = y;
            while (y0 >= 1 && field[y0 - 1][x].status == CellStatus::Ship) {
                y0--;
            }

            // Определяем сегмент, исходя из позиции начала корабля
            if (x - x0 > 0) {
                segmentIndex = x - x0; // Горизонтально
            }
            else {
                segmentIndex = y - y0; // Вертикально
            }


            if (attackedShip.getSegmentState(segmentIndex) == Ship::ShipState::Destroyed) {
                state = 4;
            }
            else if (attackedShip.getSegmentState(segmentIndex) == Ship::ShipState::Damaged) {
                state = 3;
            }
            else {
                state = 2;
            }

        }
        break;
    }
    return state;
}

bool GameField::damagedSegment(int x, int y) {
    Ship& attackedShip = *field[y][x].ship;
    int segmentIndex = 0;

    // Ищем начало корабля по горизонтали (слева)
    int x0 = x;
    while (x0 >= 1 && field[y][x0 - 1].status == CellStatus::Ship) {
        x0--;
    }

    // Ищем начало корабля по вертикали (сверху)
    int y0 = y;
    while (y0 >= 1 && field[y0 - 1][x].status == CellStatus::Ship) {
        y0--;
    }

    // Определяем сегмент, исходя из позиции начала корабля
    if (x - x0 > 0) {
        segmentIndex = x - x0; // Горизонтально
    }
    else {
        segmentIndex = y - y0; // Вертикально
    }
    if (attackedShip.getSegmentState(segmentIndex) == Ship::ShipState::Damaged) {
        return true;
    }
    return false;
}

void GameField::removeShipsLocations() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            field[y][x].status = CellStatus::Unknown;
            field[y][x].ship = nullptr;
        }
    }
}

void GameField::writeInfo(const std::string& filename) {
    std::ofstream out(filename);
    std::vector<int> sizes;

    if (!out) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }

    out << "Info about the GameField:\n";
    out << width << " " << height << std::endl;
    out << "Info about the Ships:\n";

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (field[y][x].ship != nullptr) {
                // Проверяем, является ли это начальной клеткой корабля
                bool isNewShip = (x == 0 || field[y][x - 1].ship == nullptr) &&
                    (y == 0 || field[y - 1][x].ship == nullptr);

                if (isNewShip) {
                    out << "New ship\n";
                    out << x << " " << y;

                    // Определяем ориентацию корабля
                    if (x + 1 == width || field[y][x + 1].ship == nullptr) {
                        out << " Vertical\n";
                    }
                    else {
                        out << " Horizontal\n";
                    }

                    sizes.push_back(field[y][x].ship->getLength());
                    field[y][x].ship->writeInfo(out);
                }
            }
        }
    }

    // Запись размеров кораблей
    out << "Sizes: ";
    for (size_t i = 0; i < sizes.size(); ++i) {
        out << sizes[i];
        if (i != sizes.size() - 1) {
            out << " "; // Выводим пробел между элементами, кроме последнего
        }
        else {
            out << std::endl;
        }
    }

    // Запись статусов клеток
    out << "Statuses:\n";
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            switch (field[y][x].status) {
            case CellStatus::Unknown:
                out << "0 ";
                break;
            case CellStatus::Empty:
                out << "1 ";
                break;
            case CellStatus::Ship:
                out << "2 ";
                break;
            }
        }
        out << std::endl;
    }

    out.close(); // Закрываем файл (хотя деструктор out закроет его автоматически)
}


void GameField::loadInfo(const std::string& filename, ShipManager& manager) {
    manager.removeAllShips();
    field.clear();

    std::ifstream in(filename);
    std::string line;

    // Чтение размеров поля
    getline(in, line);
    getline(in, line);
    std::istringstream in_line(line);
    in_line >> width >> height;
    field.resize(height, std::vector<Cell>(width, { CellStatus::Unknown, nullptr }));

    // Чтение информации о кораблях
    getline(in, line);
    getline(in, line);

    int x, y;
    std::string orient;
    bool flag_vertical;
    int index = 0;

    while (line == "New ship") {
        getline(in, line);
        std::istringstream place(line);
        place >> x >> y >> orient;

        flag_vertical = (orient == "Vertical");

        Ship new_ship(1);
        getline(in, line);
        new_ship.loadInfo(line);
        manager.addShip(new_ship);

        this->placeShip(manager.getShip(index), x, y, flag_vertical, index);
        index++;

        getline(in, line);
    }

    // Чтение статусов клеток
    getline(in, line);
    int status;

    for (int y = 0; y < height; ++y) {
        getline(in, line);
        std::istringstream statuses(line);

        for (int x = 0; x < width; ++x) {
            statuses >> status;

            if (status == 0) {
                field[y][x].status = CellStatus::Unknown;
            }
            else if (status == 1) {
                field[y][x].status = CellStatus::Empty;
            }
            else {
                field[y][x].status = CellStatus::Ship;
            }
        }
    }

    in.close();
}


//json GameField::to_json(ShipManager& manager) const {
//    json j;
//    j["width"] = width;
//    j["height"] = height;
//
//    for (int i = 0; i < height; ++i) {
//        std::vector<int> row;
//        for (int j = 0; j < width; ++j) {
//            if (field[i][j].ship != nullptr) {
//                int index = manager.getShipIndex(*field[i][j].ship)
//            }
//            else if {
//                
//            }
//                
//            row.push_back(field[i][j]);
//        }
//        j["field"].push_back(row);
//    }
//
//    return j;
//}
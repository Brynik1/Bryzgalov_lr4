#include "ShipManager.h"


ShipManager::ShipManager(const std::vector<int>& sizes) {
    for (int size : sizes) {
        ships.emplace_back(size);
    }
}

Ship& ShipManager::getShip(int index) {
    if (index < 0 || index >= ships.size()) {
        throw std::out_of_range("Ship index out of range.");
    }
    return ships[index];
}

int ShipManager::getCount() {
    return ships.size();
}

int ShipManager::getShipIndex(const Ship& ship) const {
    for (int i = 0; i < ships.size(); ++i) {
        if (&ships[i] == &ship) {
            return i;
        }
    }
    return -1; // ������� �� ������
}

bool ShipManager::allShipDestroyed() {
    for (int i = 0; i < ships.size(); ++i) {
        if (!ships[i].isDestroyed())
            return false;
    }
    return true;
}

void ShipManager::restoreAllShips() {
    for (int i = 0; i < ships.size(); ++i) {
        ships[i].restore();
    }
}

void ShipManager::removeAllShips() {
    ships.clear();
}

void ShipManager::addShip(Ship& ship) {
    ships.push_back(ship);
}



void ShipManager::writeInfo(const std::string& filename) {
    std::ofstream out(filename);

    if (!out) {
        std::cerr << "������ �������� �����: " << filename << std::endl;
        return;
    }
    out << "Ships:\n";
    for (int i = 0; i < ships.size(); ++i) {
        ships[i].writeInfo(out);
    }
    out.close(); // ��������� ���� (���� ���������� out ������� ��� �������������)
}

void ShipManager::loadInfo(const std::string& filename) {
    ships.clear();
    std::ifstream in(filename);
    std::string line;
    getline(in, line);
    while (getline(in, line)) {
        //std::cout << line;
        Ship new_ship(1);
        new_ship.loadInfo(line);
        ships.push_back(new_ship);
    }
    in.close();
}



//void ShipManager::toJson(const std::string& filename) const {
//    json j;
//
//    for (int i = 0; i < ships.size(); ++i) {
//        json shipJson;
//        shipJson["size"] = ships[i].getLength();
//        shipJson["destroyed"] = ships[i].isDestroyed();
//    }
//    //for (const auto& ship : ships) {
//    //    json shipJson;
//    //    shipJson["size"] = ship.getLength(); // ��������������, ��� � ������ Ship ���� ����� getSize()
//    //    shipJson["destroyed"] = ship.isDestroyed(); // ��������������, ��� � ������ Ship ���� ����� isDestroyed()
//
//    //    j.push_back(shipJson);
//    //}
//
//    std::ofstream file(filename);
//    if (file.is_open()) {
//        file << j.dump(4); // ���������� JSON � ��������� � 4 �������
//        file.close();
//    }
//    else {
//        throw std::runtime_error("Could not open file for writing.");
//    }
//}
//
//void ShipManager::fromJson(const std::string& filename) {
//    std::ifstream file(filename);
//    if (!file.is_open()) {
//        throw std::runtime_error("Could not open file for reading.");
//    }
//
//    json j;
//    file >> j; // ������ ���������� ����� � ������ JSON
//    file.close();
//
//    ships.clear(); // ������� ������� ������ ��������
//
//    for (const auto& shipJson : j) {
//        int size = shipJson["size"];
//        bool destroyed = shipJson["destroyed"];
//
//        Ship newShip(size);
//        if (destroyed) {
//            newShip.destroy(); // ��������������, ��� � ������ Ship ���� ����� destroy()
//        }
//
//        ships.push_back(newShip);
//    }
//}

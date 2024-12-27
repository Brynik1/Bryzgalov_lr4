#include "Ship.h"

Ship::Ship(int length)
    : length(length), state(length, ShipState::Whole) {
    if (length < 1 || length > 4)
        throw std::invalid_argument("Ship length must be between 1 and 4.");
}

void Ship::damage(int segment) {
    if (segment < 0 || segment >= length)
        throw std::out_of_range("Segment index out of range.");

    if (state[segment] == ShipState::Whole) {
        state[segment] = ShipState::Damaged;
    }
    else if (state[segment] == ShipState::Damaged) {
        state[segment] = ShipState::Destroyed;
    }
}

int Ship::getLength() {
    return length;
}

Ship::ShipState Ship::getSegmentState(int segment) {
    return state[segment];
}

bool Ship::isDestroyed() {
    for (const auto& s : state) {
        if (s != ShipState::Destroyed) {
            return false;
        }
    }
    return true;
}

void Ship::restore() {
    for (int i = 0; i < length; ++i) {
        state[i] = ShipState::Whole;
    }
}

void Ship::writeInfo(std::ofstream& out) {
    out << length << " ";
    for (int i = 0; i < length; ++i) {
        if (state[i] == ShipState::Whole) {
            out << "Whole ";
        }
        else if (state[i] == ShipState::Damaged) {
            out << "Damaged ";
        }
        else {
            out << "Destroyed ";
        }
    }
    out << "\n";
}

void Ship::loadInfo(const std::string& text) {
    std::istringstream in(text);
    std::string stat;

    in >> length;
    //std::cout << "\n" << length << "\n";
    state.clear();
    for (int i = 0; i < length; ++i) {
        in >> stat;
        if (stat == "Whole") {
            state.push_back(ShipState::Whole);
        }
        else if (stat == "Damaged") {
            state.push_back(ShipState::Damaged);
        }
        else {
            state.push_back(ShipState::Destroyed);
        }
    }
    //std::cout << "Size: " << state.size() << "\n";
}
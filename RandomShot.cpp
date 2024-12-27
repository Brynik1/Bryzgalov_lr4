#include "RandomShot.h"
#include <random>

bool RandomShot::apply(GameField& field, ShipManager& manager) {
    srand(time(NULL));
    if (manager.getCount() > 0) {
        Ship* ship = nullptr;
        bool flag = true;
        for (int i = 0; i < manager.getCount(); i++) {
            ship = &manager.getShip(i);
            if (!(ship->isDestroyed())) {
                flag = false;
                break;
            }
        }
        if (flag) {
            std::cout << "All ships destroed!\n";
        } else {
            int random_index;
            do {
                random_index = rand() % manager.getCount();
                ship = &manager.getShip(random_index);
            } while (ship->isDestroyed());

            int segment_index;
            do {
                segment_index = rand() % ship->getLength();
            } while (ship->getSegmentState(segment_index) == Ship::ShipState::Destroyed);
            ship->damage(segment_index);
            std::cout << "Random shot hit the ship!\n";
        }
    }
    return false;
}

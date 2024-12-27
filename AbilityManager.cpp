#include "AbilityManager.h"

AbilityManager::AbilityManager() {
    generateInitialAbilities();
}

void AbilityManager::applyAbility(GameField& field, ShipManager& manager) {
    if (!abilities.empty()) {
        Ability* ability = abilities.front();
        abilities.pop();
        if (ability->apply(field, manager))
            doubleDamage = true;
        delete ability;
    }
    else {
        throw NoAbilitiesException();
    }
}

void AbilityManager::addAbility(Ability* ability) {
    abilities.push(ability);
}

void AbilityManager::generateInitialAbilities() {
    srand(time(NULL)); // Инициализация генератора случайных чисел
    // Массив с типами способностей (0 - DoubleDamage, 1 - Scanner, 2 - RandomShot)
    int abilityTypes[3] = { 0, 1, 2 };

    // Перемешивание массива для случайного порядка способностей
    for (int i = 2; i > 0; --i) {
        int j = rand() % (i + 1);
        std::swap(abilityTypes[i], abilityTypes[j]);
    }

    // Создание и добавление способностей в очередь
    for (int i = 0; i < 3; ++i) {
        switch (abilityTypes[i]) {
        case 0:
            addAbility(new DoubleDamage());
            break;
        case 1:
            addAbility(new Scanner());
            break;
        case 2:
            addAbility(new RandomShot());
            break;
        }
    }
}

void AbilityManager::giveRandomAbility() {
    srand(time(NULL)); // Инициализация генератора случайных чисел
    int abilityType = rand() % 3; // Случайное число от 0 до 2

    switch (abilityType) {
    case 0:
        std::cout << "\nAdded double damage ability!\n\n";
        addAbility(new DoubleDamage());
        break;
    case 1:
        std::cout << "\nAdded scanner ability!\n\n";
        addAbility(new Scanner());
        break;
    case 2:
        std::cout << "\nAdded RandomShot ability!\n\n";
        addAbility(new RandomShot());
        break;
    }
}


int AbilityManager::getAbilityCount() {
    return abilities.size();
}
bool AbilityManager::isDoubleDamage() {
    return doubleDamage;
}
void AbilityManager::delDoubleDamage() {
    doubleDamage = false;
}

void AbilityManager::writeInfo(const std::string& filename) {
    std::ofstream out(filename);

    out << this->getAbilityCount() << " ";

    if (!out) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }

    while (!abilities.empty()) {
        Ability* ability = abilities.front();
        out << ability->getName() << " ";
        abilities.pop();
    }

    out.close();
}

void AbilityManager::loadInfo(const std::string& filename) {
    while (!abilities.empty()) {
        abilities.pop();
    }

    std::ifstream in(filename);
    int length;
    in >> length;
    std::string abil;
    for (int i = 0; i < length; ++i) {
        in >> abil;
        if (abil == "Scanner") {
            addAbility(new Scanner());
        }
        else if (abil == "DoubleDamage") {
            addAbility(new DoubleDamage());
        }
        else {
            addAbility(new RandomShot());
        }
    }
    
    in.close();
}

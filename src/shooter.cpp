//
#include "shooter.h"

Roll* Shooter::throw_dice(Die& d1, Die& d2) {
    Roll* roll = new Roll(d1, d2);
    roll->roll_dice();
    rolls.push_back(roll);
    return roll;
}

void Shooter::display_rolled_values() {
    for (auto roll : rolls) {
        std::cout << "Rolled: " << roll->roll_value() << "\n";
    }
}

Shooter::~Shooter() {
    for (auto roll : rolls) {
        delete roll;
    }
    rolls.clear();  // not required but good practice
}
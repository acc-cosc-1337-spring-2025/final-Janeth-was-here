#include <iostream>
#include <ctime>
#include "die.h"
#include "roll.h"
#include "shooter.h"
#include "come_out_phase.h"
#include "point_phase.h"

using std::cout;
using std::endl;

int main() {
    // Seed random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Create two dice
    Die die1;
    Die die2;

    // Create Shooter instance
    Shooter shooter;

    // Pointer to Roll
    Roll* roll = shooter.throw_dice(die1, die2);
    int rolled_value = roll->roll_value();

    // Create ComeOutPhase instance
    ComeOutPhase come_out_phase;

    // Handle Come Out Phase
    while (come_out_phase.get_outcome(roll) == RollOutcome::natural ||
           come_out_phase.get_outcome(roll) == RollOutcome::craps) {
        cout << "Rolled " << rolled_value << " roll again\n";
        roll = shooter.throw_dice(die1, die2);
        rolled_value = roll->roll_value();
    }

    // After loop: point phase begins
    cout << "Rolled " << rolled_value << " start of point phase\n";
    cout << "Roll until " << rolled_value << " or a 7 is rolled\n";

    int point = rolled_value;
    roll = shooter.throw_dice(die1, die2);
    rolled_value = roll->roll_value();

    PointPhase point_phase(point);

    while (point_phase.get_outcome(roll) == RollOutcome::nopoint) {
        cout << "Rolled " << rolled_value << " roll again\n";
        roll = shooter.throw_dice(die1, die2);
        rolled_value = roll->roll_value();
    }

    // End of point phase
    cout << "Rolled " << rolled_value << " end of point phase\n\n";

    // Display all rolls
    shooter.display_rolled_values();

    return 0;
}
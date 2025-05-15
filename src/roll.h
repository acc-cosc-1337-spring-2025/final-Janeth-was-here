#ifndef ROLL_H
#define ROLL_H

#include "die.h"

class Roll {
public:
    // Constructor: takes references to two Die objects
    Roll(Die& d1, Die& d2);

    // Rolls both dice and stores the sum
    void roll_dice();

    // Returns the result of the roll
    int roll_value() const;

private:
    Die& die1;
    Die& die2;
    int rolled_value {0};  // total of both dice rolls
};

#endif // ROLL_H
//
#include "roll.h"

// Constructor uses initializer list to bind die1 and die2 to references
Roll::Roll(Die& d1, Die& d2) : die1(d1), die2(d2) {}

// Rolls both dice and saves the result
void Roll::roll_dice() {
    int value1 = die1.roll();
    int value2 = die2.roll();
    rolled_value = value1 + value2;
}

// Returns the result of the last roll
int Roll::roll_value() const {
    return rolled_value;
}
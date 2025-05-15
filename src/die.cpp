//
#include "die.h"
#include <cstdlib>  // for rand, srand
#include <ctime>    // for time

int Die::roll() {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));  // seed only once per run
        seeded = true;
    }
    return (rand() % sides) + 1;  // random number from 1 to 6
}
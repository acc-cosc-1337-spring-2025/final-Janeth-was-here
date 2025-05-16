#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "die.h"
#include "roll.h"
#include "shooter.h"
#include "come_out_phase.h"
#include "point_phase.h"

TEST_CASE("Die roll returns values from 1 to 6") 
{
    Die die;

    for (int i = 0; i < 10; ++i) {
        int roll_result = die.roll();
        REQUIRE(roll_result >= 1);
        REQUIRE(roll_result <= 6);
    }
}

TEST_CASE("Roll class returns values between 2 and 12") {
    Die die1;
    Die die2;
    Roll roll(die1, die2);

    for (int i = 0; i < 10; ++i) {
        roll.roll_dice();
        int result = roll.roll_value();
        REQUIRE(result >= 2);
        REQUIRE(result <= 12);
    }
}

TEST_CASE("Shooter throws dice and returns value between 2 and 12") {
    Die die1;
    Die die2;
    Shooter shooter;

    for (int i = 0; i < 10; ++i) {
        Roll* roll = shooter.throw_dice(die1, die2);
        int result = roll->roll_value();
        REQUIRE(result >= 2);
        REQUIRE(result <= 12);
    }

    //shooter.display_rolled_values(); //view values
}

// -------- ComeOutPhase Test Cases --------

TEST_CASE("ComeOutPhase returns natural for 7 and 11") {
    Die d1, d2;
    ComeOutPhase phase;

    Roll* r7 = nullptr;
    do {
        if (r7) delete r7;
        r7 = new Roll(d1, d2);
        r7->roll_dice();
    } while (r7->roll_value() != 7);
    REQUIRE(phase.get_outcome(r7) == RollOutcome::natural);
    delete r7;

    Roll* r11 = nullptr;
    do {
        if (r11) delete r11;
        r11 = new Roll(d1, d2);
        r11->roll_dice();
    } while (r11->roll_value() != 11);
    REQUIRE(phase.get_outcome(r11) == RollOutcome::natural);
    delete r11;
}

TEST_CASE("ComeOutPhase returns craps for 2, 3, 12") {
    Die d1, d2;
    ComeOutPhase phase;

    Roll* r2 = nullptr;
    do {
        if (r2) delete r2;
        r2 = new Roll(d1, d2);
        r2->roll_dice();
    } while (r2->roll_value() != 2);
    REQUIRE(phase.get_outcome(r2) == RollOutcome::craps);
    delete r2;

    Roll* r3 = nullptr;
    do {
        if (r3) delete r3;
        r3 = new Roll(d1, d2);
        r3->roll_dice();
    } while (r3->roll_value() != 3);
    REQUIRE(phase.get_outcome(r3) == RollOutcome::craps);
    delete r3;

    Roll* r12 = nullptr;
    do {
        if (r12) delete r12;
        r12 = new Roll(d1, d2);
        r12->roll_dice();
    } while (r12->roll_value() != 12);
    REQUIRE(phase.get_outcome(r12) == RollOutcome::craps);
    delete r12;
}

TEST_CASE("ComeOutPhase returns point for 4, 5, 6, 8, 9, 10") {
    Die d1, d2;
    ComeOutPhase phase;
    int points[] = {4, 5, 6, 8, 9, 10};

    for (int value : points) {
        Roll* roll = nullptr;
        do {
            if (roll) delete roll;
            roll = new Roll(d1, d2);
            roll->roll_dice();
        } while (roll->roll_value() != value);
        REQUIRE(phase.get_outcome(roll) == RollOutcome::point);
        delete roll;
    }
}

// -------- PointPhase Test Cases --------

TEST_CASE("PointPhase returns point when roll matches point") {
    Die d1, d2;
    int point = 6;
    PointPhase phase(point);

    Roll* roll = nullptr;
    do {
        if (roll) delete roll;
        roll = new Roll(d1, d2);
        roll->roll_dice();
    } while (roll->roll_value() != point);
    REQUIRE(phase.get_outcome(roll) == RollOutcome::point);
    delete roll;
}

TEST_CASE("PointPhase returns seven_out when roll is 7") {
    Die d1, d2;
    PointPhase phase(5);

    Roll* roll = nullptr;
    do {
        if (roll) delete roll;
        roll = new Roll(d1, d2);
        roll->roll_dice();
    } while (roll->roll_value() != 7);
    REQUIRE(phase.get_outcome(roll) == RollOutcome::seven_out);
    delete roll;
}

TEST_CASE("PointPhase returns nopoint for other values") {
    Die d1, d2;
    PointPhase phase(5);
    int other_values[] = {4, 6, 8, 9, 10};

    for (int value : other_values) {
        Roll* roll = nullptr;
        do {
            if (roll) delete roll;
            roll = new Roll(d1, d2);
            roll->roll_dice();
        } while (roll->roll_value() != value);
        REQUIRE(phase.get_outcome(roll) == RollOutcome::nopoint);
        delete roll;
    }
}
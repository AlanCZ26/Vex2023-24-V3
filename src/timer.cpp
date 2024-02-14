#include "main.h"

int start_times[5] = {
    0, 0, 0, 0, 0}; // 0 = auton, 1 is lift, 3 = routes

void startTimer(int slot)
{
    start_times[slot] = pros::millis();
}

int getTime(int slot)
{
    return (pros::millis() - start_times[slot]);
}

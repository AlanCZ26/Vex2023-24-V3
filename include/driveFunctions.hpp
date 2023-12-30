#ifndef _DRIVE_FUNCTIONS_HPP
#define _DRIVE_FUNCTIONS_HPP
const int DRIVE = 1;
const int PTO = 0;

void moveDriveSideMotors(int leftPower, int rightPower);
void ptoSwitcher(int i);
/**
 * \param position up->1, down->0, mid->2
*/
void lifter(int position);
void moveDriveMotors(int forwardPower, int turningPower);
void catapult();
#endif
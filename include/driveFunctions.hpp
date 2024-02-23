#ifndef _DRIVE_FUNCTIONS_HPP
#define _DRIVE_FUNCTIONS_HPP
const int PTOMODECATA = 1;
const int PTOMODELIFT = 0;
const int liftDefault = 0, barHangMin = 1, sideHangMin = 2, barHangMax = 3, sideHangMax = 4;
extern int state;
void moveDriveSideMotors(int leftPower, int rightPower);
void ptoSwitcher(int i);
/**
 * \param position up->1, down->0, mid->2
*/
void moveDriveMotors(int forwardPower, int turningPower);
/**
 * \param input Desired position
*/
void lift(int input);
/**
 * \param i Boolean on/off
*/
void catapult(bool i);
#endif
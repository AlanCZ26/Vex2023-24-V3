#ifndef _DRIVE_FUNCTIONS_HPP
#define _DRIVE_FUNCTIONS_HPP
const int PTOMODECATA = 1;
const int PTOMODELIFT = 0;
extern bool skillsCataVariable;
void moveDriveSideMotors(int leftPower, int rightPower);
void ptoSwitcher(int i);
/**
 * \param position up->1, down->0, mid->2
*/
void moveDriveMotors(int forwardPower, int turningPower);
#endif
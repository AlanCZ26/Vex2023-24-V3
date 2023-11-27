const int DRIVE = 0;
const int PTO = 1;
const int SW = 2;
const int DOWN = 1;
const int UP = 2;


/** 
 * range (-127 - 127)
 */
void drivetrain(int l, int r);

/** \param s forward/backward speed (-127 - 127)
 *  \param r rotation speed (-127 - 127)
 */
void driveDifferencial(int s, int r);

/** shoot cata once */
void catapult();

void lifter(int state);

void ptoSwitcher(int i);

void set_stopping(motor_brake_mode_e i);
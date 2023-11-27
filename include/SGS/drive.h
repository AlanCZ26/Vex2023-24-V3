const int DRIVE = 0;
const int PTO = 1;
const int SW = 2;
const int DOWN = 1;
const int UP = 2;

extern int liftVar;

/** \param l speed  (-127 - 127)
 *  \param r speed  (-127 - 127)
 */
void drivetrain(int l, int r);

/** \param s forward/backward speed (-127 - 127)
 *  \param r rotation speed (-127 - 127)
 */
void driveDifferencial(int s, int r);

/** \param void shoot cata once */
void catapult();

void lifter(int state);

void ptoSwitcher(int i);
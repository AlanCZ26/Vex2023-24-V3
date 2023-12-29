#ifndef _AUTO_FUNCTIONS_HPP
#define _AUTO_FUNCTIONS_HPP
void resetMotorEncoders();
void moveDriveMotors(int forwardPower, int turningPower);
void moveDriveSideMotors(int leftPower, int rightPower);
void driveStraight(double inches, double targetDegree, double maxPower, double time, double kP, double kI, double kD);
void turn(double targetDegree, double time, double kP, double kI, double kD);
void PTOswitcher(int i);
void moveArm(int position);
void turnHead(double target, double kP, double kI, double kD);

extern bool cataRunner;
void catapult();


extern bool PTOvar;
/*void moveDriveMotors(int forwardPower, int turningPower); 
void drive(int lInput, int rInput); // Drivetrain speed for time
void PTOswitcher(bool i); // 
void PTOmotors(int s); // 
void catapult(); // 
void lifter(); // Lift
void driveInches(int lInput, int rInput, int lSpd, int rSpd); // Drive amount of Inches
void driveDist(double target); 
void driveFunction(double target, double Kp, double Ki, double Kd, double intKickin, double mv) 
void driveDist2(double target, double velo)
void rotCall(double target)
void rotCall2(double target, double p, double d)
void rotDeg(double target, double Kp, double Ki, double Kd, double timer, double mv, double iw)*/
#endif
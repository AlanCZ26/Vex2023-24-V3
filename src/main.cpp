#include "main.h"
#include "autoFunctions.hpp"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "pros/screen.h"
#include "timer.hpp"
#include <sys/_stdint.h>
// test
Motor lMotor1(11, MOTOR_GEAR_BLUE, true, E_MOTOR_ENCODER_DEGREES);
Motor lMotor2(12, MOTOR_GEAR_BLUE, true, E_MOTOR_ENCODER_DEGREES);
Motor lMotor3(13, MOTOR_GEAR_BLUE, true, E_MOTOR_ENCODER_DEGREES);
Motor rMotor1(18, MOTOR_GEAR_BLUE, false, E_MOTOR_ENCODER_DEGREES);
Motor rMotor2(19, MOTOR_GEAR_BLUE, false, E_MOTOR_ENCODER_DEGREES);
Motor rMotor3(20, MOTOR_GEAR_BLUE, false, E_MOTOR_ENCODER_DEGREES);

pros::MotorGroup leftMotors({lMotor1,lMotor2,lMotor3});
pros::MotorGroup rightMotors({rMotor1,rMotor2,rMotor3});

Motor intMotor(1);
Motor cataMotor(15, MOTOR_GEAR_GREEN, false, E_MOTOR_ENCODER_DEGREES);
Motor cataMotor2(16, MOTOR_GEAR_GREEN, false, E_MOTOR_ENCODER_DEGREES);

Distance cataDist(4); //temp number, not actually connected
Rotation liftRot(5); //temp
Rotation odomPodVertical(3);
Imu gyro(10); 

ADIDigitalOut wingsSolL('b');
ADIDigitalOut wingsSolR('a');
ADIDigitalOut backRight('c');
ADIDigitalOut backLeft('d');
ADIDigitalOut hangSol1('g');
ADIDigitalOut hangSol2('h');

Controller master(E_CONTROLLER_MASTER);
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

/*
int position = -1;
void liftThread()
{
	while (true)
	{
		pros::delay(10);
		if (position != -1) {
			int temp = position;
			position = -1;
			lift(temp);
		}
	}
}
*/
void screenT() {
    // loop forever
    while (true) {
        lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        pros::lcd::print(0, "x: %f", pose.x); // print the x position
        pros::lcd::print(1, "y: %f", pose.y); // print the y position
        pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
		pros::lcd::print(3, "pitch: %f", gyro.get_roll());
        pros::delay(50);
    }
}

void on_center_button()
{
	static bool pressed = false;
	pressed = !pressed;
	if (pressed)
	{
		pros::lcd::set_text(2, "I was pressed!");
	}
	else
	{
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
	pros::lcd::register_btn1_cb(on_center_button);
	//Task armTask(liftThread);
	
	pros::Task screenTask(screenT);

	//pros::Task odomTrackerTask(odomTracker);
	chassis.calibrate();
	chassis.setPose(0,0,0);
	delay(2000);
	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rMotor3.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	lMotor3.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	cataMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	cataMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    gyro.tare_rotation();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

int AUTOTIMER = 4;
int autonMode = 3;
void autonomous()
{
	/*
	intMotor = 127;
	//driveStraight(10, 0, 100, 5000, 1, 0, 0);
	// turn(-90, 10000, 1, 0, 10);
	intMotor = 0;
	*/
	// pros::screen::print(TEXT_MEDIUM, 6, "x: %i", gyro);
	AUTOTIMER = 4;
	startTimer(AUTOTIMER);
	//testingAuto2(4);
	mainAuton(autonMode);
	

	//skillsAuto();
	//testingAuto();
	//nearsideSafeAWP();
	//nearsideBallrushAWP();
	//nearSideBallrushElims();
	//farSideAuto();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
	int x;
	int y;
	bool toggleBack = false;
	bool toggleWings = false;
	bool toggleCata = false;
	bool toggleHang = false;

	cataRunner = false;
	int iter = 0;
	while (gyro.is_calibrating())
	{
		pros::screen::print(TEXT_MEDIUM, 7, "gyro calibrating... %d/n", iter);
		iter += 10;
		pros::delay(10);
	}
	//if (!master.get_digital(DIGITAL_A)){skillsDriverMacro();}
	
	if (autonMode == -1) mainAuton(-1);

	while (true)
	{	
		x = master.get_analog(ANALOG_RIGHT_X);
		y = master.get_analog(ANALOG_LEFT_Y);
		x = (pow((abs(x)/5.3), 1.5))*(abs(x)/x);
		if (toggleHang){
			int hangSpdLim = 128;
			if (y > hangSpdLim) y = hangSpdLim;
			else if (y < -hangSpdLim) y = -hangSpdLim;
		}

		moveDriveMotors(y, x);

		/* print stuff
		// pros::screen::print(TEXT_MEDIUM, 2, "x: %i", x);
		// pros::screen::print(TEXT_MEDIUM, 3, "x: %i", y);
		// pros::screen::print(TEXT_MEDIUM, 4, "cata: %i", cataRunner);
		// pros::screen::print(TEXT_MEDIUM, 5, "gyro heading: %f", gyro.get_heading());
		// pros::screen::print(TEXT_MEDIUM, 6, "gyro rotation: %f", gyro.get_rotation());
		// pros::screen::print(TEXT_MEDIUM, 5, "dist: %i", catapultLoadDist.get());
		if (!master.get_digital(DIGITAL_LEFT)) {
			 //pros::screen::print(TEXT_MEDIUM, 8, "l1: %f", lMotor1.get_actual_velocity());
			 //pros::screen::print(TEXT_MEDIUM, 9, "l2: %f", lMotor2.get_actual_velocity());
			//pros::screen::print(TEXT_MEDIUM, 10, "lT: %f", ltMotor.get_actual_velocity());
			 //pros::screen::print(TEXT_MEDIUM, 10, "r1: %f", rMotor1.get_actual_velocity());
			 //pros::screen::print(TEXT_MEDIUM, 11, "r2: %f", rMotor2.get_actual_velocity());
			//pros::screen::print(TEXT_MEDIUM, 13, "rT: %f", rtMotor.get_actual_velocity());
		}
		*/

		if (master.get_digital_new_press(DIGITAL_R1))
		{
			toggleWings = !toggleWings;
			wingsSolL.set_value(toggleWings);
			wingsSolR.set_value(toggleWings);
			if (toggleWings&&toggleBack) {
				toggleBack = false;
				backLeft.set_value(false);
				backRight.set_value(false);
			}
		}
		if (master.get_digital_new_press(DIGITAL_R2))
		{
			toggleBack = !toggleBack;
			startTimer(5);
			backRight.set_value(toggleBack);
			backLeft.set_value(toggleBack);
			if (toggleWings&&toggleBack) {
				toggleWings = false;
				wingsSolL.set_value(false);
				wingsSolR.set_value(false);
			}
		}


		if (master.get_digital(DIGITAL_L1))
			intMotor = 127;
		else if (master.get_digital(DIGITAL_L2))
			intMotor = -127;
		else 
			intMotor.brake();
		if (master.get_digital(DIGITAL_X)){
			cataMotor.move_voltage(master.get_analog(ANALOG_RIGHT_Y)*150);
        	cataMotor2.move_voltage(master.get_analog(ANALOG_RIGHT_Y)*150);
			
		}
		if (master.get_digital_new_press(DIGITAL_X)){
			toggleHang = !toggleHang;
			hangSol1.set_value(toggleHang);
			hangSol2.set_value(toggleHang);
		}
		if (toggleHang && (gyro.get_roll() < -5)){
			toggleHang = false;
			hangSol1.set_value(false);
			hangSol2.set_value(false);
		}

		if (master.get_digital_new_press(DIGITAL_A)) {
			toggleCata = !toggleCata;
			catapult(toggleCata);
		}
		// hold r2 = 1 side down, let go is back up
		// press r2 once = both down with toggle back up
		/*if (master.get_digital_new_press(DIGITAL_R1) == 1){
			toggleWing = !toggleWing;
			wingsSolenoid2.set_value(toggle);
			wingsSolenoid.set_value(toggle);
		}
		*/
		/*if (master.get_digital_new_press(DIGITAL_X) == 1){
			toggle = !toggle;
			intakePiston.set_value(toggle);

		}*/

		/*
		if (master.get_digital_new_press(DIGITAL_UP) == 1){
			PTOswitcher(1);
		}*/
		pros::delay(50);
	}
}

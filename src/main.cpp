#include "main.h"
#include "autoFunctions.hpp"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "pros/screen.h"
#include "timer.hpp"
#include <sys/_stdint.h>
#include "lemlib/api.hpp"
// e
Motor lMotor1(6, MOTOR_GEAR_BLUE, true, E_MOTOR_ENCODER_DEGREES);
Motor lMotor2(7, MOTOR_GEAR_BLUE, true, E_MOTOR_ENCODER_DEGREES);
Motor ltMotor(1, MOTOR_GEAR_BLUE, true);
Motor rMotor1(8, MOTOR_GEAR_BLUE, false, E_MOTOR_ENCODER_DEGREES);
Motor rMotor2(9, MOTOR_GEAR_BLUE, false, E_MOTOR_ENCODER_DEGREES);
Motor rtMotor(10, MOTOR_GEAR_BLUE, false);

Motor intMotor(-11);
Motor cataMotor(-16);

Rotation liftSens(19);
Distance cataDist(13);
Rotation cataRot(12);
Imu gyro(2);

ADIDigitalOut PTOpiston({{20, 'd'}});
ADIDigitalOut wingsSolenoid2({{20, 'g'}});
ADIDigitalOut wingsSolenoid({{20, 'h'}});
ADIDigitalOut backRight({{20, 'b'}});
ADIDigitalOut ratchPiston({{20, 'c'}});
ADIDigitalOut backLeft({{20, 'a'}});

ADIDigitalOut intakePiston(8);

Controller master(E_CONTROLLER_MASTER);
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

int position = -1;
void liftThread()
{
	while (true)
	{
		pros::delay(10);
		if (position != -1) {
			lifter(position);
		}
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
	ptoSwitcher(DRIVE);
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
	pros::lcd::register_btn1_cb(on_center_button);
	Task cataTask(catapult);
	Task armTask(liftThread);
	gyro.reset();
	delay(2000);
	pros::Distance catapultLoadDist(12);
	rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	cataMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    gyro.tare_rotation();
	intakePiston.set_value(true);
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
	//skillsAuto();
	//testingAuto();
	//nearsideSafeAWP();
	nearsideBallrushAWP();
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
	bool toggle = 1;
	bool toggleWing = 0;
	bool toggleBack = 0;
	bool toggleBackRight = 0;
	bool toggleCata = 0;
	cataRunner = false;
	int iter = 0;
	while (gyro.is_calibrating())
	{
		pros::screen::print(TEXT_MEDIUM, 7, "gyro calibrating... %d/n", iter);
		iter += 10;
		pros::delay(10);
	}
	//if (!master.get_digital(DIGITAL_A)){skillsDriverMacro();}
	
	while (true)
	{
		x = master.get_analog(ANALOG_RIGHT_X);
		y = master.get_analog(ANALOG_LEFT_Y);
		moveDriveMotors(y, x);
		pros::screen::print(TEXT_MEDIUM, 2, "x: %i", x);
		pros::screen::print(TEXT_MEDIUM, 3, "x: %i", y);
		pros::screen::print(TEXT_MEDIUM, 4, "cata: %i", cataRunner);

		pros::screen::print(TEXT_MEDIUM, 5, "gyro heading: %f", gyro.get_heading());
		pros::screen::print(TEXT_MEDIUM, 6, "gyro rotation: %f", gyro.get_rotation());
		// pros::screen::print(TEXT_MEDIUM, 5, "dist: %i", catapultLoadDist.get());
		if (!master.get_digital(DIGITAL_LEFT)) {
			pros::screen::print(TEXT_MEDIUM, 8, "l1: %f", lMotor1.get_actual_velocity());
			pros::screen::print(TEXT_MEDIUM, 9, "l2: %f", lMotor2.get_actual_velocity());
			pros::screen::print(TEXT_MEDIUM, 10, "lT: %f", ltMotor.get_actual_velocity());
			pros::screen::print(TEXT_MEDIUM, 11, "r1: %f", rMotor1.get_actual_velocity());
			pros::screen::print(TEXT_MEDIUM, 12, "r2: %f", rMotor2.get_actual_velocity());
			pros::screen::print(TEXT_MEDIUM, 13, "rT: %f", rtMotor.get_actual_velocity());
		}

		if (master.get_digital_new_press(DIGITAL_Y) == 1)
		{
			ratchPiston.set_value(0);
			position = 1;
			backRight.set_value(1);
		}
		else if (master.get_analog(ANALOG_RIGHT_Y) <= -110)
		{
			position = 0;
		}
		else if (master.get_digital_new_press(DIGITAL_RIGHT) == 1)
		{
			ratchPiston.set_value(0);
			position = 2;
		}

		if (master.get_digital_new_press(DIGITAL_X) == 1)
		{
			toggle = !toggle;
			intakePiston.set_value(toggle);
		}
		if (master.get_digital_new_press(DIGITAL_R1) == 1)
		{
			toggleWing = !toggleWing;
			wingsSolenoid2.set_value(toggleWing);
			wingsSolenoid.set_value(toggleWing);
			if (toggleWing&&toggleBack) {
				toggleBack = false;
				backLeft.set_value(false);
				backRight.set_value(false);
			}
		}
		if (master.get_digital_new_press(DIGITAL_R2) == 1)
		{
			toggleBack = !toggleBack;
			startTimer(5);
			backRight.set_value(toggleBack);
			backLeft.set_value(toggleBack);
			if (toggleWing&&toggleBack) {
				toggleWing = false;
				wingsSolenoid2.set_value(false);
				wingsSolenoid.set_value(false);
			}
		}
		// else if(getTime(5) >= 2 && master.get_digital(DIGITAL_R2)){
		// 	backLeft.set_value(1);
		// 	backRight.set_value(1);
		// }

		if (master.get_digital_new_press(DIGITAL_UP) == 1)
		{
			toggleCata = !toggleCata;
			cataRunner = toggleCata;
		}
		if (master.get_digital_new_press(DIGITAL_DOWN) == 1)
		{
			std::cout << "test" << std::endl;
		}

		if (master.get_digital(DIGITAL_L1) == 1)
		{
			intMotor = 127;
		}
		else if (master.get_digital(DIGITAL_L2) == 1)
		{
			intMotor = -127;
		}
		else
		{
			intMotor.brake();
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
		pros::delay(20);
	}
}

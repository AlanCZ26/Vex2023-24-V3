#include "main.h"

Controller controller(E_CONTROLLER_MASTER);

Motor lMotor1(1, MOTOR_GEAR_BLUE, true, E_MOTOR_ENCODER_DEGREES);
Motor lMotor2(1, MOTOR_GEAR_BLUE, true, E_MOTOR_ENCODER_DEGREES);
Motor ltMotor(1, MOTOR_GEAR_BLUE, true);
Motor rMotor1(1, MOTOR_GEAR_BLUE, false, E_MOTOR_ENCODER_DEGREES);
Motor rMotor2(1, MOTOR_GEAR_BLUE, false, E_MOTOR_ENCODER_DEGREES);
Motor rtMotor(1, MOTOR_GEAR_BLUE, false);
Motor intakeMotor(1, MOTOR_GEAR_BLUE);
Motor cataMotor(1, MOTOR_GEAR_RED);

ADIDigitalOut ptoSol({{1, 1}});
ADIDigitalOut wingsSol({{1, 2}});
ADIDigitalOut wingsSol2({{1,2}});
ADIDigitalOut sideSol({{1, 3}});
ADIDigitalOut ratchSol({{1, 4}});
ADIDigitalIn cataLimit({{1, 5}});

Rotation liftSensor(10);
Distance cataDistance(1);

Imu imu(1);

bool cataRunner = false;
void cataThread()
{
	while (true)
	{
		pros::delay(10);
		if (cataRunner)
		{
			catapult();
			cataRunner = false;
		}
	}
}

int liftVar;
void liftThread()
{
	while (true)
	{
		if (liftVar != 0)
		{
			lifter(liftVar);
		}
		pros::delay(10);
	}
}

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
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
	pros::lcd::set_text(1, "initialize");

	pros::lcd::register_btn1_cb(on_center_button);

	Task cataTask(cataThread);
	Task liftTask(liftThread);
	imu.reset();

	cataMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
	intakeMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
	set_stopping(defaultBrakeMode);
	
	pros::delay(2000);
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
void autonomous() {}

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
	/*
	l1 = intake in
	l2 = int out
	r1 = wings toggle
	r2 = side mech
	up = intake up
	x = constant shooting
	down  = ratchet


	*/
	bool wingsState = false;
	bool sideState = false;
	bool ratchState = false;
	controller.set_text(0, 0, "Ratchet is off");
	while (true)
	{
		driveDifferencial(controller.get_analog(ANALOG_LEFT_X), controller.get_analog(ANALOG_RIGHT_Y));
		if (controller.get_digital_new_press(DIGITAL_R1))
		{
			wingsState = !wingsState;
			wingsSol.set_value(wingsState);
		}
		if (controller.get_digital_new_press(DIGITAL_R2))
		{
			sideState = !sideState;
			sideSol.set_value(sideState);
		}
		if (controller.get_digital_new_press(DIGITAL_DOWN))
		{
			ratchState = !ratchState;
			ratchSol.set_value(ratchState);
			controller.clear_line(0);
			if (ratchState == true)
				controller.set_text(0, 0, "Ratchet on");
			else
				controller.set_text(0, 0, "Ratchet off");
		}
		if (controller.get_digital(DIGITAL_L1))
			intakeMotor = 127;
		else if (controller.get_digital(DIGITAL_L2))
			intakeMotor = -127;
		else
			intakeMotor.brake();
		if (controller.get_digital(DIGITAL_X))
			cataRunner = true;
		if (controller.get_analog(ANALOG_RIGHT_Y) > 90)
		{
			liftVar = UP;
			set_stopping(MOTOR_BRAKE_BRAKE);
		}
		else if (controller.get_analog(ANALOG_RIGHT_Y) < -90)
		{
			liftVar = DOWN;
			set_stopping(defaultBrakeMode);
		}
		pros::delay(10);
	}
}

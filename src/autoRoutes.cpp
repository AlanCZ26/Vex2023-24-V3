#include "main.h"
#include "pros/llemu.hpp"
#include "pros/screen.h"

void testingAuto() {
    /*
    turnCall(45);
    turnCall(-45);
    turnCall(90);
    turnCall(-90);*/

    driveCall(12);
    delay(1000);
    driveCall(-12);
    delay(1000);
    driveCall(24);
    delay(1000);
    driveCall(-24);
    delay(1000);
}

void skillsAuto()
{
    intakePiston.set_value(false);
    cataRunner = true;
    intMotor = 127;
    delay(100);
    cataRunner = false;
    turnCall(-32);
    intMotor.brake();
    driveCall(20);
    turnCall(32);

    //push in
    intakePiston.set_value(true);
    intMotor = -127;
    moveDriveSideMotors(100, 100);
    delay(600);
    moveDriveSideMotors(0, 0);
    intMotor.brake();
    //back off, turn
    driveCall(-12);
    turnCall(72);
    driveCall(2);
    //prepare to shoot
    /*
    intakePiston.set_value(false);
    moveDriveSideMotors(-50, -50);
    delay(500);
    moveDriveSideMotors(100, 100);
    delay(100);
    moveDriveSideMotors(0, 0);
    */
    
    backRight.set_value(true);
    intakePiston.set_value(false);
    cataRunner = true;
    /*moveDriveSideMotors(-50, -50);
    delay(500);
    moveDriveSideMotors(-20, -20);
    delay(500);*/
    rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    delay(2000); //25!! ---------
    ratchPiston.set_value(false);
    delay(2000);
    backRight.set_value(false);
    delay(500);
    rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    driveCall(3);
    cataMotor.brake();
    cataRunner = false;
    turnCall(238);
    driveCall(-28);
    turnCall(-40);

    //across
    driveCall(-73);
    intakePiston.set_value(true);
    turnCall(-45);
    //descore
    backLeft.set_value(true);
    driveCall(-18); //
    backLeft.set_value(false);
    turnCall(-20);
    backRight.set_value(true);
    driveCall(-5);
    turnCall(-25);

    //side push
    moveDriveSideMotors(-100, -100);
    delay(800);
    moveDriveMotors(100,0);
    delay(100);
    turnCall(0);
    driveCall(15);
    backRight.set_value(false);
    backLeft.set_value(false);
    turnCall(-60);
    driveCall(-48);
    turnCall(60);

    // first push
    driveCall(-12);
    turnCall(90);
    moveDriveSideMotors(-100, -100);
    delay(900);
    moveDriveSideMotors(70, 70);
    delay(100);
    turnCall(0);
    //leave first push
    driveCall(24);
    turnCall(-90);
    /* last stuff old
    driveCall(-30);
    turnCall(-70);
    wingsSolenoid.set_value(true);
    wingsSolenoid2.set_value(true);
    delay(100);
    moveDriveSideMotors(100, 100);
    delay(900);
    moveDriveSideMotors(-100, -100);
    delay(300);
    turnCall(-20);
    moveDriveSideMotors(100, 100);
    delay(600);
    wingsSolenoid.set_value(false);
    wingsSolenoid2.set_value(false);
    driveCall(-7);
    turnCall(-90);
    driveCall(53);
    turnCall(-70);
    // side in
    moveDriveSideMotors(-50, -100);
    delay(1000);
    moveDriveSideMotors(100, 100);
    delay(400);
    turnCall(50);
    moveDriveSideMotors(-100, -100);
    delay(1000);
    moveDriveSideMotors(100, 100);
    delay(400);
    turnCall(0);
    moveDriveSideMotors(-100, -100);
    delay(1000);
    moveDriveSideMotors(100, 100);
    delay(400);
    moveDriveSideMotors(0, 0);*/
    
    //push middle
    driveCall(-38, 1.5, 10);
    turnCall(-70);
    wingsSolenoid.set_value(true);
    wingsSolenoid2.set_value(true);
    delay(100);
    moveDriveMotors(100,0);
    delay(1500);
    moveDriveMotors(-100,0);
    delay(100);
    turnCall(-20);
    std::cout<<"e"<<std::endl;
}


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

void skillsAuto() {
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
    gyro.tare_rotation();
    moveDriveSideMotors(0, 0);
    intMotor.brake();
    //back off, turn
    driveCall(-12);
    turnCall(70);
    driveCall(3);
    //prepare to shoot
    backRight.set_value(true);
    intakePiston.set_value(false);
    //autoCata = true;
    cataRunner = true;
    rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    delay(25000); //25!! ---------
    delay(2000);
    backRight.set_value(false);
    delay(500);
    rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    cataRunner = false;
    driveCall(15);
    turnCallAbsolute(45);
    intMotor = -127;
    driveCall(41);
    turnCallAbsolute(-90);
    moveDriveMotors(-100,0);
    delay(1200);
    backRight.set_value(true);
    backLeft.set_value(true);
    driveCall(36);
    moveDriveMotors(100,0);
    delay(80);
    backRight.set_value(false);
    backLeft.set_value(false);
    turnCall(0);
    driveCall(30);
    turnCall(-90);
    driveCall(-20);
    turnCall(90);
    moveDriveMotors(-100,0);
    backRight.set_value(true);
    backLeft.set_value(true);    
    delay(1400);
    moveDriveMotors(0,0);
}

void skillsAuto140()
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
    gyro.tare_rotation();
    moveDriveSideMotors(0, 0);
    intMotor.brake();
    //back off, turn
    driveCall(-12);
    turnCall(70);
    driveCall(3);
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
    //autoCata = true;
    cataRunner = true;
    /*moveDriveSideMotors(-50, -50);
    delay(500);
    moveDriveSideMotors(-20, -20);
    delay(500);*/
    rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    delay(25000); //25!! ---------
    ratchPiston.set_value(false);
    delay(2000);
    backRight.set_value(false);
    delay(500);
    rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    driveCall(3);
    //autoCata = false; 
    cataRunner = false;
    turnCall(240);
    driveCall(-26);
    turnCall(-40);

    //across
    intakePiston.set_value(true);
    driveCall(-67);
    turnCall(-45);

    //corner
    driveCall(-20);
    turnCall(-45);

    //side push
    backRight.set_value(true);
    moveDriveSideMotors(-100, -100);
    delay(800);
    moveDriveMotors(100,0);
    delay(100);
    turnCall(0);
    driveCall(15);
    backRight.set_value(false);
    backLeft.set_value(false);
    turnCall(-60);
    driveCall(-48,1.5,10);
    turnCall(60);

    // first push
    driveCall(-12);
    backRight.set_value(true);
    turnCall(90);
    moveDriveSideMotors(-100, -100);
    delay(900);
    backRight.set_value(false);
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
    
    //push left
    driveCall(-38, 1.5, 10);
    backLeft.set_value(true);
    turnCall(300);
    wingsSolenoid.set_value(true);
    wingsSolenoid2.set_value(true);    
    delay(200);
    backLeft.set_value(false);
    driveCall(20,1.5,10);
    moveDriveMotors(0,100);
    delay(100);
    turnCall(0);
    wingsSolenoid.set_value(false);
    wingsSolenoid2.set_value(false);    
    driveCall(-20);

    //push middle
    turnCall(60);
    driveCall(18);
    wingsSolenoid.set_value(true);
    wingsSolenoid2.set_value(true);    
    turnCall(-90);
    moveDriveMotors(100,0);
    delay(1000);
    moveDriveMotors(-100,0);
    delay(200);
    turnCall(0);
    moveDriveMotors(100,0);
    delay(1000);
    moveDriveMotors(-100,0);
    delay(100);
    driveCall(-24);

}

void skillsAuto2(){
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
    gyro.tare_rotation();
    moveDriveSideMotors(0, 0);
    intMotor.brake();
    //back off, turn
    driveCall(-12);
    turnCall(70);
    driveCall(3);
    //prepare to shoot
    backRight.set_value(true);
    intakePiston.set_value(false);
    //autoCata = true;
    cataRunner = true;
    rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    delay(25000); //25!! ---------
    ratchPiston.set_value(false);
    delay(2000);
    backRight.set_value(false);
    delay(500);
    rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    driveCall(3);
    //autoCata = false; 
    cataRunner = false;
    turnCall(240);
    driveCall(-24);
    turnCall(-40);

    //across
    intakePiston.set_value(true);
    driveCall(-67,2.3,7);
    turnCall(-20);

    //corner
    driveCall(-26);
    turnCall(-70);

    //side push
    backRight.set_value(true);
    moveDriveSideMotors(-100, -100);
    delay(800);
    moveDriveMotors(100,0);
    delay(100);
    turnCall(0);
    driveCall(3);
    backRight.set_value(false);
    backLeft.set_value(false);
    turnCall(90);
    driveCall(44);
    turnCall(90);

    // first push
    driveCall(16);
    turnCall(-100);
    moveDriveSideMotors(-100, -100);
    delay(900);
    backRight.set_value(false);
    moveDriveSideMotors(70, 70);
    delay(100);
    turnCall(10);
    //leave first push
    driveCall(24);
    turnCall(-90);

    //push left
    driveCall(-44);
    turnCall(-60);
    delay(200);
    moveDriveMotors(100,0);//driveCall(20);
    delay(900);
    moveDriveMotors(-100,0);
    delay(50);
    turnCall(-30);
    driveCall(-22);

    //push middle
    turnCall(90);
    driveCall(15);
    wingsSolenoid.set_value(true);
    wingsSolenoid2.set_value(true);    
    turnCall(-90);
    moveDriveMotors(100,0);
    delay(1000);
    moveDriveMotors(-100,0);
    delay(200);
    turnCall(0);
    moveDriveMotors(100,0);
    delay(1000);
    moveDriveMotors(-100,0);
    delay(100);
    driveCall(-24);

}
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/screen.h"

void testingAuto() {
    /*
    turnCall(45);
    turnCall(-45);
    turnCall(90);
    turnCall(-90);*/

    driveCall(24);
}
void testingAutoe(){
    driveCall(2);
    delay(500);
    driveCall(-2);
    delay(500);
    driveCall(4);
    delay(500);
    driveCall(-4);
    delay(500);
    driveCall(8);
    delay(500);
    driveCall(-8);
    delay(500);
    driveCall(12);
    delay(500);
    driveCall(-12);
    delay(500);
    driveCall(16);
    delay(500);
    driveCall(-16);
    delay(500);
    driveCall(20);
    delay(500);
    driveCall(-20);
    delay(500);
    driveCall(24);
    delay(500);
    driveCall(-24);
    delay(500);
    driveCall(30);
    delay(500);
    driveCall(-30);
    delay(500);
    driveCall(40);
    delay(500);
    driveCall(-40);
    delay(500);
    driveCall(50);
    delay(500);
    driveCall(-50);
    delay(500);

}

void skillsAuto() {
    ///*
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
    moveDriveSideMotors(127, 127);
    delay(600);
    moveDriveSideMotors(0, 0);
    intMotor.brake();

    //back off, turn
    driveCall(-12);
    //AIM HERE -----------------
    turnCall(72.5);
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
    delay(25000); //25!! ----------------------------------
    delay(2000);
    backRight.set_value(false);
    delay(500);
    rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    intMotor = -127;
    cataRunner = true;
    driveCall(15);
    cataRunner = false;
    turnCallAbsolute(35);
    driveCall(41);
    turnCallAbsolute(-90);

    //over the bar
    moveDriveMotors(-127,0);
    //delay(1200);
    startTimer(3);
    while (fabs(gyro.get_roll())<=5&&getTime(3)<1600){
        delay(10);
    }
    std::cout<<"OVER 5 ROLL"<<std::endl;
    while (fabs(gyro.get_roll())>5&&getTime(3)<1600){
        delay(10);
    }
    std::cout<<"UNDER 5 ROLL"<<std::endl;
    while (fabs(gyro.get_roll())<=5&&getTime(3)<1600){
        delay(10);
    }
    std::cout<<"OVER 5 ROLL"<<std::endl;
    while (fabs(gyro.get_roll())>5&&getTime(3)<1600){
        delay(10);
    }
    std::cout<<"UNDER 5 ROLL"<<std::endl;
    delay(100);
    intMotor.brake();
    moveDriveMotors(100,0);
    delay(700);
    gyro.set_rotation(-90);
    delay(100);
    //backRight.set_value(true);
    //backLeft.set_value(true);

    //first push
    moveDriveMotors(-60,0);
    delay(1650);
    moveDriveMotors(100,0);
    delay(80);

    //recenter and leave
    turnCall(0);
    driveCall(30);

    //turn and move
    turnCall(-90);
    driveCall(28);

    //aim and push (second)
    turnCall(65);
    backRight.set_value(true);
    backLeft.set_value(true);     
    driveCall(-34.5);
    backRight.set_value(false);
    backLeft.set_value(false);

    //leave
    moveDriveMotors(127,0);
    delay(80);
    turnCall(25);
    driveCall(30);
    turnCall(90);

    //across, aim and push (third)
    driveCall(46);
    turnCall(-65);
    backRight.set_value(true);
    backLeft.set_value(true);     
    driveCall(-35);
    backRight.set_value(false);
    backLeft.set_value(false);
    moveDriveMotors(127,0);
    delay(80);

    //center and leave
    turnCall(-25);
    driveCall(24);

    //mid push (last)
    turnCall(-90);
    driveCall(16); // move to center
    wingsSolenoid2.set_value(true);
    wingsSolenoid.set_value(true);
    intakePiston.set_value(true);
    turnCall(-90);
    moveDriveMotors(127,0);
    delay(900);

    //center and leave
    moveDriveMotors(100,0);
    delay(80);
    turnCall(0);
    wingsSolenoid2.set_value(false);
    wingsSolenoid.set_value(false);
    //*/
    driveCall(-7);
    
    //face edge and move
    turnCall(90);
    ptoSwitcher(PTO);
    position = 1; //lift up    
    driveCall(-100);
    turnCall(90);
    driveCall(38,2,12);
    moveDriveMotors(127,0);
    delay(300);
    moveDriveMotors(-20,0);
    delay(200);
    moveDriveMotors(0,0);
    position = 10;


}

void skillsAutoBackup1(){
///*
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
    moveDriveSideMotors(127, 127);
    delay(600);
    moveDriveSideMotors(0, 0);
    intMotor.brake();

    //back off, turn
    driveCall(-12);
    //AIM HERE -----------------
    turnCall(70);
    driveCall(3);
    //prepare to shoot
    backRight.set_value(true);
    intakePiston.set_value(false);
    //autoCata = true;
    cataMotor = 120;
    skillsCataVariable = true;
    rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    delay(25000); //25!! ----------------------------------
    delay(2000);
    backRight.set_value(false);
    delay(500);
    rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    skillsCataVariable = false;
    cataRunner = true;
    driveCall(15);
    cataRunner = false;
    turnCallAbsolute(35);
    intMotor = -127;
    driveCall(41);
    turnCallAbsolute(-90);
    moveDriveMotors(-127,0);
    delay(1200);
    intMotor.brake();
    //backRight.set_value(true);
    //backLeft.set_value(true);

    //first push
    moveDriveMotors(-60,0);
    delay(1500);
    moveDriveMotors(127,0);
    delay(80);

    //recenter and leave
    turnCall(0);
    driveCall(30);

    //turn and move
    turnCall(-90);
    driveCall(24);

    //aim and push (second)
    turnCall(70);
    backRight.set_value(true);
    backLeft.set_value(true);     
    driveCall(-34.5);
    backRight.set_value(false);
    backLeft.set_value(false);

    //leave
    moveDriveMotors(127,0);
    delay(80);
    turnCall(20);
    driveCall(30);
    turnCall(90);

    //across, aim and push (third)
    driveCall(40);
    turnCall(-70);
    backRight.set_value(true);
    backLeft.set_value(true);     
    driveCall(-34.5);
    backRight.set_value(false);
    backLeft.set_value(false);
    moveDriveMotors(127,0);
    delay(80);

    //center and leave
    turnCall(-20);
    driveCall(24);

    //mid push (last)
    turnCall(-90);
    driveCall(15);
    wingsSolenoid2.set_value(true);
    wingsSolenoid.set_value(true);
    turnCall(-90);
    driveCall(28);

    //center and leave
    moveDriveMotors(127,0);
    delay(80);
    turnCall(0);
    wingsSolenoid2.set_value(false);
    wingsSolenoid.set_value(false);
    //*/
    driveCall(-7);
    
    //face edge and move
    turnCall(90);
    ptoSwitcher(PTO);
    position = 1; //lift up    
    driveCall(-60);
    turnCall(90);
    driveCall(38,2,12);
    moveDriveMotors(100,0);
    delay(300);
    moveDriveMotors(0,0);
    position = 10;

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

void skillsDriverMacro(){
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
    //autoCata = false; 
    cataRunner = false;

}

void nearsideSafeAWP(){
    intakePiston.set_value(false);
    cataRunner = true;
    intMotor = 127;
    delay(200);
    cataRunner = false;
    intMotor.brake();

    driveCall(16);
    intakePiston.set_value(true);
    turnCall(45);
    driveCall(17);
    turnCall(0);
    delay(100);
    driveCall(-15,1,15);
    turnCall(-45);
    backLeft.set_value(true);
    driveCall(-12);
    backLeft.set_value(false);
    driveCall(-10);
    turnCall(-45);
    driveCall(-35.5,1,15);
}

void nearsideBallrushAWP(){
    gyro.set_rotation(14);
    absoluteAngle = 14;
    intakePiston.set_value(false);
    // wingsSolenoid2.set_value(true);
    // delay(800);
    // wingsSolenoid2.set_value(false);
    intMotor = 127;
    driveCall(46);
    delay(100);
    driveCall(-46);
    intMotor.brake();
    turnCallAbsolute(120);
    intMotor = -127;
    intakePiston.set_value(true);
    delay(200);
    driveCall(-24,0.5,12);
    turnCallAbsolute(160);
    driveCall(-10,1,12);
    turnCallAbsolute(180);
    driveCall(-18);

    driveCall(13,1,15);
    turnCall(-200,1.5);
    driveCall(-5);
    turnCall(-25);
    backLeft.set_value(true);
    driveCall(-10);
    backLeft.set_value(false);

    driveCall(-6);
    turnCall(-40);
    driveCall(-13);
    turnCall(-5);
    backRight.set_value(true);
    driveCall(-20);
    backRight.set_value(false);
    intMotor.brake();
}

void nearSideBallrushElims(){
    gyro.set_rotation(14);
    absoluteAngle = 14;
    intakePiston.set_value(false);
    // wingsSolenoid2.set_value(true);
    // delay(800);
    // wingsSolenoid2.set_value(false);
    intMotor = 127;
    driveCall(46);
    delay(100);
    driveCall(-46);
    intMotor.brake();
    turnCallAbsolute(120);
    intMotor = -127;
    //
    intakePiston.set_value(true);
    delay(200);
    driveCall(-26,1,12);
    turnCallAbsolute(180);
    driveCall(-18);

    driveCall(15,1,15);
    turnCall(-225,1.5);
    backLeft.set_value(true);
    driveCall(-10);
    backLeft.set_value(false);

    driveCall(-6);
    turnCall(-40);
    driveCall(-13);
    turnCall(-15);
    backRight.set_value(true);
    driveCall(-22);
    backRight.set_value(false);
    intMotor.brake();

    //end part
    driveCall(28);
    turnCallAbsolute(-45);
    driveCall(40);
    backRight.set_value(true);    
    turnCall(135);
}

void farSideAutoUnlucky(){
    gyro.set_rotation(-14);
    absoluteAngle = -14;
    intakePiston.set_value(false);
    intMotor = 127;
    driveCall(48);
    delay(100);
    driveCall(-5);
    wingsSolenoid2.set_value(true);
    turnCallAbsolute(90);
    intMotor.brake();
    driveCall(28);
    driveCall(-24);
    turnCall(135);
    intMotor = 127;
    driveCall(12);
    delay(100);
    driveCall(-6);
    turnCall(90);
    driveCall(-60);
    turnCall(135);
}

void farSideAuto(){
    moveDriveMotors(-127,0);
    delay(2000);
    driveCall(10);
    moveDriveMotors(-127,0);
    delay(2000);
}
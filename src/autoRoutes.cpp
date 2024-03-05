#include "main.h"
#include "pros/llemu.hpp"
#include "pros/screen.h"


ASSET(skills_path0_txt);
ASSET(skills_path1_txt);
ASSET(skills_path2_txt);
ASSET(skills_path3_txt);
ASSET(skills_path3_1_txt);
ASSET(skills_path4_txt);
ASSET(skills_path5_txt);
ASSET(skills_path6_txt);
ASSET(skills_path10_txt);
ASSET(skills_path11_txt);
ASSET(skills_path30_txt);
ASSET(skills_path31_txt);
ASSET(skills_path32_txt);
ASSET(skills_path33_txt);

ASSET(rs_safe_path00_txt);
ASSET(rs_safe_path01_txt);
ASSET(rs_safe_path10_txt);
ASSET(rs_safe_path20_txt);

ASSET(rs_rush_path00_txt);
ASSET(rs_rush_path01_txt);
ASSET(rs_rush_path02_txt);
ASSET(rs_rush_path10_txt);
ASSET(rs_rush_path11_txt);

ASSET(ls_rush_path00_txt);
ASSET(ls_rush_path01_txt);
ASSET(ls_rush_path10_txt);
ASSET(ls_rush_path20_txt);
ASSET(ls_rush_path30_txt);

void testingAuto2(int i) {
    if (i == 1){
    chassis.turnTo(100, 0, 1000); // turn to the point (53, 53) with a timeout of 1000 ms
    delay(2000);
    chassis.turnTo(-100, 0, 1000); // turn to the point (-20, 32) with the back of the robot facing the point, and a timeout of 1500 ms
    delay(2000);
    chassis.turnTo(0, 10, 2000); // turn to the point (10, 0) with a timeout of 1000 ms, and a maximum speed of 50
    }
    else if (i == 2){
    chassis.moveToPoint(24, 24, 1000); // move to the point (53, 53) with a timeout of 1000 ms
    delay(2000);
    chassis.moveToPoint(10, 0, 1000, 50);// move to the point (10, 0) with a timeout of 1000 ms, and a maximum speed of 50
    }
    else if (i == 3){
        std::cout<<"first"<<std::endl;
        chassis.moveToPoint(0,10,1000);
        delay(1000);
        chassis.moveToPoint(0,0,1000,false);
        delay(1000);
        chassis.moveToPoint(0,24,1000);
        delay(1000);
        chassis.moveToPoint(0,0,1000,false);
    }
    else if (i == 4){
        chassis.setPose(24,0,180); // temp start pos
        chassis.moveToPoint(24,-10,700);
        chassis.turnTo(43,-58,800);
        chassis.moveToPoint(43,-58,1300);
        chassis.turnTo(56,-48,1000);
        chassis.follow(skills_path10_txt,10,2000);
        chassis.moveToPoint(63,-40,1000,false);
        chassis.moveToPoint(63,-24,1000);
        chassis.moveToPoint(63,-40,1000,false);
        chassis.turnTo(36,-60,1000);
        wingsSolL.set_value(false);
        chassis.follow(skills_path11_txt,25,2000);
        hangSol1.set_value(true);
        hangSol2.set_value(true);
        while (gyro.get_roll() > -10) {
            pros::delay(10);
        }
        hangSol1.set_value(false);
        hangSol2.set_value(false);
    }
  }

void mainAuton(int i) {
    if (i == 0) { // skills
        chassis.setPose(-47.302,-53.365,0); // skills start pos
        chassis.follow(skills_path0_txt,15, 1400); // push balls in
        chassis.follow(skills_path1_txt,6, 1200,false); // move to center
        pros::delay(100);
        chassis.turnTo(43,5,1000,true, 127,false); // aim
        backRight.set_value(true);
        catapult(true);
        lMotor1.set_brake_mode(MOTOR_BRAKE_BRAKE);
        lMotor2.set_brake_mode(MOTOR_BRAKE_BRAKE);
        lMotor3.set_brake_mode(MOTOR_BRAKE_BRAKE);
        rMotor1.set_brake_mode(MOTOR_BRAKE_BRAKE);
        rMotor2.set_brake_mode(MOTOR_BRAKE_BRAKE);
        rMotor3.set_brake_mode(MOTOR_BRAKE_BRAKE);
        pros::delay(21000); // 21000 <===================
        lMotor1.set_brake_mode(MOTOR_BRAKE_COAST);
        lMotor2.set_brake_mode(MOTOR_BRAKE_COAST);
        lMotor3.set_brake_mode(MOTOR_BRAKE_COAST);
        rMotor1.set_brake_mode(MOTOR_BRAKE_COAST);
        rMotor2.set_brake_mode(MOTOR_BRAKE_COAST);
        rMotor3.set_brake_mode(MOTOR_BRAKE_COAST);
        catapult(false);
        backRight.set_value(false);
        chassis.moveToPoint(-14,-28,1000); // back
        //chassis.follow(skills_path2_txt,15,1200,true,false);
        intMotor = -127;
        chassis.moveToPoint(-10,43.5,2200,true,90); // big push
        wingsSolL.set_value(true);
        chassis.moveToPoint(-10,30 ,7000,false); // back for second push
        chassis.moveToPoint(-10,43.5,500,true,127,false);
        chassis.moveToPoint(-12,35,500,false); // back

        chassis.turnTo(-60,42,600,true,127);
        intMotor = 0;
        catapult(true);
        delay(350);
        catapult(false);
        wingsSolL.set_value(false); 
        cataMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
        cataMotor2.set_brake_mode(MOTOR_BRAKE_BRAKE);
        chassis.moveToPoint(-60,40,1400);
        chassis.turnTo(-48,70,900);
        chassis.follow(skills_path3_txt,15,2000,true,false); // curve to alley
        
        //chassis.setPose(16,60,90); //temp
        intMotor = -127;
        lemlib::Pose pose = chassis.getPose();
        chassis.setPose(pose.x,pose.y-2,pose.theta); // scuffed !!
        intMotor = 0;
        chassis.moveToPoint(33,66,2000); // across
        delay(500);
        wingsSolR.set_value(true);
        chassis.follow(skills_path3_1_txt,15,2000);
        delay(500);
        intMotor = -127;
        wingsSolR.set_value(false);
        chassis.moveToPoint(55,51,1500,false,127,false); // back up 1 
        chassis.follow(skills_path3_1_txt,15,1500); //push again
        //moveDriveMotors(127,0);delay(1000);moveDriveMotors(0,0); // push
        cataMotor.set_brake_mode(MOTOR_BRAKE_COAST);
        cataMotor2.set_brake_mode(MOTOR_BRAKE_COAST);
        chassis.moveToPoint(56,44,1300,false); // back up
        intMotor = 0;
        chassis.turnTo(16,37,800); // face mid
        chassis.moveToPoint(16,36,1500,true,80);
        //anchor
        chassis.turnTo(16,16,700);
        lemlib::Pose pose2 = chassis.getPose();
        chassis.setPose(pose2.x,pose2.y-2,pose2.theta); // scuffed pt2!!

        chassis.moveToPoint(14,20,1000,true,80);
        chassis.turnTo(48,12,600);
        chassis.moveToPoint(48,12,1000);
        wingsSolL.set_value(true);
        chassis.follow(skills_path30_txt,15,1400,false);
        chassis.follow(skills_path31_txt,25,2000,true,false);
        lemlib::Pose pose3 = chassis.getPose();
        chassis.setPose(40,-7,pose3.theta); // scuffed pt3!!
        chassis.follow(skills_path32_txt,15,1400,false,false);
        chassis.follow(skills_path33_txt,25,2500,true,false);
        lemlib::Pose pose4 = chassis.getPose();
        chassis.setPose(40,-12,pose4.theta); // scuffed pt4!!
        // chassis.turnTo(12,24,800,false);
        // chassis.moveToPoint(12,24,1000,false);
        // chassis.turnTo(12,0,800);
        // chassis.moveToPoint(12,0,1000);
        // chassis.turnTo(48,0,800);
        // chassis.moveToPoint(48,4,1000);
        // chassis.turnTo(12,0,800,false);
        // chassis.moveToPoint(12,0,1000,false);
        // chassis.turnTo(12,-12,800);
        // chassis.moveToPoint(12,-12,1000);
        // chassis.turnTo(48,-12,800);
        // chassis.moveToPoint(48,-9,1000);

        // hang
        chassis.moveToPoint(24,-10,1500,false);
        chassis.turnTo(45,-58,800);
        chassis.moveToPoint(45,-58,1600,true,80);
        wingsSolL.set_value(false);
        chassis.turnTo(56,-48,1000,true,80);
        chassis.follow(skills_path10_txt,10,2000);
        chassis.moveToPoint(63,-40,1000,false);
        chassis.moveToPoint(63,-24,1000);
        chassis.moveToPoint(63,-40,1000,false);
        return;
        chassis.turnTo(36,-60,1000);
        chassis.follow(skills_path11_txt,25,2000);
        hangSol1.set_value(true);
        hangSol2.set_value(true);
        while (gyro.get_roll() > -5) {
            pros::delay(10);
        }
        hangSol1.set_value(false);
        hangSol2.set_value(false);
        return;

        chassis.turnTo(18,23,800); // face to push in
        chassis.follow(skills_path4_txt,15,1800);
        chassis.moveToPoint(34,16,1000,false); // back up and turn away
        chassis.turnTo(24,24,800);
        chassis.follow(skills_path5_txt,15,1800);
        chassis.turnTo(48,0,800,true,110,false);
        wingsSolL.set_value(true);
        chassis.moveToPoint(50,0,2000,true,90);
        // second push
        chassis.moveToPoint(34,4,1000,false); // back up and turn away
        chassis.turnTo(24,12,800);
        chassis.follow(skills_path6_txt,15,1800);
        chassis.turnTo(48,-12,800,true,110,false);
        wingsSolL.set_value(true);
        chassis.moveToPoint(50,-12,2000,true,90);
        std::cout<<(getTime(AUTOTIMER))<<std::endl;

    }
    else if (i == 1) // safe 6 ball
    {
        chassis.setPose(12,-60,-90);
        intMotor = -127;
        moveDriveMotors(-90,0);
        delay(150);
        chassis.moveToPoint(6,-60,500);
        intMotor = 127;
        chassis.follow(rs_safe_path00_txt,15,2000,false,false);
        backLeft.set_value(true);
        intMotor = 0;
        chassis.moveToPoint(50,-49,1000,false,50,false);
        backLeft.set_value(false);
        chassis.follow(rs_safe_path01_txt,15,1000,false); // curve push
        chassis.moveToPoint(56,-40,1000);
        chassis.turnTo(64,-17,1000,true,127,false);
        intMotor = -127;
        delay(200);
        chassis.moveToPoint(64,-24,800); // push in
        chassis.moveToPoint(55,-42,1000,false);
        chassis.turnTo(3,-24,1000);
        chassis.moveToPoint(9,-29,2000,true);
        intMotor = 127;
        chassis.turnTo(27,-17,1000,true,127,false);
        chassis.moveToPoint(27,-17,1000,true,127,false); // first ball
        intMotor = -127;
        delay(800);
        intMotor = 127; // ??
        chassis.follow(rs_safe_path20_txt,15,1500,false);
        chassis.turnTo(5,0,1000);

        chassis.moveToPoint(8,-4,1000,true,100);
        chassis.turnTo(48,-10,1000,true,127,false);
        wingsSolL.set_value(true); 
        wingsSolR.set_value(true);
        intMotor = -127;
        chassis.moveToPoint(48,-8,1000);
    }
    else if (i == 2) {// safe l awp 
        chassis.setPose(-48,-55,-45);

    }
    else if (i == 3) { // rush l awp
        //chassis.setPose(-40,-54,0);
        chassis.setPose(-38,-55,19.5);
        //chassis.follow(ls_rush_path00_txt,30,1500);
        intMotor = 127;
        chassis.moveToPoint(-26,-11,1500,true,127,false);
        pros::delay(200);
        chassis.follow(ls_rush_path01_txt,25,1500,false,false);
        intMotor = 0;
        chassis.turnTo(0,-65,1000,true,127,false);
        intMotor = -127;
        delay(400);
        chassis.follow(ls_rush_path10_txt,15,1500,false,false);
        chassis.follow(ls_rush_path20_txt,15,1500);
        delay(500);
        backRight.set_value(true);
        chassis.turnTo(10,-30,1000,true,90,false);
        backRight.set_value(false);
        chassis.turnTo(0,-70,1000);
        chassis.follow(ls_rush_path30_txt,15,1500,true);
        pros::delay(1500);
        chassis.moveToPoint(-51,-50,1500,false,100,false);
        wingsSolL.set_value(true);
        wingsSolR.set_value(true);
        chassis.turnTo(-34,-68,1000);
        return;
    }
    else if (i == -1) { // macro
        chassis.setPose(-47.302,-53.365,0); // skills start pos
        chassis.follow(skills_path0_txt,15, 1400); // push balls in
        chassis.follow(skills_path1_txt,6, 1200,false); // move to center
        pros::delay(100);
        chassis.turnTo(43,5,1000,true, 127,false); // aim
        backRight.set_value(true);
        catapult(true);
        lMotor1.set_brake_mode(MOTOR_BRAKE_BRAKE);
        lMotor2.set_brake_mode(MOTOR_BRAKE_BRAKE);
        lMotor3.set_brake_mode(MOTOR_BRAKE_BRAKE);
        rMotor1.set_brake_mode(MOTOR_BRAKE_BRAKE);
        rMotor2.set_brake_mode(MOTOR_BRAKE_BRAKE);
        rMotor3.set_brake_mode(MOTOR_BRAKE_BRAKE);
        pros::delay(21000); // 21000 <===================
        lMotor1.set_brake_mode(MOTOR_BRAKE_COAST);
        lMotor2.set_brake_mode(MOTOR_BRAKE_COAST);
        lMotor3.set_brake_mode(MOTOR_BRAKE_COAST);
        rMotor1.set_brake_mode(MOTOR_BRAKE_COAST);
        rMotor2.set_brake_mode(MOTOR_BRAKE_COAST);
        rMotor3.set_brake_mode(MOTOR_BRAKE_COAST);
        catapult(false);
        backRight.set_value(false);
    }
    else if (i == 4) { // rush 6ball
        chassis.setPose(36,-54,0);
        moveDriveMotors(-90,0);
        delay(100);
        intMotor = 127;
        wingsSolR.set_value(true);
        delay(100);
        wingsSolR.set_value(false);
        chassis.follow(rs_rush_path00_txt,15,1000,true,false);
        delay(200);
        chassis.follow(rs_rush_path01_txt,15,1500,false,false);
        intMotor = -127;
        delay(400);
        chassis.turnTo(24,-60,600,true,127,false);
        intMotor = 127;
        chassis.follow(rs_rush_path02_txt,15,1500,true,false);
        delay(200);
        chassis.follow(rs_rush_path10_txt,15,1500,false);
        delay(1000);
        backLeft.set_value(true);
        intMotor = 0;
        delay(200);
        backLeft.set_value(false);
        chassis.moveToPoint(60,-44,1000);
        chassis.turnTo(64,-17,600,true,127,false);
        intMotor = -127;
        delay(150);
        chassis.moveToPoint(64,-24,800); // push in
        chassis.follow(rs_rush_path11_txt,15,1500,false);
        // chassis.moveToPoint(55,-42,1000,false);
        // chassis.turnTo(3,-24,1000);
        chassis.moveToPoint(9,-29,2000,true);
        intMotor = 127;
        chassis.turnTo(48,-10,600,true,127,false);
        intMotor = -127;
        delay(400);
        intMotor = 127; // ??
        chassis.follow(rs_safe_path20_txt,15,1500,false);
        chassis.turnTo(5,0,1000);

        chassis.moveToPoint(8,-4,1000,true,100);
        chassis.turnTo(48,-10,1000,true,127,false);
        wingsSolL.set_value(true); 
        wingsSolR.set_value(true);
        intMotor = -127;
        chassis.moveToPoint(48,-8,1000);
    }
}



/**/
// void testingAuto() {
//     /*
//     turnCall(45);
//     turnCall(-45);
//     turnCall(90);
//     turnCall(-90);*/

//     driveCall(24);
// }
// void testingAutoe(){
//     driveCall(2);
//     delay(500);
//     driveCall(-2);
//     delay(500);
//     driveCall(4);
//     delay(500);
//     driveCall(-4);
//     delay(500);
//     driveCall(8);
//     delay(500);
//     driveCall(-8);
//     delay(500);
//     driveCall(12);
//     delay(500);
//     driveCall(-12);
//     delay(500);
//     driveCall(16);
//     delay(500);
//     driveCall(-16);
//     delay(500);
//     driveCall(20);
//     delay(500);
//     driveCall(-20);
//     delay(500);
//     driveCall(24);
//     delay(500);
//     driveCall(-24);
//     delay(500);
//     driveCall(30);
//     delay(500);
//     driveCall(-30);
//     delay(500);
//     driveCall(40);
//     delay(500);
//     driveCall(-40);
//     delay(500);
//     driveCall(50);
//     delay(500);
//     driveCall(-50);
//     delay(500);

// }

// void skillsAuto() {
//     ///*
//     intakePiston.set_value(false);
//     cataRunner = true;
//     intMotor = 127;
//     delay(100);
//     cataRunner = false;
//     turnCall(-32);
//     intMotor.brake();
//     driveCall(20);
//     turnCall(32);

//     //push in
//     intakePiston.set_value(true);
//     intMotor = -127;
//     moveDriveSideMotors(127, 127);
//     delay(600);
//     moveDriveSideMotors(0, 0);
//     intMotor.brake();

//     //back off, turn
//     driveCall(-12);
//     //AIM HERE -----------------
//     turnCall(72.5);
//     driveCall(3);
//     //prepare to shoot
//     backRight.set_value(true);
//     intakePiston.set_value(false);
//     //autoCata = true;
//     cataRunner = true;
//     rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
// 	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
// 	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
// 	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
//     delay(25000); //25!! ----------------------------------
//     delay(2000);
//     backRight.set_value(false);
//     delay(500);
//     rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
// 	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
// 	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
// 	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
//     intMotor = -127;
//     cataRunner = true;
//     driveCall(15);
//     cataRunner = false;
//     turnCallAbsolute(35);
//     driveCall(41);
//     turnCallAbsolute(-90);

//     //over the bar
//     moveDriveMotors(-127,0);
//     //delay(1200);
//     startTimer(3);
//     while (fabs(gyro.get_roll())<=5&&getTime(3)<1600){
//         delay(10);
//     }
//     std::cout<<"OVER 5 ROLL"<<std::endl;
//     while (fabs(gyro.get_roll())>5&&getTime(3)<1600){
//         delay(10);
//     }
//     std::cout<<"UNDER 5 ROLL"<<std::endl;
//     while (fabs(gyro.get_roll())<=5&&getTime(3)<1600){
//         delay(10);
//     }
//     std::cout<<"OVER 5 ROLL"<<std::endl;
//     while (fabs(gyro.get_roll())>5&&getTime(3)<1600){
//         delay(10);
//     }
//     std::cout<<"UNDER 5 ROLL"<<std::endl;
//     delay(100);
//     intMotor.brake();
//     moveDriveMotors(100,0);
//     delay(700);
//     gyro.set_rotation(-90);
//     delay(100);
//     //backRight.set_value(true);
//     //backLeft.set_value(true);

//     //first push
//     moveDriveMotors(-60,0);
//     delay(1650);
//     moveDriveMotors(100,0);
//     delay(80);

//     //recenter and leave
//     turnCall(0);
//     driveCall(30);

//     //turn and move
//     turnCall(-90);
//     driveCall(28);

//     //aim and push (second)
//     turnCall(65);
//     backRight.set_value(true);
//     backLeft.set_value(true);     
//     driveCall(-34.5);
//     backRight.set_value(false);
//     backLeft.set_value(false);

//     //leave
//     moveDriveMotors(127,0);
//     delay(80);
//     turnCall(25);
//     driveCall(30);
//     turnCall(90);

//     //across, aim and push (third)
//     driveCall(46);
//     turnCall(-65);
//     backRight.set_value(true);
//     backLeft.set_value(true);     
//     driveCall(-35);
//     backRight.set_value(false);
//     backLeft.set_value(false);
//     moveDriveMotors(127,0);
//     delay(80);

//     //center and leave
//     turnCall(-25);
//     driveCall(24);

//     //mid push (last)
//     turnCall(-90);
//     driveCall(16); // move to center
//     wingsSolenoid2.set_value(true);
//     wingsSolenoid.set_value(true);
//     intakePiston.set_value(true);
//     turnCall(-90);
//     moveDriveMotors(127,0);
//     delay(900);

//     //center and leave
//     moveDriveMotors(100,0);
//     delay(80);
//     turnCall(0);
//     wingsSolenoid2.set_value(false);
//     wingsSolenoid.set_value(false);
//     //*/
//     driveCall(-7);
    
//     //face edge and move
//     turnCall(90);
//     ptoSwitcher(PTO);
//     position = 1; //lift up    
//     driveCall(-100);
//     turnCall(90);
//     driveCall(38,2,12);
//     moveDriveMotors(127,0);
//     delay(300);
//     moveDriveMotors(-20,0);
//     delay(200);
//     moveDriveMotors(0,0);
//     position = 10;


// }

// void skillsAutoBackup1(){
// ///*
//     intakePiston.set_value(false);
//     cataRunner = true;
//     intMotor = 127;
//     delay(100);
//     cataRunner = false;
//     turnCall(-32);
//     intMotor.brake();
//     driveCall(20);
//     turnCall(32);

//     //push in
//     intakePiston.set_value(true);
//     intMotor = -127;
//     moveDriveSideMotors(127, 127);
//     delay(600);
//     moveDriveSideMotors(0, 0);
//     intMotor.brake();

//     //back off, turn
//     driveCall(-12);
//     //AIM HERE -----------------
//     turnCall(70);
//     driveCall(3);
//     //prepare to shoot
//     backRight.set_value(true);
//     intakePiston.set_value(false);
//     //autoCata = true;
//     cataMotor = 120;
//     skillsCataVariable = true;
//     rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
// 	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
// 	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
// 	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
//     delay(25000); //25!! ----------------------------------
//     delay(2000);
//     backRight.set_value(false);
//     delay(500);
//     rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
// 	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
// 	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
// 	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
//     skillsCataVariable = false;
//     cataRunner = true;
//     driveCall(15);
//     cataRunner = false;
//     turnCallAbsolute(35);
//     intMotor = -127;
//     driveCall(41);
//     turnCallAbsolute(-90);
//     moveDriveMotors(-127,0);
//     delay(1200);
//     intMotor.brake();
//     //backRight.set_value(true);
//     //backLeft.set_value(true);

//     //first push
//     moveDriveMotors(-60,0);
//     delay(1500);
//     moveDriveMotors(127,0);
//     delay(80);

//     //recenter and leave
//     turnCall(0);
//     driveCall(30);

//     //turn and move
//     turnCall(-90);
//     driveCall(24);

//     //aim and push (second)
//     turnCall(70);
//     backRight.set_value(true);
//     backLeft.set_value(true);     
//     driveCall(-34.5);
//     backRight.set_value(false);
//     backLeft.set_value(false);

//     //leave
//     moveDriveMotors(127,0);
//     delay(80);
//     turnCall(20);
//     driveCall(30);
//     turnCall(90);

//     //across, aim and push (third)
//     driveCall(40);
//     turnCall(-70);
//     backRight.set_value(true);
//     backLeft.set_value(true);     
//     driveCall(-34.5);
//     backRight.set_value(false);
//     backLeft.set_value(false);
//     moveDriveMotors(127,0);
//     delay(80);

//     //center and leave
//     turnCall(-20);
//     driveCall(24);

//     //mid push (last)
//     turnCall(-90);
//     driveCall(15);
//     wingsSolenoid2.set_value(true);
//     wingsSolenoid.set_value(true);
//     turnCall(-90);
//     driveCall(28);

//     //center and leave
//     moveDriveMotors(127,0);
//     delay(80);
//     turnCall(0);
//     wingsSolenoid2.set_value(false);
//     wingsSolenoid.set_value(false);
//     //*/
//     driveCall(-7);
    
//     //face edge and move
//     turnCall(90);
//     ptoSwitcher(PTO);
//     position = 1; //lift up    
//     driveCall(-60);
//     turnCall(90);
//     driveCall(38,2,12);
//     moveDriveMotors(100,0);
//     delay(300);
//     moveDriveMotors(0,0);
//     position = 10;

// }

// void skillsAuto140()
// {
//     intakePiston.set_value(false);
//     cataRunner = true;
//     intMotor = 127;
//     delay(100);
//     cataRunner = false;
//     turnCall(-32);
//     intMotor.brake();
//     driveCall(20);
//     turnCall(32);

//     //push in
//     intakePiston.set_value(true);
//     intMotor = -127;
//     moveDriveSideMotors(100, 100);
//     delay(600);
//     gyro.tare_rotation();
//     moveDriveSideMotors(0, 0);
//     intMotor.brake();
//     //back off, turn
//     driveCall(-12);
//     turnCall(70);
//     driveCall(3);
//     //prepare to shoot
//     /*
//     intakePiston.set_value(false);
//     moveDriveSideMotors(-50, -50);
//     delay(500);
//     moveDriveSideMotors(100, 100);
//     delay(100);
//     moveDriveSideMotors(0, 0);
//     */
    
//     backRight.set_value(true);
//     intakePiston.set_value(false);
//     //autoCata = true;
//     cataRunner = true;
//     /*moveDriveSideMotors(-50, -50);
//     delay(500);
//     moveDriveSideMotors(-20, -20);
//     delay(500);*/
//     rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
// 	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
// 	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
// 	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
//     delay(25000); //25!! ---------
//     ratchPiston.set_value(false);
//     delay(2000);
//     backRight.set_value(false);
//     delay(500);
//     rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
// 	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
// 	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
// 	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
//     driveCall(3);
//     //autoCata = false; 
//     cataRunner = false;
//     turnCall(240);
//     driveCall(-26);
//     turnCall(-40);

//     //across
//     intakePiston.set_value(true);
//     driveCall(-67);
//     turnCall(-45);

//     //corner
//     driveCall(-20);
//     turnCall(-45);

//     //side push
//     backRight.set_value(true);
//     moveDriveSideMotors(-100, -100);
//     delay(800);
//     moveDriveMotors(100,0);
//     delay(100);
//     turnCall(0);
//     driveCall(15);
//     backRight.set_value(false);
//     backLeft.set_value(false);
//     turnCall(-60);
//     driveCall(-48,1.5,10);
//     turnCall(60);

//     // first push
//     driveCall(-12);
//     backRight.set_value(true);
//     turnCall(90);
//     moveDriveSideMotors(-100, -100);
//     delay(900);
//     backRight.set_value(false);
//     moveDriveSideMotors(70, 70);
//     delay(100);
//     turnCall(0);
//     //leave first push
//     driveCall(24);
//     turnCall(-90);
//     /* last stuff old
//     driveCall(-30);
//     turnCall(-70);
//     wingsSolenoid.set_value(true);
//     wingsSolenoid2.set_value(true);
//     delay(100);
//     moveDriveSideMotors(100, 100);
//     delay(900);
//     moveDriveSideMotors(-100, -100);
//     delay(300);
//     turnCall(-20);
//     moveDriveSideMotors(100, 100);
//     delay(600);
//     wingsSolenoid.set_value(false);
//     wingsSolenoid2.set_value(false);
//     driveCall(-7);
//     turnCall(-90);
//     driveCall(53);
//     turnCall(-70);
//     // side in
//     moveDriveSideMotors(-50, -100);
//     delay(1000);
//     moveDriveSideMotors(100, 100);
//     delay(400);
//     turnCall(50);
//     moveDriveSideMotors(-100, -100);
//     delay(1000);
//     moveDriveSideMotors(100, 100);
//     delay(400);
//     turnCall(0);
//     moveDriveSideMotors(-100, -100);
//     delay(1000);
//     moveDriveSideMotors(100, 100);
//     delay(400);
//     moveDriveSideMotors(0, 0);*/
    
//     //push left
//     driveCall(-38, 1.5, 10);
//     backLeft.set_value(true);
//     turnCall(300);
//     wingsSolenoid.set_value(true);
//     wingsSolenoid2.set_value(true);    
//     delay(200);
//     backLeft.set_value(false);
//     driveCall(20,1.5,10);
//     moveDriveMotors(0,100);
//     delay(100);
//     turnCall(0);
//     wingsSolenoid.set_value(false);
//     wingsSolenoid2.set_value(false);    
//     driveCall(-20);

//     //push middle
//     turnCall(60);
//     driveCall(18);
//     wingsSolenoid.set_value(true);
//     wingsSolenoid2.set_value(true);    
//     turnCall(-90);
//     moveDriveMotors(100,0);
//     delay(1000);
//     moveDriveMotors(-100,0);
//     delay(200);
//     turnCall(0);
//     moveDriveMotors(100,0);
//     delay(1000);
//     moveDriveMotors(-100,0);
//     delay(100);
//     driveCall(-24);

// }

// void skillsAuto2(){
//     intakePiston.set_value(false);
//     cataRunner = true;
//     intMotor = 127;
//     delay(100);
//     cataRunner = false;
//     turnCall(-32);
//     intMotor.brake();
//     driveCall(20);
//     turnCall(32);

//     //push in
//     intakePiston.set_value(true);
//     intMotor = -127;
//     moveDriveSideMotors(100, 100);
//     delay(600);
//     gyro.tare_rotation();
//     moveDriveSideMotors(0, 0);
//     intMotor.brake();
//     //back off, turn
//     driveCall(-12);
//     turnCall(70);
//     driveCall(3);
//     //prepare to shoot
//     backRight.set_value(true);
//     intakePiston.set_value(false);
//     //autoCata = true;
//     cataRunner = true;
//     rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
// 	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
// 	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
// 	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
//     delay(25000); //25!! ---------
//     ratchPiston.set_value(false);
//     delay(2000);
//     backRight.set_value(false);
//     delay(500);
//     rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
// 	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
// 	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
// 	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
//     driveCall(3);
//     //autoCata = false; 
//     cataRunner = false;
//     turnCall(240);
//     driveCall(-24);
//     turnCall(-40);

//     //across
//     intakePiston.set_value(true);
//     driveCall(-67,2.3,7);
//     turnCall(-20);

//     //corner
//     driveCall(-26);
//     turnCall(-70);

//     //side push
//     backRight.set_value(true);
//     moveDriveSideMotors(-100, -100);
//     delay(800);
//     moveDriveMotors(100,0);
//     delay(100);
//     turnCall(0);
//     driveCall(3);
//     backRight.set_value(false);
//     backLeft.set_value(false);
//     turnCall(90);
//     driveCall(44);
//     turnCall(90);

//     // first push
//     driveCall(16);
//     turnCall(-100);
//     moveDriveSideMotors(-100, -100);
//     delay(900);
//     backRight.set_value(false);
//     moveDriveSideMotors(70, 70);
//     delay(100);
//     turnCall(10);
//     //leave first push
//     driveCall(24);
//     turnCall(-90);

//     //push left
//     driveCall(-44);
//     turnCall(-60);
//     delay(200);
//     moveDriveMotors(100,0);//driveCall(20);
//     delay(900);
//     moveDriveMotors(-100,0);
//     delay(50);
//     turnCall(-30);
//     driveCall(-22);

//     //push middle
//     turnCall(90);
//     driveCall(15);
//     wingsSolenoid.set_value(true);
//     wingsSolenoid2.set_value(true);    
//     turnCall(-90);
//     moveDriveMotors(100,0);
//     delay(1000);
//     moveDriveMotors(-100,0);
//     delay(200);
//     turnCall(0);
//     moveDriveMotors(100,0);
//     delay(1000);
//     moveDriveMotors(-100,0);
//     delay(100);
//     driveCall(-24);

// }

// void skillsDriverMacro(){
// intakePiston.set_value(false);
//     cataRunner = true;
//     intMotor = 127;
//     delay(100);
//     cataRunner = false;
//     turnCall(-32);
//     intMotor.brake();
//     driveCall(20);
//     turnCall(32);

//     //push in
//     intakePiston.set_value(true);
//     intMotor = -127;
//     moveDriveSideMotors(100, 100);
//     delay(600);
//     gyro.tare_rotation();
//     moveDriveSideMotors(0, 0);
//     intMotor.brake();
//     //back off, turn
//     driveCall(-12);
//     turnCall(70);
//     driveCall(3);
//     //prepare to shoot
//     /*
//     intakePiston.set_value(false);
//     moveDriveSideMotors(-50, -50);
//     delay(500);
//     moveDriveSideMotors(100, 100);
//     delay(100);
//     moveDriveSideMotors(0, 0);
//     */
    
//     backRight.set_value(true);
//     intakePiston.set_value(false);
//     //autoCata = true;
//     cataRunner = true;
//     /*moveDriveSideMotors(-50, -50);
//     delay(500);
//     moveDriveSideMotors(-20, -20);
//     delay(500);*/
//     rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
// 	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
// 	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
// 	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
//     delay(25000); //25!! ---------
//     ratchPiston.set_value(false);
//     delay(2000);
//     backRight.set_value(false);
//     delay(500);
//     rMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
// 	rMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
// 	lMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
// 	lMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
//     //autoCata = false; 
//     cataRunner = false;

// }

// void nearsideSafeAWP(){
//     intakePiston.set_value(false);
//     cataRunner = true;
//     intMotor = 127;
//     delay(200);
//     cataRunner = false;
//     intMotor.brake();

//     driveCall(16);
//     intakePiston.set_value(true);
//     turnCall(45);
//     driveCall(17);
//     turnCall(0);
//     delay(100);
//     driveCall(-15,1,15);
//     turnCall(-45);
//     backLeft.set_value(true);
//     driveCall(-12);
//     backLeft.set_value(false);
//     driveCall(-10);
//     turnCall(-45);
//     driveCall(-35.5,1,15);
// }

// void nearsideBallrushAWP(){
//     gyro.set_rotation(14);
//     absoluteAngle = 14;
//     intakePiston.set_value(false);
//     // wingsSolenoid2.set_value(true);
//     // delay(800);
//     // wingsSolenoid2.set_value(false);
//     intMotor = 127;
//     driveCall(46);
//     delay(100);
//     driveCall(-46);
//     intMotor.brake();
//     turnCallAbsolute(120);
//     intMotor = -127;
//     intakePiston.set_value(true);
//     delay(200);
//     driveCall(-24,0.5,12);
//     turnCallAbsolute(160);
//     driveCall(-10,1,12);
//     turnCallAbsolute(180);
//     driveCall(-18);

//     driveCall(13,1,15);
//     turnCall(-200,1.5);
//     driveCall(-5);
//     turnCall(-25);
//     backLeft.set_value(true);
//     driveCall(-10);
//     backLeft.set_value(false);

//     driveCall(-6);
//     turnCall(-40);
//     driveCall(-13);
//     turnCall(-5);
//     backRight.set_value(true);
//     driveCall(-20);
//     backRight.set_value(false);
//     intMotor.brake();
// }

// void nearSideBallrushElims(){
//     gyro.set_rotation(14);
//     absoluteAngle = 14;
//     intakePiston.set_value(false);
//     // wingsSolenoid2.set_value(true);
//     // delay(800);
//     // wingsSolenoid2.set_value(false);
//     intMotor = 127;
//     driveCall(46);
//     delay(100);
//     driveCall(-46);
//     intMotor.brake();
//     turnCallAbsolute(120);
//     intMotor = -127;
//     //
//     intakePiston.set_value(true);
//     delay(200);
//     driveCall(-26,1,12);
//     turnCallAbsolute(180);
//     driveCall(-18);

//     driveCall(15,1,15);
//     turnCall(-225,1.5);
//     backLeft.set_value(true);
//     driveCall(-10);
//     backLeft.set_value(false);

//     driveCall(-6);
//     turnCall(-40);
//     driveCall(-13);
//     turnCall(-15);
//     backRight.set_value(true);
//     driveCall(-22);
//     backRight.set_value(false);
//     intMotor.brake();

//     //end part
//     driveCall(28);
//     turnCallAbsolute(-45);
//     driveCall(40);
//     backRight.set_value(true);    
//     turnCall(135);
// }

// void farSideAutoUnlucky(){
//     gyro.set_rotation(-14);
//     absoluteAngle = -14;
//     intakePiston.set_value(false);
//     intMotor = 127;
//     driveCall(48);
//     delay(100);
//     driveCall(-5);
//     wingsSolenoid2.set_value(true);
//     turnCallAbsolute(90);
//     intMotor.brake();
//     driveCall(28);
//     driveCall(-24);
//     turnCall(135);
//     intMotor = 127;
//     driveCall(12);
//     delay(100);
//     driveCall(-6);
//     turnCall(90);
//     driveCall(-60);
//     turnCall(135);
// }

// void farSideAuto(){
//     moveDriveMotors(-127,0);
//     delay(2000);
//     driveCall(10);
//     moveDriveMotors(-127,0);
//     delay(2000);
// }



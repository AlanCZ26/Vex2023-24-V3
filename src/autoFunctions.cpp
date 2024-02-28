#include "main.h"
#include "pros/llemu.hpp"
#include "pros/screen.h"
#include <vector>
bool PTOvar = false;//no drive when false
bool infiniteCata;
bool autoCata;
bool shootCommand;
bool liftVar;
bool cataRunner;

void resetMotorEncoders()
{
    rMotor1.tare_position();
    rMotor2.tare_position();
    rMotor3.tare_position();
    lMotor1.tare_position();
    lMotor2.tare_position();
    lMotor3.tare_position();
}

// double absoluteAngle = 0;
// /**
//  * \param target Target in inches
//  * \param time Time limit in ms
//  */
// void driveDist(double target, double time, double kP, double kI, double kD, double minVal, double intKickin, double intMax, double tkP, double tMinVal)
// {
//     std::cout << "--------MOV-------" << std::endl;
//     std::cout <<"Starting time: " << (getTime(AUTOTIMER)) << "ms" <<std::endl;
//     std::cout << "Target: " << target << std::endl;
//     resetMotorEncoders();
//     startTimer(0);
//     double error = 10;
//     double integral = 0;
//     double derivative;
//     double measure;
//     double prevError = error;
//     double output;
//     double errorRot;
//     double lOut;
//     double rOut;
//     double endVariable = fabs(target);
//     while (fabs(endVariable) > 0.5 && time >= getTime(0))
//     {
//         measure = (((lMotor2.get_position() + rMotor2.get_position())) * 0.002127120025868);
//         error = target - measure;
//         if (fabs(integral) <= intMax)
//             integral += error;
//         if (fabs(error) <= 4) 
//             derivative = error - prevError;
//         else
//             derivative = 0;
        
//         prevError = error;

//         errorRot = (gyro.get_rotation() - absoluteAngle) * tkP;

//         output = (error * kP) + (integral * kI) + (derivative * kD);

//         if (lOut > 0 && lOut < minVal)
//             lOut = minVal;
//         if (lOut < 0 && lOut > -minVal)
//             lOut = -minVal;
//         if (rOut > 0 && rOut < minVal)
//             rOut = minVal;
//         if (rOut < 0 && rOut > -minVal)
//             rOut = -minVal;
//         if (errorRot > 0 && errorRot < tMinVal)
//             errorRot = tMinVal;
//         if (errorRot < 0 && errorRot > -tMinVal)
//             errorRot = -tMinVal;

//         if (output > 13) {output = 13;}
//         if (output < -13) {output = -13;}
//         lOut = (output - errorRot) * 10; // 10x bc we used volts before :P
//         rOut = (output + errorRot) * 10;            

//         moveDriveSideMotors(lOut, rOut);
//         pros::screen::print(TEXT_MEDIUM, 1, "error: %f", error);
//         pros::screen::print(TEXT_MEDIUM, 2, "power: %f", lOut);
//         pros::screen::print(TEXT_MEDIUM, 3, "enc: %f", lMotor1.get_position());
        
//         //std::cout << getTime(0) << "MS  |  " << ((floorf(error*100.0))/100.0) << " Err  |  " << ((floorf(lOut*100.0))/100.0) << " Out  |  " << std::endl;

//         pros::delay(10);
//         endVariable = (endVariable * 2 + fabs(error))/3;
//     }
//     if (time < getTime(0)){std::cout <<"   ============="<<std::endl<<"     TIMED OUT" << std::endl<<"     ("<<getTime(0)<<"ms)"<<std::endl<<"   ============="<<std::endl;}
//     else std::cout << "TOOK " << getTime(0) << "MS" << std::endl;
//     std::cout << "Ending distance: " << measure << std::endl;
//     std::cout << "--------END-------" << std::endl << std::endl;
//     moveDriveMotors(0, 0);
//     pros::delay(10);
//     pros::screen::print(TEXT_MEDIUM, 1, "-end-");
// }

// void driveCall(double target)
// {
//     double time = 800;
//     double kP = 2;
//     double kI = 0; 
//     double kD = 7; 
//     double minVal = 2; 
//     double intKickin = 0;
//     double intMax = 5; 
//     double tkP = 0.5;
//     double tMinVal = 1;
    
//     if (fabs(target)< 10) {
//         time = 600;
//         minVal = 3.5;
//         kP = 2.5;
//     }
//     if (fabs(target)<5) {
//         minVal = 4;
//         kP = 3.5;
//     }
//     if (fabs(target) > 18) {
//         time = 1000;
//     }
//     if (fabs(target) >= 36) {
//         time = 1600;
//         kP = 2;
//         kD = 7;
//     }
//     if (fabs(target>=48)){
//         time = 2000;
//     }
//     if (fabs(target)>60) {
//         time = 3000;
//     }
    
//     driveDist(target, time, kP, kI, kD, minVal, intKickin, intMax, tkP, tMinVal);
// }

// void driveCall(double target, double kP, double kD)
// {
//     double time = 1000;
//     double kI = 0; 
//     double minVal = 2.5; 
//     double intKickin = 0;
//     double intMax = 5; 
//     double tkP = kP/6;
//     double tMinVal = 1.5;
//     if (fabs(target) > 24) {
//         time = 1500;
//     }
//     driveDist(target, time, kP, kI, kD, minVal, intKickin, intMax, tkP, tMinVal);
// }

// void turnCallAbsolute(double target)
// {
//     absoluteAngle = target;
//     turnCall(0);
// }

// void turnCall(double targetAngle)
// {
//     double time = 1000;
//     double kP = 2.5;
//     double kI = 0;
//     double kD = 12;
//     double integralKickin = 5;
//     double minVal = 18;
//     /*if (fabs(targetAngle) > 60) {
//         time = 2500;
//         kP = 4;
//         kD = 2;
//     }*/
//     if (fabs(targetAngle) < 35) {
//         kP = 2.7;
//         minVal = 25;
//     }
//     if (fabs(targetAngle > 100)){
//         time = 1500;
//     }
//     if (fabs(targetAngle) > 200) {
//         time = 2300;
//         minVal = 20;
//     }
//     turn(targetAngle, time, kP, kI, kD, integralKickin, minVal);
// }
// // pros terminal --no-banner | tee output.txt 
// void turnCall(double targetAngle, double kP)
// {
//     double time = 1000;
//     double kI = 0;
//     double kD = 12;
//     double integralKickin = 5;
//     double minVal = 18;
//     /*if (fabs(targetAngle) > 60) {
//         time = 2500;
//         kP = 4;
//         kD = 2;
//     }*/
//     if (fabs(targetAngle) < 35) {
//         kP = 2.7;
//         minVal = 25;
//     }
//     if (fabs(targetAngle > 100)){
//         time = 1500;
//     }
//     if (fabs(targetAngle) > 200) {
//         time = 2300;
//         minVal = 20;
//     }
//     turn(targetAngle, time, kP, kI, kD, integralKickin, minVal);
// }

// void turn(double targetDegree, double time, double kP, double kI, double kD, double integralKickin, double minVal)
// {
//     std::cout << "--------TRN-------" << std::endl;
//     std::cout <<"Starting time: " << (getTime(AUTOTIMER)) << "ms" <<std::endl;
//     std::cout << "Starting true angle: " << gyro.get_rotation() << std::endl;
//     std::cout << "Target: " << targetDegree << std::endl;
//     absoluteAngle += targetDegree;
//     targetDegree = absoluteAngle;
//     double error = targetDegree - gyro.get_rotation();
//     double integral, derivative, lastError, power, tPower;
//     double endVariable = fabs(error);
//     std::vector<double> outputVector;
//     std::vector<double> readVector;
//     std::vector<double> pVector;
//     std::vector<double> dVector;
//     startTimer(0);
//     while (endVariable >= 1 && time >= getTime(0))
//     {
//         delay(10);
//         error = targetDegree - gyro.get_rotation();
//         //if (fabs(error) <= integralKickin && fabs(integral) < (1.5 / kI))
//         //    integral += error;
//         derivative = error - lastError;
//         lastError = error;
//         tPower = error * kP + integral * kI + derivative * kD;
//         if (tPower > 0 && tPower < minVal)
//             tPower = minVal;
//         if (tPower < 0 && tPower> -minVal)
//             tPower= -minVal;
//         moveDriveMotors(0, tPower);
//         //std::cout <<getTime(0) << "ms, " << tPower << std::endl;
//         outputVector.push_back(tPower);
//         readVector.push_back(error);
//         pVector.push_back(error*kP);
//         dVector.push_back(derivative*kD);
//         endVariable = (endVariable * 4 + fabs(error))/5;
//     }
//     moveDriveMotors(0, 0);
//     /*
//     std::cout<<std::endl<<"Outpt"<<std::endl<<"[";
//     for (int i=0;i<outputVector.size();i++) {
//         std::cout << outputVector.at(i) <<", ";
//         delay(10);
//     }
//     std::cout<<"0]"<<std::endl;

//     std::cout<<std::endl<<"Input"<<std::endl<<"[";
//     for (int i=0;i<readVector.size();i++) {
//         std::cout << readVector.at(i) <<", ";
//         delay(10);
//     }
//     std::cout<<"0]"<<std::endl;

//     std::cout<<std::endl<<"Propr"<<std::endl<<"[";
//     for (int i=0;i<pVector.size();i++) {
//         std::cout << pVector.at(i) <<", ";
//         delay(10);
//     }
//     std::cout<<"0]"<<std::endl;

//     std::cout<<std::endl<<"Deriv"<<std::endl<<"[";
//     for (int i=0;i<dVector.size();i++) {
//         std::cout << dVector.at(i) <<", ";
//         delay(10);
//     }
//     std::cout<<"0]"<<std::endl;
//     */
//     if (time < getTime(0)){std::cout <<"   ============="<<std::endl<<"     TIMED OUT" << std::endl<<"     ("<<getTime(0)<<"ms)"<<std::endl<<"   ============="<<std::endl;}
//     else {std::cout << "TOOK " << getTime(0) << "MS" << std::endl;}
//     std::cout << "Ending true angle: " << gyro.get_rotation() << std::endl;
//     std::cout << "Ending expected angle: " << absoluteAngle << std::endl;
//     std::cout << "--------END-------" << std::endl << std::endl;
//     delay(10);
// }

// // void catapult():
// //     while true:
// //         delay(100)
// //         if (infiniteCata == false){
// //             cataMotor.break()
// //         }
// //         if (controller.buttonUp.pressing()
// //             or (cataDist.object_distance(MM) < 50 and autoCata == True)
// //             or (shootCommand)
// //             or (autoCata == True and stallVariable > 100)):
// //             #if not controller.buttonX.pressing(): wait(0.05,SECONDS)
// //             cataMotor.spin(FORWARD,12,VOLT)
// //             wait(0.3,SECONDS)
// //             timer = 80
// //             while (catapultLoadDist.object_distance(MM) > 90) and timer > 0:
// //                 wait(0.01,SECONDS)
// //                 timer -= 1
// //             if timer == 0:
// //                 cataMotor.spin(REVERSE,12,VOLT)
// //                 wait(0.1,SECONDS)
// //                 cataMotor.stop()
// //             else:
// //                 shootCommand = False
// //             stallVariable = 0

// //int trackerCurrentState = -1;
// // void odomTracker(){
// //     std::vector<double> xVector;
// //     std::vector<double> yVector;
// //     while (true){
// //         if (trackerCurrentState == -1) continue;
// //         else if (trackerCurrentState == 1) { // currently tracking
// //             lemlib::Pose pose = chassis.getPose();
// //             xVector.push_back(pose.x);
// //             yVector.push_back(pose.y);
// //             std::cout<<"test"<<std::endl;
// //         }
// //         else if (trackerCurrentState == 0) {
// //             trackerCurrentState = -1;
// //             xVector.clear();
// //             yVector.clear();
// //             std::cout<<std::endl<<"x"<<std::endl<<"[";
// //             for (int i=0;i<xVector.size();i++) {
// //                 std::cout << xVector.at(i) <<", ";
// //                 delay(10);
// //             }
// //             std::cout<<"0]"<<std::endl;
// //             std::cout<<std::endl<<"y"<<std::endl<<"[";
// //             for (int i=0;i<yVector.size();i++) {
// //                 std::cout << yVector.at(i) <<", ";
// //                 delay(10);
// //             }
// //             std::cout<<"0]"<<std::endl;
// //         }
// //     }
// // }

// void odomDrive(double x, double y, int time){
//     int maxSpeed = 200;
//     //trackerCurrentState = 1;
//     chassis.moveToPoint(x,y,time,maxSpeed);
//     //trackerCurrentState = 0;
// }

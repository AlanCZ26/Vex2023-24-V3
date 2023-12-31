#include "main.h"
#include "pros/llemu.hpp"
#include "pros/screen.h"
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
    lMotor1.tare_position();
    lMotor2.tare_position();
    rtMotor.tare_position();
    ltMotor.tare_position();
}

double absoluteAngle = 0;
/**
 * \param target Target in inches
 * \param time Time limit in ms
 */
void driveDist(double target, double time, double kP, double kI, double kD, double minVal, double intKickin, double intMax, double tkP, double tMinVal)
{
    resetMotorEncoders();
    startTimer(0);
    double error = 10;
    double integral = 0;
    double derivative;
    double measure;
    double prevError = error;
    double output;
    double errorRot;
    double lOut;
    double rOut;
    double endVariable = fabs(target);
    while (fabs(endVariable) > 0.5 && time >= getTime(0))
    {
        measure = (((lMotor1.get_position() + rMotor1.get_position() + lMotor2.get_position() + rMotor2.get_position())) * 0.00425424005);
        error = target - measure;
        if (fabs(integral) <= intMax)
            integral += error;
        if (fabs(error) <= 4) 
            derivative = error - prevError;
        else
            derivative = 0;
        
        prevError = error;

        errorRot = (gyro.get_rotation() - absoluteAngle) * tkP;

        output = (error * kP) + (integral * kI) + (derivative * kD);

        if (lOut > 0 && lOut < minVal)
            lOut = minVal;
        if (lOut < 0 && lOut > -minVal)
            lOut = -minVal;
        if (rOut > 0 && rOut < minVal)
            rOut = minVal;
        if (rOut < 0 && rOut > -minVal)
            rOut = -minVal;
        if (errorRot > 0 && errorRot < tMinVal)
            errorRot = tMinVal;
        if (errorRot < 0 && errorRot > -tMinVal)
            errorRot = -tMinVal;

        lOut = (output - errorRot) * 10; // 10x bc we used volts before :P
        rOut = (output + errorRot) * 10;            

        moveDriveSideMotors(lOut, rOut);
        pros::screen::print(TEXT_MEDIUM, 1, "error: %f", error);
        pros::screen::print(TEXT_MEDIUM, 2, "power: %f", lOut);
        pros::screen::print(TEXT_MEDIUM, 3, "enc: %f", lMotor1.get_position());
        
        //std::cout << getTime(0) << "MS  |  " << ((floorf(error*100.0))/100.0) << " Err  |  " << ((floorf(lOut*100.0))/100.0) << " Out  |  " << std::endl;

        pros::delay(10);
        endVariable = (endVariable * 2 + fabs(error))/3;
    }
    if (time <= getTime(0)) std::cout <<"TIMED OUT" << std::endl;
    else std::cout << "TOOK " << getTime(0) << "MS" << std::endl;
    std::cout << "Ending distance: " << measure << std::endl;
    std::cout << "--------end-------"<<std::endl;
    moveDriveMotors(0, 0);
    pros::delay(10);
    pros::screen::print(TEXT_MEDIUM, 1, "-end-");
}

void driveCall(double target)
{
    double time = 20000;
    double kP = 2;
    double kI = 0; 
    double kD = 7; 
    double minVal = 2; 
    double intKickin = 0;
    double intMax = 5; 
    double tkP = 0.3;
    double tMinVal = 1;
    if (target > 24) {
        time = 50000;
    }
    if (target >= 36) {
        kP = 0.5;
        kD = 12;
    }
    
    driveDist(target, time, kP, kI, kD, minVal, intKickin, intMax, tkP, tMinVal);
}

void driveCall(double target, double kP, double kD)
{
    double time = 20000;
    double kI = 0; 
    double minVal = 2; 
    double intKickin = 0;
    double intMax = 5; 
    double tkP = 0.3;
    double tMinVal = 1.5;
    if (target > 24) {
        time = 50000;
    }
    
    driveDist(target, time, kP, kI, kD, minVal, intKickin, intMax, tkP, tMinVal);
}

void turnCallAbsolute(double target)
{
    absoluteAngle = target;
    turnCall(0);
}

void turnCall(double targetAngle)
{
    double time = 1500;
    double kP = 2.5;
    double kI = 0;
    double kD = 12;
    double integralKickin = 5;
    double minVal = 18;
    /*if (fabs(targetAngle) > 60) {
        time = 2500;
        kP = 4;
        kD = 2;
    }*/
    if (fabs(targetAngle) < 35) {
        kP = 3;
        minVal = 25;
    }
    if (fabs(targetAngle) > 200) {
        kP = 2;
        minVal = 20;
    }
    turn(targetAngle, time, kP, kI, kD, integralKickin, minVal);
}

void turn(double targetDegree, double time, double kP, double kI, double kD, double integralKickin, double minVal)
{
    std::cout << "Starting true angle: " << gyro.get_rotation() << std::endl;
    absoluteAngle += targetDegree;
    targetDegree = absoluteAngle;
    double error = targetDegree - gyro.get_rotation();
    double integral, derivative, lastError, power, tPower;
    double endVariable = fabs(error);
    std::vector<double> outputVector;
    std::vector<double> readVector;
    std::vector<double> pVector;
    std::vector<double> dVector;
    startTimer(0);
    while (endVariable >= 0.5 && time >= getTime(0))
    {
        delay(10);
        error = targetDegree - gyro.get_rotation();
        //if (fabs(error) <= integralKickin && fabs(integral) < (1.5 / kI))
        //    integral += error;
        derivative = error - lastError;
        lastError = error;
        tPower = error * kP + integral * kI + derivative * kD;
        if (tPower > 0 && tPower < minVal)
            tPower = minVal;
        if (tPower < 0 && tPower> -minVal)
            tPower= -minVal;
        moveDriveMotors(0, tPower);
        //std::cout <<getTime(0) << "ms, " << tPower << std::endl;
        outputVector.push_back(tPower);
        readVector.push_back(error);
        pVector.push_back(error*kP);
        dVector.push_back(derivative*kD);
        endVariable = (endVariable * 4 + fabs(error))/5;
    }
    moveDriveMotors(0, 0);
    /*
    std::cout<<std::endl<<"Outpt"<<std::endl<<"[";
    for (int i=0;i<outputVector.size();i++) {
        std::cout << outputVector.at(i) <<", ";
        delay(10);
    }
    std::cout<<"0]"<<std::endl;

    std::cout<<std::endl<<"Input"<<std::endl<<"[";
    for (int i=0;i<readVector.size();i++) {
        std::cout << readVector.at(i) <<", ";
        delay(10);
    }
    std::cout<<"0]"<<std::endl;

    std::cout<<std::endl<<"Propr"<<std::endl<<"[";
    for (int i=0;i<pVector.size();i++) {
        std::cout << pVector.at(i) <<", ";
        delay(10);
    }
    std::cout<<"0]"<<std::endl;

    std::cout<<std::endl<<"Deriv"<<std::endl<<"[";
    for (int i=0;i<dVector.size();i++) {
        std::cout << dVector.at(i) <<", ";
        delay(10);
    }
    std::cout<<"0]"<<std::endl;
    */
    if (time < getTime(0)){std::cout <<"TIMED OUT" << std::endl;}
    else {std::cout << "TOOK " << getTime(0) << "MS" << std::endl;}
    std::cout << "Ending true angle: " << gyro.get_rotation() << std::endl;
    std::cout << "Ending expected angle: " << absoluteAngle << std::endl;
    std::cout << "final integral: " << integral << std::endl;
    std::cout << "--------end-------" << std::endl << std::endl;
    delay(10);
}

// void catapult():
//     while true:
//         delay(100)
//         if (infiniteCata == false){
//             cataMotor.break()
//         }
//         if (controller.buttonUp.pressing()
//             or (cataDist.object_distance(MM) < 50 and autoCata == True)
//             or (shootCommand)
//             or (autoCata == True and stallVariable > 100)):
//             #if not controller.buttonX.pressing(): wait(0.05,SECONDS)
//             cataMotor.spin(FORWARD,12,VOLT)
//             wait(0.3,SECONDS)
//             timer = 80
//             while (catapultLoadDist.object_distance(MM) > 90) and timer > 0:
//                 wait(0.01,SECONDS)
//                 timer -= 1
//             if timer == 0:
//                 cataMotor.spin(REVERSE,12,VOLT)
//                 wait(0.1,SECONDS)
//                 cataMotor.stop()
//             else:
//                 shootCommand = False
//             stallVariable = 0

// Drive amount of Inches
/*void setDriveStopping(){
    rMotor1.brake();
    rMotor2.brake();
    lMotor1.brake();
    rMotor2.brake();
}
void drive(int lInput, int rInput){
    lSpeed = lInput / 8;
    rSpeed = rInput / 8;
    if (abs(lInput) < 5){
        lMotor1.brake();
        lMotor2.brake();
    }
    if (PTOvar == false){
        ltMotor.brake();
    }
    if (abs(rInput) < 5){
        rMotor1.brake();
        rMotor2.brake();
        if (PTOvar == false){
            rtMotor.brake()
        }
    }
    else {
        lMotor1 = lInput;
        lMotor2 = lInput;
        rMotor1 = rInput;
        rMotor2 = rInput;
        if(PTOvar == 0){
            ltMotor = lInput;
            rtMotor = rInput;
        }
    }
}
void PTOswitcher(bool i){
    if (i){
        PTOvar = 0;
        PTOpiston = true;
        ltMotor.brake();
        rtMotor.brake();
    }

    else {
        PTOvar = 1;
        PTOpiston = false;
        ltMotor.brake();
        rtMotor.brake();
    }
}
void PTOmotors(int s){
    if (PTOvar == 1){
        if (s == 0){
            ltMotor.stop()
            rtMotor.stop()
        }
        else{
            ltMotor.spin(FORWARD,s,VOLT)
            rtMotor.spin(FORWARD,s,VOLT)
        }
    }
bool shootCommand = False
bool infiniteCata = False
}
void catapult(){
    int stallVariable = 0
    while (true){
        delay(100)
        if (infiniteCata == false){
            cataMotor.brake()
        }
        if ((master.get_digital(DIGITAL_UP)) || (cataDist.object_distance(MM) < 50 and autoCata == True) || (shootCommand) || (autoCata == True and stallVariable > 100)){
            cataMotor = 127;
            delay(300);
            timer = 80;
            while ((catapultLoadDist.object_distance(MM) > 90) and timer > 0){
                delay(100);
                timer -= 1;
            }
            if (timer == 0){
                cataMotor = -127;
                delay(100);
                cataMotor.brake()
            }
            else{
                shootCommand = false
            }
            stallVariable = 0
        }

    }
}
void lifter(){
    while (true){
        delay(100)
        if ((master.get_digital(DIGITAL_Y) || liftVar == 1)){
                setDriveStopping()
                PTOswitcher(false)
                ratchPiston.set(false)
                master.print("F")
                delay(200)
                master.set_cursor(0,0)
                ltMotor.brake()
                rtMotor.brake()
                PTOmotors(12)
                i = 0
                while ((liftSens.position() % 360) < 100 and i < 30){
                    wait(0.1,SECONDS)
                    i+=1
                }
                delay(50)
                PTOmotors(0)
                liftVar = 0
                autoCata = true
            }

        else if (controller.axis2.position() < -96 or liftVar == 2){
            autoCata = False
            PTOmotors(-12);
            ltMotor.coast();
            rtMotor.coast();
            setDriveStopping();
            i = 0;
        }

            while ((liftSens.position() % 360) > 10 && i < 30){
                delay(100);
                i+=1;
                if (i >=25){
                    ratchPiston = true;
                }
            }
            delay(50);
            PTOmotors(0);
            PTOswitcher(true);
            liftVar = 0;
        else if (controller.buttonRight.pressing() || liftVar == 3){
            setDriveStopping();
            PTOswitcher(false)
            ratchPiston.set(false)
            controller.screen.print("F")
            controller.screen.set_cursor(0,0)
            ltMotor.hold()
            rtMotor.set_stopping(HOLD)
            PTOmotors(12) #loop to make it go up until limit
            i = 0
        }
            while ((liftSens.position() % 360) < 50 and i < 30){
                delay(100)
                i+=1
            }
            PTOmotors(0)
            liftVar = 0
    }

}
void driveInches(int lInput, int rInput, int lSpd, int rSpd){

}
void driveDist(double target);{

}
void driveFunction(double target, double Kp, double Ki, double Kd, double intKickin, double mv){

}
void driveDist2(double target, double velo){

}
void rotCall(double target){

}
void rotCall2(double target, double p, double d){

}
void rotDeg(double target, double Kp, double Ki, double Kd, double timer, double mv, double iw){

}
*/

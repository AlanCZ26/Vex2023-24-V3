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

// Drive amount of Inches
void driveStraight(double inches, double targetDegree, double maxPower, double time, double kP, double kI, double kD)
{
    resetMotorEncoders();
    startTimer(0);
    double error, tError, derivative, lastError, tPower, tkP;
    double integral = 0;
    double integralLimit = 5;

    /*
    resetMotorEncoders();
    startTimer(0);
    // double rPos = (rMotor1.get_position() * (3 / 5)) * 0.02836160034;
    // double lPos = (lMotor1.get_position() * (3 / 5)) * 0.02836160034;
    double integralLimit = 5;
    double integral = 0;
    double error;
    double tError;
    double derivative;
    double lastError;
    double tPower;
    double tkP;

    // error = inches * (5.0 / 3.0) / 0.02836160034;
    error = inches;
    double power = error * kP + integral * kI + derivative * kD;
    moveDriveMotors(power, 0);
    while (fabs(error) >= 0.1 && time >= getTime(0))
    {
        // rPos = (rMotor1.get_position() * (3.0 / 5.0)) * 0.02836160034;
        // lPos = (lMotor1.get_position() * (3.0 / 5.0)) * 0.02836160034;
        tError = targetDegree - gyro.get_heading();
        error = (inches * (5.0 / 3.0) / 0.02836160034) - (((rMotor1.get_position() + rMotor1.get_position()) / 2));
        integral += error;

        derivative = error - lastError;
        lastError = error;
        if (inches * 0.8 <= (fabs(rMotor1.get_position()) + fabs(lMotor1.get_position())) / 2)
        {
            power = error * kP + integral * kI + derivative * kD;
            tPower = tError * tkP;
            moveDriveMotors(power, 0);
        }
        else
        {
            power = error * kP + derivative * kD;
            tPower = tError * tkP;
            moveDriveMotors(power, 0);
        }
        pros::screen::print(TEXT_MEDIUM, 1, "error: %d", error);
        pros::screen::print(TEXT_MEDIUM, 2, "power: %d", power);
    }
    /*
    // while(fabs(error) >= 0.1 // && time <= getTime(0) ){
    //     rPos = (rMotor1.get_position() * (3.0 / 5.0)) * 0.02836160034;
    //     lPos = (lMotor1.get_position() * (3.0 / 5.0)) * 0.02836160034;
    //     tError = targetDegree - gyro.get_heading();
    //     error = inches - (fabs(rPos) + fabs(lPos))/2;
    //     	pros::screen::print(TEXT_MEDIUM, 2, "error: %d", error);
    //         integral += error;

    //     derivative = error - lastError;
    //     lastError = error;
    //     if(inches * 0.8 <= (fabs(rPos) + fabs(lPos))/2){
    //         power = error*kP + integral*kI + derivative*kD;
    //         tPower = tError*tkP;
    //         moveDriveMotors(power, 0);
    //     }
    //     else{
    //         power = error*kP + derivative*kD;
    //         tPower = tError*tkP;
    //         moveDriveMotors(power, 0);
    //     }
    // }

    moveDriveMotors(0, 0);
    rMotor1.brake();
    rMotor2.brake();
    lMotor1.brake();
    lMotor2.brake();
    */
}
double absoluteAngle = 0;
/**
 * \param target Target in inches
 * \param time Time limit in ms
 */
void driveDist(double target, double time, double kP, double kI, double kD, double minVal, double intKickin, double intMax, double tkP)
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
    double endVariable = target;
    while (fabs(endVariable) > 0.5 && time >= getTime(0))
    {
        measure = (((lMotor1.get_position() + rMotor1.get_position() + lMotor2.get_position() + rMotor2.get_position())) * 0.00425424005);
        error = target - measure;
        if (fabs(integral) <= intMax)
            integral += error;
        derivative = error - prevError;
        prevError = error;

        errorRot = (gyro.get_rotation() - absoluteAngle) * tkP;

        output = (error * kP) + (integral * kI) + (derivative * kD);

        lOut = (output - errorRot) * 10; // 10x bc we used volts before :P
        rOut = (output + errorRot) * 10;
        if (lOut > 0 && lOut < minVal)
            lOut = minVal;
        if (lOut < 0 && lOut > -minVal)
            lOut = -minVal;
        if (rOut > 0 && rOut < minVal)
            rOut = minVal;
        if (rOut < 0 && rOut > -minVal)
            rOut = -minVal;

        moveDriveSideMotors(lOut, rOut);
        pros::screen::print(TEXT_MEDIUM, 1, "error: %f", error);
        pros::screen::print(TEXT_MEDIUM, 2, "power: %f", lOut);
        pros::screen::print(TEXT_MEDIUM, 3, "enc: %f", lMotor1.get_position());
        pros::delay(10);
        endVariable = (endVariable * 9 + error)/10;
    }
    moveDriveMotors(0, 0);
    pros::delay(10);
    pros::screen::print(TEXT_MEDIUM, 1, "-end-");
}

void driveCall(double target)
{
    driveDist(target, 10000, 1, 0, 1, 1, 0, 5, 0.5);
}

void turnCall(double targetAngle)
{
    turn(targetAngle, 10000, 1, 0, 10);
}

void turn(double targetDegree, double time, double kP, double kI, double kD)
{
    absoluteAngle += targetDegree;
    targetDegree = absoluteAngle;
    double error = targetDegree - gyro.get_rotation();
    double integralLimit = 5;
    double integral, derivative, lastError, power, tPower;
    startTimer(0);
    while (fabs(error) >= 1 && time >= getTime(0))
    {
        error = targetDegree - gyro.get_rotation();
        if (error <= integralLimit)
            integral += error;
        derivative = error - lastError;
        lastError = error;
        tPower = error * kP + integral * kI + derivative * kD;
        moveDriveMotors(0, tPower);
    }
    moveDriveMotors(0, 0);
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

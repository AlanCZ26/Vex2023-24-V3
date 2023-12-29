#include "main.h"
#include "pros/llemu.hpp"
#include "pros/screen.h"
bool PTOvar = false;
bool infiniteCata;
bool autoCata;
bool shootCommand;
bool liftVar;
bool cataRunner;


void PTOswitcher(int i){
    if (i == 1){
        PTOpiston.set_value(1);
    }     
    else{
        PTOpiston.set_value(0);
    }
}

void resetMotorEncoders(){
    rMotor1.tare_position();
    rMotor2.tare_position();
    lMotor1.tare_position();
    lMotor2.tare_position();
    rtMotor.tare_position();
    ltMotor.tare_position();
}
void moveDriveMotors(int forwardPower, int turningPower){
    rMotor1 = forwardPower + turningPower; 
    rMotor2 = forwardPower + turningPower; 
    lMotor1 = forwardPower - turningPower; 
    lMotor2 = forwardPower - turningPower; 
    //This is for PTO
    if(PTOvar == true){
        ltMotor = forwardPower - turningPower;
        rtMotor = forwardPower + turningPower;
    }
    else{

    }
}
void moveDriveSideMotors(int leftPower, int rightPower){
    rMotor1 = rightPower; 
    rMotor2 = rightPower; 
    lMotor1 = leftPower; 
    lMotor2 = leftPower; 
    //This is for PTO
    if(PTOvar == true){
        ltMotor = leftPower;
        rtMotor = rightPower;
    }
    else{
        ltMotor = 0;
        rtMotor = 0;
    }
}
// Drive amount of Inches
void driveStraight(double inches, double targetDegree, double maxPower, double time, double kP, double kI, double kD){
    resetMotorEncoders();
    startTimer(0);
    //double rPos = (rMotor1.get_position() * (3 / 5)) * 0.02836160034;
    //double lPos = (lMotor1.get_position() * (3 / 5)) * 0.02836160034;
    double error;
    double integralLimit = 5; 
    double tError;
    double integral = 0; 
    double derivative; 
    double lastError;

    double tPower;
    double tkP;


    //error = inches * (5.0 / 3.0) / 0.02836160034;
    error = inches; 
    double power = error*kP + integral*kI + derivative*kD;
    moveDriveMotors(power, 0);
    while(fabs(error) >= 0.1 && time >= getTime(0)){
        //rPos = (rMotor1.get_position() * (3.0 / 5.0)) * 0.02836160034;
        //lPos = (lMotor1.get_position() * (3.0 / 5.0)) * 0.02836160034;
        tError = targetDegree - gyro.get_heading();
        error = (inches * (5.0 / 3.0) / 0.02836160034) -(((rMotor1.get_position()+rMotor1.get_position())/2)); 
            integral += error;

        derivative = error - lastError;
        lastError = error;
        if(inches * 0.8 <= (fabs(rMotor1.get_position()) + fabs(lMotor1.get_position()))/2){
            power = error*kP + integral*kI + derivative*kD;
            tPower = tError*tkP;
            moveDriveMotors(power, 0);
        }
        else{
            power = error*kP + derivative*kD;
            tPower = tError*tkP;
            moveDriveMotors(power, 0);
        }
        pros::screen::print(TEXT_MEDIUM, 1, "error: %d", error);
        pros::screen::print(TEXT_MEDIUM, 2, "power: %d", power);

    }
    // while(fabs(error) >= 0.1 /*&& time <= getTime(0)*/){
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
    moveDriveMotors(0,0);
    rMotor1.brake();
    rMotor2.brake();
    lMotor1.brake();
    lMotor2.brake();
} 
void turnHead(double target, double kP, double kI, double kD){
    double error = target - gyro.get_heading();
    double integral;
    double integralLimit = 5;
    double derivative;
    double lastError;
    double power;
    double tPower;
    while(gyro.get_heading() <= target){
        error = target - gyro.get_heading();
        if(error <= integralLimit){
            integral += error;
        }
        derivative = error - lastError;
        lastError = error;
        tPower = error*kP + integral*kI + derivative*kD;
        moveDriveMotors(0,-tPower);
    }
    moveDriveMotors(0, 0);
}
void turn(double targetDegree, double time, double kP, double kI, double kD){
    gyro.tare_rotation();
    double error = targetDegree - gyro.get_rotation();
    double integral;
    double integralLimit = 5;
    double derivative;
    double lastError;
    double power;
    double tPower;
    startTimer(0); 
    while (fabs(error) >= 1 && time >= getTime(0)){
        error = targetDegree - gyro.get_rotation();
        if(error <= integralLimit){
            integral += error;
        }
        derivative = error - lastError;
        lastError = error;
        tPower = error*kP + integral*kI + derivative*kD;
        moveDriveMotors(0,tPower);
    }
    moveDriveMotors(0,0);
    pros::screen::print(TEXT_MEDIUM, 1, "Rotation: %f", gyro.get_rotation());
    pros::screen::print(TEXT_MEDIUM, 2, "Derivative: %f", derivative*kD);
    pros::screen::print(TEXT_MEDIUM, 3, "Error: %f", error*kP);

}

void moveArm(int position){
    if(position == 1){
        PTOvar = false;
        PTOpiston.set_value(0);
        ratchPiston.set_value(0);
        while(liftSens.get_position() <= 9900){
            rtMotor = 127;
            ltMotor = 127;
            pros::delay(10);
        }
            rtMotor = 0;
            ltMotor = 0;
    }
    else if(position == 0){
        while(liftSens.get_position() >= 900){
            startTimer(1);
            if(liftSens.get_position() >= 900 && getTime(1) > 3){
                rtMotor = 0;
                ltMotor = 0;
            }
            else{
                rtMotor = -127;
                ltMotor = -127;
            }
            pros::delay(10);
        }
            rtMotor = 0;
            ltMotor = 0;
            PTOpiston.set_value(1);
            PTOvar = true;
    }
    else if(position == 2){
        PTOvar = false;
        PTOpiston.set_value(0);
        ratchPiston.set_value(0);
        while(liftSens.get_position() <= 5000){
            rtMotor = 127;
            ltMotor= 127;
            pros::delay(10);
        }
            rtMotor = 0;
            ltMotor = 0;
    }
 
}
void catapult()
{
    /*
    if (!controller.get_digital(E_CONTROLLER_DIGITAL_X))
    {
        pros::delay(50);
    }
    */
   

    delay(200);
    while(true){
        if(cataRunner == true){
            cataMotor = 127;

        }
        // else{
        //     cataMotor = 0;
        // }
    
        else if (cataRot.get_position() <= 12400 && cataRunner == false)
        {
           cataMotor = 127;

          delay(10);
        }
        else {
            cataMotor = 0;
        }
    }
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

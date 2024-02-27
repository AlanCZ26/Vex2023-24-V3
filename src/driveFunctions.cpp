#include "main.h"
#include "pros/llemu.hpp"
#include "pros/screen.h"

void moveDriveSideMotors(int leftPower, int rightPower)
{
    rMotor1 = rightPower;
    rMotor2 = rightPower;
    rMotor3 = rightPower;
    lMotor1 = leftPower;
    lMotor2 = leftPower;
    lMotor3 = rightPower;
}

void moveDriveMotors(int forwardPower, int turningPower)
{
    
    if (forwardPower == 0 && turningPower == 0)
    {
        rMotor1.brake();
        rMotor2.brake();
        rMotor3.brake();
        lMotor1.brake();
        lMotor2.brake();
        lMotor3.brake();
    }
    else {
        rMotor1 = forwardPower - turningPower;
        rMotor2 = forwardPower - turningPower;
        rMotor3 = forwardPower - turningPower;
        lMotor1 = forwardPower + turningPower;
        lMotor2 = forwardPower + turningPower;
        lMotor3 = forwardPower + turningPower;   
    }    

}
/*
void ptoSwitcher(int i)
{
    if (i == PTOMODECATA)
    {
        PTOvar = PTOMODECATA;
        PTOpiston.set_value(false);
        cataMotor.brake();
        cataMotor2.brake();
    }
    else if (i == PTOMODELIFT)
    {
        PTOvar = PTOMODELIFT;
        PTOpiston.set_value(true);
        cataMotor.brake();
        cataMotor2.brake();
    }
}

int state = 0;
void lift(int input)
{
    int limit;
    startTimer(1);
    if (input == liftDefault) {limit = 0;}
    if (input == barHangMin)  {limit = 0;}
    if (input == sideHangMin) {limit = 0;}
    if (input == barHangMax)  {limit = 0;}
    if (input == sideHangMax) {limit = 0;}
    ratchPiston.set_value(false);
    ptoSwitcher(PTOMODELIFT);
    delay(50);
    if (input < state) {
        cataMotor.move(-127);
        cataMotor2.move(-127);    
        while (liftRot.get_position() > limit && getTime(1) < 3000){
            pros::delay(50);
        }
    }
    else{
        cataMotor.move(127);
        cataMotor2.move(127); 
        while (liftRot.get_position() < limit && getTime(1) < 3000){
            pros::delay(50);
        }
    }

    if (input == 3 || input == 4) ratchPiston.set_value(true);
    state = input;
}
*/
void catapult(bool i){
    if (i) {
        //ptoSwitcher(PTOMODECATA);
        cataMotor.move(127);
        cataMotor2.move(127); 
    }
    else {
        cataMotor = 0;
        cataMotor2 = 0;
    }
}

void cataTracker(){
    int cataEff;
    while (true){
        cataEff = (cataMotor.get_efficiency() + cataMotor2.get_efficiency())/2;
    } 
}

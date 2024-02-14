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

bool skillsCataVariable = false;
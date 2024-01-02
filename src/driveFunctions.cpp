#include "main.h"
#include "pros/llemu.hpp"
#include "pros/screen.h"

void moveDriveSideMotors(int leftPower, int rightPower)
{
    rMotor1 = rightPower;
    rMotor2 = rightPower;
    lMotor1 = leftPower;
    lMotor2 = leftPower;
    if (PTOvar == DRIVE)
    {
        ltMotor = leftPower;
        rtMotor = rightPower;
    }
}

void moveDriveMotors(int forwardPower, int turningPower)
{
    
    if (forwardPower == 0 && turningPower == 0)
    {
        rMotor1.brake();
        rMotor2.brake();
        lMotor1.brake();
        lMotor2.brake();
        if (PTOvar == DRIVE)
        {
            ltMotor.brake();
            rtMotor.brake();
        }
    }
    else {
        rMotor1 = forwardPower - turningPower;
        rMotor2 = forwardPower - turningPower;
        lMotor1 = forwardPower + turningPower;
        lMotor2 = forwardPower + turningPower;
        if (PTOvar == DRIVE)
        {
            rtMotor = forwardPower - turningPower;
            ltMotor = forwardPower + turningPower;
        }        
    }    

}

void ptoSwitcher(int i)
{
    if (i == DRIVE)
    {
        PTOvar = DRIVE;
        PTOpiston.set_value(true);
        ltMotor.brake();
        rtMotor.brake();
    }
    else if (i == PTO)
    {
        PTOvar = PTO;
        PTOpiston.set_value(false);
        ltMotor.brake();
        rtMotor.brake();
    }
}

int heldPosition = 0;
void lifter(int position)
{
    if (position == 1 && heldPosition != 1) // up
    {
        ptoSwitcher(PTO);
        startTimer(1);
        rtMotor = -127;
        ltMotor = -127;
        while (liftSens.get_position() <= 9900 && getTime(1) < 3000)
        {
            pros::delay(10);
        }
        rtMotor = 0;
        ltMotor = 0;
        heldPosition = position;
    }
    else if (position == 0 && heldPosition != 0) // down
    {
        startTimer(1);
        rtMotor = 127;
        ltMotor = 127;
        while (liftSens.get_position() >= 900 && getTime(1) < 3000)
        {
            pros::delay(10);
            if (getTime(1) > 2000)
            {
                ratchPiston.set_value(1);
            }
        }
        rtMotor = 0;
        ltMotor = 0;
        ptoSwitcher(DRIVE);
        heldPosition = position;
    }
    else if (position == 2 && heldPosition != 2) // middle
    {
        ptoSwitcher(PTO);
        while (liftSens.get_position() <= 3000)
        {
            rtMotor = -127;
            ltMotor = -127;
            pros::delay(10);
        }
        rtMotor = 0;
        ltMotor = 0;
        heldPosition = position;
    }
    position = -1;
}

void catapult()
{
    delay(200);
    while (true)
    {
        if (cataRunner == true
        || (autoCata == true && cataDist.get() <= 50))
        {
            cataMotor = 127;
            delay(200);
        }
        else if (cataRot.get_position() <= 12400 && cataRunner == false)
        {
            cataMotor = 127;
            delay(10);
        }
        else cataMotor.brake();
    }
}

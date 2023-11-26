#include "main.h"

int PTOvar = DRIVE;
void drivetrain(int l, int r)
{
    if (l == r == 0)
    {
        lMotor1.brake();
        lMotor2.brake();
        rMotor1.brake();
        rMotor2.brake();
        if (PTOvar == DRIVE)
        {
            ltMotor.brake();
            rtMotor.brake();
        }
    }
    else
    {
        lMotor1 = l;
        lMotor2 = l;
        rMotor1 = r;
        rMotor2 = r;
        if (PTOvar == PTO)
        {
            ltMotor = l;
            rtMotor = r;
        }
    }
}

void ptoSwitcher(int i)
{
    if (i == true)
    {
        PTOvar = DRIVE;
        ptoSol.set_value(true);
        ltMotor.brake();
        rtMotor.brake();
    }
    else
    {
        PTOvar = PTO;
        ptoSol.set_value(false);
        ltMotor.brake();
        rtMotor.brake();
    }
}

void PTOmotors(int s)
{
    if (PTOvar == PTO)
    {
        if (s == 0)
        {
            ltMotor.brake();
            rtMotor.brake();
        }
        else
        {
            ltMotor = s;
            rtMotor = s;
        }
    }
}

void catapult()
{
    if (!controller.get_digital(E_CONTROLLER_DIGITAL_X))
    {
        pros::delay(50);
    }
    cataMotor = 127;
    delay(100);
    if (!controller.get_digital(E_CONTROLLER_DIGITAL_X))
    {
        while (cataLimit.get_value() == 1)
        {
            delay(10);
        }
        cataMotor.brake();
    }
}

void lifter(){
    
}
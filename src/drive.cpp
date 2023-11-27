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

void driveDifferencial(int s, int r) {
    drivetrain(s + r, s - r);
}

void set_stopping(motor_brake_mode_e_t i)
{
    lMotor1.set_brake_mode(i);
    lMotor2.set_brake_mode(i);
    rMotor1.set_brake_mode(i);
    rMotor2.set_brake_mode(i);
}

void ptoSwitcher(int i)
{
    if (i == DRIVE)
    {
        PTOvar = DRIVE;
        ptoSol.set_value(true);
        ltMotor.brake();
        rtMotor.brake();
    }
    else if (i == PTO)
    {
        PTOvar = PTO;
        ptoSol.set_value(false);
        ltMotor.brake();
        rtMotor.brake();
    }
}

/** \param s -127 - 127 */
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

void lifter(int state)
{
    if (state == UP)
    {
        ptoSwitcher(PTO);
        ratchSol.set_value(true);
        controller.clear_line(0);
        controller.set_text(0, 0, "Ratchet off");
        ltMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
        rtMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
        PTOmotors(127);
        int i = 0;
        while ((liftSensor.get_position() % 360) < 100 && i <= 30)
        {
            pros::delay(100);
            i++;
        }
        pros::delay(50);
        PTOmotors(0);
        liftVar = 0;
    }
    else if (state == DOWN)
    {
        ltMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        rtMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        PTOmotors(-127);
        int i = 0;
        while ((liftSensor.get_position() % 360) > 5 && i <= 30)
        {
            pros::delay(100);
            i++;
        }
        pros::delay(50);
        PTOmotors(0);
        ptoSwitcher(DRIVE);
        liftVar = 0;
    }
}

#include "main.h"

int PTOvar = DRIVE;
void drivetrain(int l, int r)
{
    // controller.clear_line(0);

    if (l == 0 && r == 0)
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
        if (PTOvar == DRIVE)
        {
            ltMotor = l;
            rtMotor = r;
        }
    }
}

void driveDifferencial(int s, int r)
{
    int left = s + r;
    int right = s - r;
    drivetrain(left, right);
}

double getEncoders()
{
    double raw;
    double output;
    raw = lMotor1.get_position() + lMotor2.get_position() + rMotor1.get_position() + rMotor2.get_position();
    output = raw / 4;
    return output;
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
    /*
    if (!controller.get_digital(E_CONTROLLER_DIGITAL_X))
    {
        pros::delay(50);
    }
    */
    cataMotor = 127;
    delay(200);
    while (cataLimit.get_value() == 0 || cataRunner == true)
    {
        delay(10);
    }
    cataMotor.brake();
}

int currentLiftState;
void lifter(int i)
{
    if (i == UP && currentLiftState != UP)
    {
        ptoSwitcher(PTO);
        ratchSol.set_value(false);
        controller.clear_line(0);
        controller.set_text(0, 0, "Ratchet off");
        ltMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
        rtMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
        PTOmotors(127);
        int i = 0;
        while (((liftSensor.get_position()) < 10500) && (i <= 30))
        {
            pros::delay(100);
            i++;
        }
        pros::delay(50);
        PTOmotors(0);
        liftVar = 0;
        currentLiftState = UP;
    }
    else if (i == DOWN && currentLiftState != DOWN)
    {
        ltMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        rtMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        PTOmotors(-127);
        int i = 0;
        while ((liftSensor.get_position()) > 700 && i <= 30)
        {
            pros::delay(100);
            i++;
        }
        pros::delay(50);
        PTOmotors(0);
        ptoSwitcher(DRIVE);
        liftVar = 0;
        currentLiftState = DOWN;
    }
}

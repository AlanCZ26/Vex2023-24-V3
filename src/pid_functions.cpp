#include "main.h"

/*
class gyroClass
{
private:
    double position;
public:
    void set_zero()
    {
        position = imu.get_rotation();
    }
    double get_relative()
    {
        return (imu.get_rotation() - position);
    }
    double get_absolute()
    {
        return imu.get_rotation();
    }
};
*/

void straight_pid(double targetDist, double kp, double ki, double kd, double min)
{
    tare_encoders();
    double proportional = 3;
    double integral = 0;
    double derivative = 0;
    double prevProportional = 0;
    double prevRotation = imu.get_rotation();
    double error = targetDist + 0.1;
    double prevError = abs(error);
    int timer = 200; // make timer function l8r
    double measure;
    double angleMeasure;
    double output;
    double outputRot;
    double outputL;
    double outputR;

    while (abs(prevError) > 3 && (error != prevError) && timer > 0)
    {
        timer--;
        pros::delay(10);
        measure = getEncoders();
        angleMeasure = imu.get_rotation() - prevRotation;
        proportional = targetDist - measure;
        integral += proportional;
        derivative = proportional = prevProportional;
        output = proportional * kp + integral * ki + derivative * kd;
        outputRot = angleMeasure * 0.1;
        outputL = output + outputRot;
        outputR = output - outputRot;
        if (0 < outputL < min)
            outputL = min;
        if (0 > outputL > -min)
            outputL = -min;
        if (0 < outputR < min)
            outputR = min;
        if (0 > outputR > -min)
            outputR = -min;
        drivetrain(outputL * 1.27,outputR * 1.27);
        pros::lcd::set_text(0,std::to_string(output));
    }
    drivetrain(0,0);
    pros::delay(100);
}

void drive_straight(double target) {
    double kp = 0.8;
    double ki = 0;
    double kd = 0;
    double min = 20;
    straight_pid(target,kp,ki,kd,min);
}

//double current_imu_pos = 0;
void rotate_pid(double target) {
    double error = 100;
    double prevError = abs(target);
    int timer = 150;
    double rot;
    double output;
    double min = 25;
    while (prevError > 4 && timer > 0) {
        timer--;
        pros::delay(10);
        rot = imu.get_rotation();
        error = target - rot;
        output = error * 0.25;
        if (0 < output < min) output = min;
        if (0 > output > min) output = -min;
        drivetrain(output * 1.27, output * -1.27);
        prevError = (prevError * 9 + abs(error)) / 10;
    }
    drivetrain(0,0);
    pros::delay(100);
}
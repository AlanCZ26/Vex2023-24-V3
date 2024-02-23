#include "main.h"
#include "pros/llemu.hpp"
#include "pros/screen.h"

lemlib::TrackingWheel verticalTrackingWheel(&odomPodVertical, 2.75, 0);

// odometry struct
lemlib::OdomSensors_t sensors {
    &verticalTrackingWheel, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &gyro // inertial sensor
};

// forward/backward PID
lemlib::ChassisController_t lateralController {
    10, // kP
    60, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    4, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    40 // slew rate
};

lemlib::Drivetrain_t drivetrain {
    &leftMotors, // left drivetrain motors
    &rightMotors, // right drivetrain motors
    25, // track width 
    2.75, // wheel diameter
    450 // wheel rpm
};

lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);


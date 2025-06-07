#include "VISUAL API.hpp" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep

#pragma once

// controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

// motor groups
inline pros::MotorGroup leftMotors({-5, 4, -3}, pros::MotorGearset::blue); // left motor group - ports 5 (reversed), 4, 3 (reversed)
inline pros::MotorGroup rightMotors({6, -9, 7}, pros::MotorGearset::blue); // right motor group - ports 6, 9 (reversed), 7

// Inertial Sensor on port 10
inline pros::Imu imu(10);

// tracking wheels
// horizontal tracking wheel encoder. Rotation sensor, port 20, not reversed
    inline pros::Rotation horizontalEnc(20);
// vertical tracking wheel encoder. Rotation sensor, port 11, reversed
    inline pros::Rotation verticalEnc(-11);

//tracking wheeel data setup
// horizontal tracking wheel. 2.75" diameter, 5.75" offset, back of the robot (negative)
    inline lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_275, -5.75);
// vertical tracking wheel. 2.75" diameter, 2.5" offset, left of the robot (negative)
    inline lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_275, -2.5);

// drivetrain settings
inline lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              10, // 10 inch track width
                              lemlib::Omniwheel::NEW_4, // using new 4" omnis
                              600, // drivetrain rpm is 600
                              2 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
inline lemlib::ControllerSettings linearController(10, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            3, // derivative gain (kD)
                                            3, // anti windup
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

 // angular motion controller
inline lemlib::ControllerSettings angularController(2, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             10, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// sensors for odometry
inline lemlib::OdomSensors sensors(&vertical, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            &horizontal, // horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// input curve for throttle input during driver control
inline lemlib::ExpoDriveCurve throttleCurve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1 // expo curve gain
);

// input curve for steer input during driver control
inline lemlib::ExpoDriveCurve steerCurve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1 // expo curve gain
);

// create the chassis
inline lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);

// Add more ports and PIDS down here...

// pros::adi::DigitalOut piston('A'); // this is a true/false signal named piston on 3 wire port A
// lemlib::PID name(1,0,2); // this is a pid callled name with p = 1 i = 0 d = 2
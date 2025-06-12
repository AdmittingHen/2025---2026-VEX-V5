#include "Visual VEX/LemLib_setup.hpp"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <algorithm>
#include <cmath>

#include <stdlib.h>

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize(){
    //add autons to the selector
    VIS::Setup_Autons();

    chassis.calibrate(); // calibrate sensors
}

/**
 * Runs while the robot is disabled
 */
void disabled(){}

/**
 * runs after initialize if the robot is connected to field control
 */
void competition_initialize(){}

/**
 * Runs during auto
 */
void autonomous(){
    chassis.setPose(0,0,0);
    VIS::S::run();//this runs the selected auton
}

float activebrake_power = 0.01;//leave this very small

lemlib::PID ActiveBrakeR(activebrake_power, 0, 0.2);
lemlib::PID ActiveBrakeL(activebrake_power, 0, 0.2);

void updateDrive(){
    // get joystick positions
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    // move the chassis with curvature drive
    if (abs(leftY) + abs(rightX)<2){
        double brakeR = ActiveBrakeR.update(0-rightMotors.get_actual_velocity());
        double brakeL = ActiveBrakeL.update(0-leftMotors.get_actual_velocity());
        double brakepwrR = abs(rightMotors.get_actual_velocity()) > 10 ? std::max(-10.0, std::min(brakeR, 10.0)) : 0;
        double brakepwrL = abs(leftMotors.get_actual_velocity()) > 10 ? std::max(-10.0, std::min(brakeL, 10.0)) : 0;
        chassis.tank(brakepwrL, brakepwrR);
    } else {
        chassis.arcade(leftY, rightX);
        ActiveBrakeR.reset();
        ActiveBrakeL.reset();
    }
}

/**
 * Runs in driver control
 */
void opcontrol(){
    bool allowAutonTest = true;
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    //runs the driver loop
    while (true){

        if (allowAutonTest && !pros::competition::is_connected() && (controller.get_digital(DIGITAL_A) && controller.get_digital(DIGITAL_B))){
            chassis.tank(0, 0);
            autonomous();// if no field is conected and buttons A and B are pressed, the bot will run the selected auton
        }

		updateDrive(); //this function updates the drivetrain with new contoller inputs

        //put other code below this line
        
        // delay to save resources
        pros::delay(6);
    }
}
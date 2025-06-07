#include "Visual VEX/LemLib_setup.hpp"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"
#include "pros/vision.h"
#include "pros/vision.hpp"
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

    pros::Vision eye(1, pros::E_VISION_ZERO_TOPLEFT);

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

float activebrake_power = 0.05;
float activebrake_curve = 8;

lemlib::PID LeftActiveBrake(activebrake_power, 0, 0);
lemlib::PID RightActiveBrake(activebrake_power, 0, 0);

void updateDrive(){
    // get joystick positions
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    // move the chassis with curvature drive
    if (abs(leftY + rightX)<2){
        chassis.tank(pow(LeftActiveBrake.update(rightMotors.get_actual_velocity()), activebrake_curve), 
                    pow(RightActiveBrake.update(leftMotors.get_actual_velocity()), activebrake_curve));
    } else {
        chassis.arcade(leftY, rightX);
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
            autonomous();// if no field is conected and buttons A and B are pressed, the bot will run the selected auton
        }

		updateDrive(); //this function updates the drivetrain with new contoller inputs
        
        // delay to save resources
        pros::delay(6);
    }
}
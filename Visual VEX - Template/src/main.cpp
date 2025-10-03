#include "Visual VEX/LemLib_setup.hpp"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
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

int ab[2] = {0,0};//a list for storage of active brake values for left and right

lemlib::PID ActiveBrakeR(activebrakepwr, 0, 0.2);//this creates the PID for ActiveBrake
lemlib::PID ActiveBrakeL(activebrakepwr, 0, 0.2);

void updateDrive(){
    // get joystick positions
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    // move the chassis with curvature drive
    if (abs(leftY + rightX)<2){
        ab[0] = ActiveBrakeL.update(leftMotors.get_actual_velocity());
        ab[1] = ActiveBrakeR.update(rightMotors.get_actual_velocity());

        if (curves[0]>0){
            chassis.tank(pow(abs(ab[0])<0.05?0:ab[0], curves[0]), 
                        pow(abs(ab[1])<0.05?0:ab[1], curves[0]));
        } else {
            chassis.tank(abs(ab[0])<0.05?0:ab[0], 
                        abs(ab[1])<0.05?0:ab[1]);
        }
        
    } else {
        ActiveBrakeL.reset();
        ActiveBrakeR.reset();
        chassis.arcade(curves[1]>0?pow(leftY, curves[1]):leftY, curves[2]>0?pow(rightX, curves[2]):rightX);
    }
}

/**
 * Runs in driver control
 */
void opcontrol(){
    bool allowAutonTest = true;//this is the master control for the testing of autons in driver control
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
#include "Visual VEX/LemLib_setup.hpp"
#include "pros/misc.hpp"
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
    VIS::Setup_Autons("1.0");

    //eye.signature_from_utility(const std::int32_t id, const std::int32_t u_min, const std::int32_t u_max, const std::int32_t u_mean, const std::int32_t v_min, const std::int32_t v_max, const std::int32_t v_mean, const float range, const std::int32_t type);
    
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

int DeadZone = 2; // joystick deadzone

int ab[2] = {0,0};

lemlib::PID LeftActiveBrake(activebrake_power, 0, 0);
lemlib::PID RightActiveBrake(activebrake_power, 0, 0);

void updateDrive(){
    // get joystick positions
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    // move the chassis with curvature drive
    if (abs(leftY + rightX)<2){
        ab[0] = LeftActiveBrake.update(leftMotors.get_actual_velocity());
        ab[1] = RightActiveBrake.update(rightMotors.get_actual_velocity());
        chassis.tank(pow(ab[0]<0?0:ab[0], activebrake_curve), 
                    pow(ab[1]<0?0:ab[1], activebrake_curve));
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
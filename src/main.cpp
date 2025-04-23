#include "Visual VEX/VISUAL API.hpp"
#include "Visual VEX/LemLib_setup.hpp"
#include "pros/rtos.hpp"
#include <cmath>

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

    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms
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

float DriveTrain_values[4] = {6, //this is fwrd/back curve
                              6, //this is turning curve
                              30, //this is the curve for active brake 
                              0.2 //this is activebrake strength
                             };

lemlib::PID LeftActiveBrake(DriveTrain_values[3], 0, 0);
lemlib::PID RightActiveBrake(DriveTrain_values[3], 0, 0);

void updateDrive(){
    // get joystick positions
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    // move the chassis with curvature drive
    if (abs(leftY + rightX)<2){
        chassis.tank(pow(LeftActiveBrake.update(rightMotors.get_actual_velocity()), DriveTrain_values[2]), pow(RightActiveBrake.update(leftMotors.get_actual_velocity()), DriveTrain_values[2]));
    } else {
        chassis.arcade(pow(leftY, DriveTrain_values[0]), pow(rightX, DriveTrain_values[1]));
    }
}

/**
 * Runs in driver control
 */
void opcontrol(){
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    //runs the driver loop
    while (true){
		updateDrive(); //this function updates the drivetrain with new contoller inputs
        
        // delay to save resources
        pros::delay(10);
    }
}
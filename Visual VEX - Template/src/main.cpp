#include "Visual VEX/VISUAL_API.hpp"
#include "VISUAL VEX/AutonCode.cpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <cmath>

void Setup_Autons(){
    auton_selector.setframerate(60);
    auton_selector.autons_add(
        {{"red team test", "This is a red team auton function", drivefunc},
              {"red team test 2", "This is another red team function", drivefunc2}
    }, 
        {{"blue team test", "This is a blue team auton function", turnfunc},
               {"blue team test 2", "This is another blue team function", turnfunc2}
    }, 
        {{"skils test", "This is a Skils function it has no team", skils},
                {"skils test 2", "This is another Skils function you probably wont ever need another of these", skils2}
    }
    );
    auton_selector.auton_print();
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize(){
    //add autons to the selector
    Setup_Autons();

    chassis.calibrate(); // calibrate sensors

    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms
}

/**
 * Runs while the robot is disabled
 */
void disabled(){
    auton_selector.setframerate(60);
}

/**
 * runs after initialize if the robot is connected to field control
 */
void competition_initialize(){
    auton_selector.setframerate(50);
}

// get a path used for pure pursuit
// this needs to be put outside a function
ASSET(example_txt); // '.' replaced with "_" to make c++ happy

/**
 * Runs during auto
 */
void autonomous(){
    auton_selector.setframerate(10);
    auton_selector.selected_auton_run();
}

int curves[4] = {6, //this is fwrd/back curve
                 6, //this is turning curve
                 30 //this is the curve for active brake 
                };

float activebrake = 0.2;
lemlib::PID LeftActiveBrake(activebrake, 0, 0);
lemlib::PID RightActiveBrake(activebrake, 0, 0);

void updateDrive(){
    // get joystick positions
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    // move the chassis with curvature drive
    if (abs(leftY + rightX)<2){
        chassis.tank(pow(LeftActiveBrake.update(rightMotors.get_actual_velocity()), curves[2]), pow(RightActiveBrake.update(leftMotors.get_actual_velocity()), curves[2]));
    } else {
        chassis.arcade(pow(leftY, curves[0]), pow(rightX, curves[1]));
    }
}

/**
 * Runs in driver control
 */
void opcontrol(){
    auton_selector.setframerate(5);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    //runs the driver loop
    while (true){
		updateDrive(); //this function updates the drivetrain with new contoller inputs
        
        // delay to save resources
        pros::delay(10);
    }
}
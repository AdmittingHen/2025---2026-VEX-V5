#include "Visual VEX\Auton_manager\AutonFunctions.cpp"
#include "pros/rtos.hpp"

//use DRIVE:: (the function you want to use) for driving to positions or for distances
//use DRIVE::SETUP (the function you want to use) for driving constants
//use TURN:: (the function you want to use) for turning
//use TURN::SETUP (the function you want to use) for turning Constants

//DO NOT USE ANYTHING UNDER "SCREEN::" THIS IS FOR SCREEN PRINTING, NOT AUTONOMUS

//-----------------------------------------------------------------------------------------------------\\
//IF YOU HAVE A QUESTION GO AND ASK ME, IF I'M NOT THERE CALL ME, IF I DON'T ANSWER, MESSAGE ME. Thanks\\
//-----------------------------------------------------------------------------------------------------\\

//add your own functions here, you can use these is autons

void wait(float Seconds){
    pros::delay(Seconds/1000);
}

void wait_msec(int msec){
    pros::delay(msec);
}


using namespace VIS;

//any function below here should be an auton funtion, each ones name should also show up in main.cpp when the Setup_Autons() function is called
void drivefunc(){}

void drivefunc2(){}

void turnfunc(){}

void turnfunc2(){}

void skils(){}

void skils2(){}
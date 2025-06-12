#include "Visual VEX\VISUAL API.hpp"
#include "Visual VEX\LemLib_setup.hpp"
#include "pros/rtos.hpp"

//use DRIVE:: (the function you want to use) for driving to positions or for distances
//use DRIVE::SETUP (the function you want to use) for driving constants
//use TURN:: (the function you want to use) for turning
//use TURN::SETUP (the function you want to use) for turning Constants

//DO NOT USE ANYTHING UNDER "SCREEN::" THIS IS FOR SCREEN PRINTING, NOT AUTONOMUS

//-----------------------------------------------------------------------------------------------------\\
//IF YOU HAVE A QUESTION GO AND ASK ME, IF I'M NOT THERE CALL ME, IF I DON'T ANSWER, MESSAGE ME. Thanks\\
//-----------------------------------------------------------------------------------------------------\\

//add your own functions here, you can use these in autons

void wait(float Seconds){
    pros::delay(Seconds*1000);
}

void wait_msec(int msec){
    pros::delay(msec);
}

// get a path used for pure pursuit
// this needs to be put outside a function
ASSET(example_txt); // '.' replaced with "_" to make c++ happy
ASSET(RedTest1_txt); //files like this must have somthing in them, one character is enough

//when you add a new function you need to add it to the definition file so things are happy
//go to (filepath) "include/Visual VEX/AutonFunc.hpp"
//once you are there just type "void [your name here]();" take out the brackets
//now go to (filepath) "scr/main.cpp"

using namespace VIS;

//any function below here should be an auton funtion, each ones name should also show up in main.cpp when the Setup_Autons() function is called
void drivefunc(){}

void drivefunc2(){}

void turnfunc(){}

void turnfunc2(){}

void skils(){}

void skils2(){}
#include "VISUAL_namespace.hpp"
#include "Visual VEX/VISUAL_API.hpp" // IWYU pragma: keep
#include "Visual VEX\Auton_manager\TurnFunctions.cpp"
#include "lemlib/pose.hpp"
#include <cmath>

int ToPointTimeout = 8000;
int timeoutmult = 8000;

void VIS::DRIVE::SETUP::Set_ToPoint_timeout(int newtime){
    ToPointTimeout = newtime;
}

void VIS::DRIVE::SETUP::Set_timeout_mult(float newmult){
    timeoutmult = newmult;
}

int calcTimoutDrive(int Xdist, int Ydist, float speed){
    return ((Xdist+Ydist)/2.0)*speed*timeoutmult;
}

void VIS::DRIVE::Drive(int dist, float speed){
    int pointX = cos(position().theta)*dist;
    int pointY = sin(position().theta)*dist;
    chassis.moveToPose(pointX, pointY, position().theta, 8000, {.maxSpeed = speed});
}

void VIS::DRIVE::Drive_to_point(float X, float Y){
    chassis.moveToPoint(X, Y, ToPointTimeout);
}

void VIS::DRIVE::Drive_to_point(float X, float Y, float maxspeed){
    chassis.moveToPoint(X, Y, calcTimoutDrive(X-position().x, Y-position().y, maxspeed), {.maxSpeed = maxspeed});
}

void VIS::DRIVE::Drive_to_point_and_face(float X, float Y, int angle){
    chassis.moveToPose(X, Y, angle, ToPointTimeout);
}

void VIS::DRIVE::Drive_to_point_and_face(float X, float Y, int angle, float maxspeed){
    chassis.moveToPose(X, Y, angle, calcTimoutDrive(X-position().x, Y-position().y, maxspeed), {.maxSpeed = maxspeed});
}

void VIS::DRIVE::Drive_to_point_and_face(float X, float Y, float X2, float Y2){
    chassis.moveToPoint(X, Y, ToPointTimeout);
    chassis.turnToPoint(X2, Y2, ToPointTimeout);
}

void VIS::DRIVE::Drive_to_point_and_face(float X, float Y, float X2, float Y2, float DriveMaxSpeed, int TurnMaxSpeed){
    chassis.moveToPoint(X, Y, calcTimoutDrive(X-position().x, Y-position().y, DriveMaxSpeed), {.maxSpeed = DriveMaxSpeed});
    chassis.turnToPoint(X2, Y2, 4000, {.maxSpeed = TurnMaxSpeed});
}

void VIS::DRIVE::stop(){
    chassis.cancelMotion();
}

void VIS::DRIVE::stopall(){
    chassis.cancelAllMotions();
}
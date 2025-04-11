#include "Visual VEX/LemLib_setup.hpp"
#include "Visual VEX/VISUAL API.hpp" // IWYU pragma: keep
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include <cstdio>
#include <cstdlib>

int ToPointTimeout = 8000;
int timeoutmult = 8000;

int TurnTimeout = 500;
int TurnTimeoutMult = 3;

//---general functions used for autons---

lemlib::Pose position(){//gets robot odom position
    return chassis.getPose();
}

//---timeout calculation---

int CalcTimeout(int angulardist){
    return TurnTimeout + (angulardist*TurnTimeoutMult);
}

int CalcTimeout(int angulardist, int speed){
    return TurnTimeout + (angulardist*TurnTimeoutMult);
}

int calcTimoutDrive(int Xdist, int Ydist, float speed){
    return ((Xdist+Ydist)/2.0)*speed*timeoutmult;
}

//---setup functions---

void VIS::TURN::SETUP::SetTurnTimeoutMinimum(int NewTimeout){
    if (NewTimeout < 100) return;
    TurnTimeout = NewTimeout;
}

void VIS::TURN::SETUP::SetTurnTimeoutMult(int NewTimeout){
    if (NewTimeout < 1) return;
    TurnTimeoutMult = NewTimeout;
}

void VIS::DRIVE::SETUP::Set_ToPoint_timeout(int newtime){
    ToPointTimeout = newtime;
}

void VIS::DRIVE::SETUP::Set_timeout_mult(float newmult){
    timeoutmult = newmult;
}

//-----------------------------------------------Turn functions-----------------------------------------------

void VIS::TURN::turn(int DegToTurn){
    DegToTurn = std::abs(position().theta + DegToTurn);
    chassis.turnToHeading(DegToTurn, CalcTimeout(DegToTurn));
}

void VIS::TURN::turn(int DegToTurn, int maxspeed){
    DegToTurn = std::abs(position().theta + DegToTurn);
    chassis.turnToHeading(DegToTurn, CalcTimeout(DegToTurn, maxspeed), {.maxSpeed = maxspeed});
}

void VIS::TURN::Turn_to_Heading(int TargetHeading){
    int TOut = std::abs(position().theta - TargetHeading);
    chassis.turnToHeading(TargetHeading, CalcTimeout(TOut));
}

void VIS::TURN::Turn_to_Heading(int TargetHeading, int maxspeed){
    int TOut = std::abs(position().theta - TargetHeading);
    chassis.turnToHeading(TargetHeading, CalcTimeout(TOut, maxspeed), {.maxSpeed = maxspeed});
}

void VIS::TURN::Turn_to_Point(float point_x, float point_y){
    chassis.turnToPoint(point_x, point_y, 4000);
}

void VIS::TURN::Turn_to_Point(float point_x, float point_y, int maxspeed){
    chassis.turnToPoint(point_x, point_y, 4000, {.maxSpeed = maxspeed});
}

void VIS::TURN::right_swing(float heading_to_end){
    chassis.swingToHeading(heading_to_end, lemlib::DriveSide::RIGHT, 8000);
}

void VIS::TURN::left_swing(float heading_to_end){
    chassis.swingToHeading(heading_to_end, lemlib::DriveSide::LEFT, 8000);
}

void VIS::TURN::waitfor(float value_to_wait_for){
    chassis.waitUntil(value_to_wait_for);
}

//-----------------------------------------------Drive functions-----------------------------------------------

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

//-----------------------------------------------Other functions-----------------------------------------------

void VIS::DRIVE::stop(){
    chassis.cancelMotion();
}

void VIS::DRIVE::stopall(){
    chassis.cancelAllMotions();
}

void VIS::DRIVE::runodomfile(const asset file, int lookAhead){
    chassis.follow(file, 4, 999999999);
}
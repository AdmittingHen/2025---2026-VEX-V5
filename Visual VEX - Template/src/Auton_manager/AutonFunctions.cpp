#include "Visual VEX/LemLib_setup.hpp"
#include "Visual VEX/VISUAL API.hpp" // IWYU pragma: keep
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include <cmath>
#include <cstdio>
#include <cstdlib>

int ToPointTimeout = 8000;
int timeoutmult = 8000;

int TurnTimeout = 500;
int TurnTimeoutMult = 3;

lemlib::Pose VIS::position(){//gets robot odom position
    return chassis.getPose();
}

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

void VIS::TURN::turn(double DegToTurn){
    lemlib::AngularDirection turndir = DegToTurn < 0? lemlib::AngularDirection::CCW_COUNTERCLOCKWISE : lemlib::AngularDirection::CW_CLOCKWISE;
    DegToTurn = position().theta + DegToTurn;
    int deltaang = DegToTurn;
    if (abs(int(DegToTurn)) > 360){
        if (DegToTurn < 0){
            DegToTurn = DegToTurn+(360*floor(double(abs(int(DegToTurn)))/360));
        } else {
            DegToTurn = DegToTurn-(360*floor(double(abs(int(DegToTurn)))/360));
        }
    } else {
        if (DegToTurn < 0){
            DegToTurn = DegToTurn+360;
        }
    }
    chassis.turnToHeading(DegToTurn, 9000, {.direction = turndir});
    chassis.waitUntilDone();
}

void VIS::TURN::turn(double DegToTurn, int maxspeed){
    lemlib::AngularDirection turndir = DegToTurn < 0? lemlib::AngularDirection::CCW_COUNTERCLOCKWISE : lemlib::AngularDirection::CW_CLOCKWISE;
    DegToTurn = position().theta + DegToTurn;
    int deltaang = DegToTurn;
    if (abs(int(DegToTurn)) > 360){
        if (DegToTurn < 0){
            DegToTurn = DegToTurn+(360*floor(double(abs(int(DegToTurn)))/360));
        } else {
            DegToTurn = DegToTurn-(360*floor(double(abs(int(DegToTurn)))/360));
        }
    } else {
        if (DegToTurn < 0){
            DegToTurn = DegToTurn+360;
        }
    }
    chassis.turnToHeading(DegToTurn, 9000, {.direction = turndir, .maxSpeed = maxspeed});
    chassis.waitUntilDone();
}

void VIS::TURN::Turn_to_Heading(int TargetHeading){
    chassis.turnToHeading(TargetHeading, 5000);
    chassis.waitUntilDone();
}

void VIS::TURN::Turn_to_Heading(int TargetHeading, int maxspeed){
    chassis.turnToHeading(TargetHeading, 5000, {.maxSpeed = maxspeed});
    chassis.waitUntilDone();
}

void VIS::TURN::Turn_to_Point(float point_x, float point_y){
    chassis.turnToPoint(point_x, point_y, 4000);
    chassis.waitUntilDone();
}

void VIS::TURN::Turn_to_Point(float point_x, float point_y, int maxspeed){
    chassis.turnToPoint(point_x, point_y, 4000, {.maxSpeed = maxspeed});
    chassis.waitUntilDone();
}

void VIS::TURN::right_swing(float heading_to_end){
    chassis.swingToHeading(heading_to_end, lemlib::DriveSide::RIGHT, 8000);
    chassis.waitUntilDone();
}

void VIS::TURN::left_swing(float heading_to_end){
    chassis.swingToHeading(heading_to_end, lemlib::DriveSide::LEFT, 8000);
    chassis.waitUntilDone();
}

void VIS::waitfor(float value_to_wait_for){
    chassis.waitUntil(value_to_wait_for);
}

void VIS::DRIVE::Drive(int dist, float speed){
    chassis.moveToPose(0, dist, position().theta, 8000, {.maxSpeed = speed});
    chassis.waitUntilDone();
}

void VIS::DRIVE::Drive_to_point(float X, float Y){
    chassis.moveToPoint(X, Y, ToPointTimeout);
    chassis.waitUntilDone();
}

void VIS::DRIVE::Drive_to_point(float X, float Y, float maxspeed){
    chassis.moveToPoint(X, Y, 9000, {.maxSpeed = maxspeed});
    chassis.waitUntilDone();
}

void VIS::DRIVE::Drive_to_point_and_face(float X, float Y, int angle){
    chassis.moveToPose(X, Y, angle, ToPointTimeout);
    chassis.waitUntilDone();
}

void VIS::DRIVE::Drive_to_point_and_face(float X, float Y, int angle, float maxspeed){
    chassis.moveToPose(X, Y, angle, 9000, {.maxSpeed = maxspeed});
    chassis.waitUntilDone();
}

void VIS::DRIVE::Drive_to_point_and_face(float X, float Y, float X2, float Y2){
    chassis.moveToPoint(X, Y, ToPointTimeout);
    chassis.waitUntilDone();
    chassis.turnToPoint(X2, Y2, ToPointTimeout);
    chassis.waitUntilDone();
}

void VIS::DRIVE::Drive_to_point_and_face(float X, float Y, float X2, float Y2, float DriveMaxSpeed, int TurnMaxSpeed){
    chassis.moveToPoint(X, Y, 9000, {.maxSpeed = DriveMaxSpeed});
    chassis.turnToPoint(X2, Y2, 4000, {.maxSpeed = TurnMaxSpeed});
    chassis.waitUntilDone();
}

void VIS::DRIVE::stop(){
    chassis.cancelMotion();
    chassis.waitUntilDone();
}

void VIS::DRIVE::stopall(){
    chassis.cancelAllMotions();
    chassis.waitUntilDone();
}

void VIS::DRIVE::runodomfile(const asset file, int lookAhead){
    chassis.follow(file, lookAhead, 999999999);
    chassis.waitUntilDone();
}
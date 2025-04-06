#include "Visual VEX/LemLib_setup.hpp"
#include "Visual VEX/VISUAL_API.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include <cstdlib>

int TurnTimeout = 500;
int TurnTimeoutMult = 3;

lemlib::Pose position(){
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

int CalcTimeout(int angulardist){
    return TurnTimeout + (angulardist*TurnTimeoutMult);
}

int CalcTimeout(int angulardist, int speed){
    return TurnTimeout + (angulardist*TurnTimeoutMult);
}

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
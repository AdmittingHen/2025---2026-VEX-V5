#include "Visual VEX/VISUAL API.hpp"

using namespace VIS::S;

//auton for auton selector data

Auton::Auton() {
    Name = "";
    auton_call = nullptr;
    Desc = "";
}

Auton::Auton(const char* name, const char* desc, std::function<void()> callback) {
    Name = name;
    auton_call = callback;
    Desc = desc;
}

//controllerDC_DATA_STRUCT for holding data about controller disconects

controllerDC_DATA_STRUCT::controllerDC_DATA_STRUCT(){
    S_TIME = 0;
    E_TIME = 0;
    DURATION = std::abs(S_TIME - E_TIME);
}

double controllerDC_DATA_STRUCT::G_START(){
    return S_TIME;
}

double controllerDC_DATA_STRUCT::G_END(){
    return E_TIME;
}

double controllerDC_DATA_STRUCT::G_DURATION(){
    return DURATION;
}

void controllerDC_DATA_STRUCT::S_START(double T){
    S_TIME = T;
}

void controllerDC_DATA_STRUCT::S_END(double T){
    E_TIME = T;
}

void controllerDC_DATA_STRUCT::S_DURATION(){
    DURATION = std::abs(S_TIME - E_TIME);
}
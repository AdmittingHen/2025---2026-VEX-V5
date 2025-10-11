#include "Visual VEX/visual API.hpp"
#include "pros/device.hpp"
#include <cstddef>

using namespace VIS::DeviceDataVT;
//Code for VARTYPE class
VARTYPE::VARTYPE(const char* Name, int Port, std::any DeviceClass, pros::DeviceType DeviceType) {
    NAME = Name;
    PORT = Port;
    DEVICE = DeviceClass;
    DEVICETYPE = DeviceType;
}

pros::DeviceType VARTYPE::G_DEVICETYPE(){return DEVICETYPE;}

std::any VARTYPE::G_DEVICE(){return DEVICE;}

int VARTYPE::G_PORT(){return PORT;}

const char* VARTYPE::G_NAME(){return NAME;}

//Code for ALLDATA class
AllData::AllData(){DEVICES.clear();}

void AllData::AddDevice(VARTYPE newdevice){DEVICES.push_back(newdevice);}

VARTYPE AllData::Getdata(int port){
    return DEVICES[port];
}

std::vector<VARTYPE> AllData::GetSpecDevice(pros::DeviceType dtype){
    std::vector<VARTYPE> returnvar; // just a blank variable to return if nothing is found
    for (int x = 0; x < DEVICES.size(); x++){
        if (DEVICES[x].G_DEVICETYPE() == dtype){
            returnvar.push_back(DEVICES[x]);
        }
    }
    return returnvar;
}
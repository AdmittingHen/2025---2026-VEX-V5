#include "VISUAL_namespace.hpp"
#include <functional>
#include <string>

using namespace VIS::S;

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
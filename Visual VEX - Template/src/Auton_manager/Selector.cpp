#include "Visual VEX/VISUAL API.hpp" // IWYU pragma: keep
#include <vector>

//selector code
VIS::S::AutonSelector::AutonSelector(){
    SelTeam = 1;
    RED_AC = 0;
    BLUE_AC = 0;
    SKILS_AC = 0;
    auton_page_current = 0;
    RED_autons = {};
    BLUE_autons = {};
    SKILS_auton = {};
}
VIS::S::AutonSelector::AutonSelector(std::vector<Auton> RED, std::vector<Auton> BLUE, std::vector<Auton> SKILS){
    SelTeam = 1;
    RED_AC = RED.size();
    BLUE_AC = BLUE.size();
    SKILS_AC = SKILS.size();
    auton_page_current = 0;
    RED_autons = {};
    BLUE_autons = {};
    SKILS_auton = {};
    RED_autons.assign(RED.begin(), RED.end());
    BLUE_autons.assign(BLUE.begin(), BLUE.end());
    SKILS_auton.assign(SKILS.begin(), SKILS.end());
}
  
void VIS::S::AutonSelector::selected_auton_run(){
    if (SelTeam == 3){
        if (SKILS_auton.size()<1) return;
        SKILS_auton[auton_page_current].auton_call();
    }

    if (SelTeam == 2){
        if (BLUE_autons.size()<1) return;
        BLUE_autons[auton_page_current].auton_call();
    }

    if (SelTeam == 1){
        if (RED_autons.size()<1) return;
        RED_autons[auton_page_current].auton_call();
    }
}
  
void VIS::S::AutonSelector::autons_add(std::vector<Auton> RED, std::vector<Auton> BLUE, std::vector<Auton> SKILS){
    RED_AC = RED.size();
    BLUE_AC = BLUE.size();
    SKILS_AC = SKILS.size();
    auton_page_current = 0;
    RED_autons.assign(RED.begin(), RED.end());
    BLUE_autons.assign(BLUE.begin(), BLUE.end());
    SKILS_auton.assign(SKILS.begin(), SKILS.end());
}
#include "Visual VEX/VISUAL_API.hpp" // IWYU pragma: keep
#include "Screen.cpp"
#include "pros/colors.hpp"
#include "pros/rtos.hpp"
#include "pros/screen.h"
#include "pros/screen.hpp"
#include <vector>

int SelTeam = 0;

pros::Color GTC(int team){
    if (team == 3) {
        return pros::Color::green;// Skils color
    }
    if (team == 2){
        return pros::Color::blue; // Blue Team color
    }
    if (team == 1){
        return pros::Color::red;  // Red Team color
    } else {
        return pros::Color::gold; // Nothing
    }
}

//selector code
VIS::S::AutonSelector::AutonSelector(std::vector<Auton> RED, std::vector<Auton> BLUE, std::vector<Auton> SKILS){
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

pros::screen_touch_status_s_t status;

bool autoTest = false;

const char* setarrowtext(int team, bool UParrow){
    std::vector<VIS::S::Auton> red = auton_selector.RED_autons;
    std::vector<VIS::S::Auton> blue = auton_selector.BLUE_autons;
    std::vector<VIS::S::Auton> skils = auton_selector.SKILS_auton;
    int currPage = auton_selector.auton_page_current;
    const char* ret[3] = {"", "", ""};

    if (UParrow){
        if (currPage+1<=red.size()){
            ret[0] = red[currPage+1].Name;
        } else {
            ret[0] = "No auton this way";
        }

        if (currPage+1<=blue.size()){
            ret[1] = blue[currPage+1].Name;
        } else {
            ret[1] = "No auton this way";
        }

        if (currPage+1<=skils.size()){
            ret[2] = skils[currPage+1].Name;
        } else {
            ret[2] = "No auton this way";
        }
    } else {
        if (currPage-1<=0){
            ret[0] = red[currPage-1].Name;
        } else {
            ret[0] = "No auton this way";
        }

        if (currPage-1<=0){
            ret[1] = blue[currPage-1].Name;
        } else {
            ret[1] = "No auton this way";
        }

        if (currPage-1<=0){
            ret[2] = skils[currPage-1].Name;
        } else {
            ret[2] = "No auton this way";
        }
    }
    return ret[team-1];
}

int runto_test_X = 0;
int runto_test_Y = 0;
int runto_test_ang_X = 0;
int runto_test_ang_Y = 0;
bool ang_place = false; // false = place true = angle
bool placeset = false;
bool angleset = false;

void runautotest(int posX, int posY, int point_to_X, int point_to_Y){
    pros::delay(1000);
    double scale = 144.0/230.0;
    VIS::DRIVE::Drive_to_point(posX*scale, posY*scale);
    VIS::TURN::Turn_to_Point(point_to_X*scale, point_to_Y*scale);
}

//static objects
rect TeamPlate(0,0,60, 240, pros::Color::dark_gray);

//togglable selection buttons
rrect RedSelBox(5, 5, 50, 50, 3, pros::Color::dark_grey);
rrect BlueSelBox(5, 55, 50, 50, 3, pros::Color::dark_grey);
rrect SkilsSelBox(5, 105, 50, 50, 3, pros::Color::dark_grey);

//push buttons
arrow up(260, 5, 50, 100, 0);
arrow dn(260, 235, 50, 100, 180);
rect ToNormalMode(250, 0, 40, 40, pros::Color::dark_gray);
rect runTest(295, 0, 40, 40, pros::Color::dark_grey);
rect ang_place_sw(245, 50, 85, 40, pros::Color::dark_grey);

//map
rect VirtualField(5, 5, 230, 230, pros::Color::white);

void updateScreen(){
    int auton_page = auton_selector.auton_page_current;
    std::vector<VIS::S::Auton> RED = auton_selector.RED_autons;
    std::vector<VIS::S::Auton> BLUE = auton_selector.BLUE_autons;
    std::vector<VIS::S::Auton> SKILS = auton_selector.SKILS_auton;
    //changing propertys
    if (SelTeam == 1){RedSelBox.Rect_color(GTC(1));} else {RedSelBox.Rect_color(pros::Color::white_smoke);}
    if (SelTeam == 2){BlueSelBox.Rect_color(GTC(2));} else {BlueSelBox.Rect_color(pros::Color::white_smoke);}
    if (SelTeam == 3){SkilsSelBox.Rect_color(GTC(3));} else {SkilsSelBox.Rect_color(pros::Color::white_smoke);}

    //printing to the screen
    if (autoTest){
        pros::screen::erase();//clears the screen, this is placed as late as posable to reduce screen flikering

        VirtualField.print();
        ToNormalMode.print();
        runTest.print();
        ang_place_sw.print();

        PRINT("Back", 255, 5, pros::Color::white, pros::E_TEXT_MEDIUM);
        PRINT("Run", 300, 5, pros::Color::white, pros::E_TEXT_MEDIUM);

        if (ang_place){
            PRINT("Switch to place selection", 250, 55, pros::Color::white, pros::E_TEXT_MEDIUM);
        } else {
            PRINT("Switch to angle selection", 250, 55, pros::Color::white, pros::E_TEXT_MEDIUM);
        }

        if (placeset){
            if (!ang_place){
                pros::screen::set_pen(pros::Color::red);
            } else {
                pros::screen::set_pen(pros::Color::white);
            }
            pros::screen::draw_circle(runto_test_X, runto_test_Y, 8);
        }

        if (angleset){
            if (ang_place){
                pros::screen::set_pen(pros::Color::red);
            } else {
                pros::screen::set_pen(pros::Color::white);
            }
            pros::screen::draw_circle(runto_test_ang_X, runto_test_ang_Y, 3);
        }
        
        if (placeset && angleset){
            makeline(runto_test_X, runto_test_Y, runto_test_ang_X, runto_test_ang_Y);
        }
    } else {
        pros::screen::erase();//clears the screen, this is placed as late as posable to reduce screen flikering

        TeamPlate.print();
        PRINT("Skils", 20, 60, GTC(3),pros::E_TEXT_MEDIUM_CENTER);
        PRINT("Blue Team", 20, 120, GTC(2), pros::E_TEXT_MEDIUM_CENTER);
        PRINT("Red Team", 20, 180, GTC(1), pros::E_TEXT_MEDIUM_CENTER);
        RedSelBox.print();
        BlueSelBox.print();
        SkilsSelBox.print();

        up.print();
        dn.print();
        PRINT(setarrowtext(SelTeam, true), 260, 10, pros::Color::white, pros::E_TEXT_MEDIUM_CENTER);
        PRINT(setarrowtext(SelTeam, false), 260, 220, pros::Color::white, pros::E_TEXT_MEDIUM_CENTER);
        
        if (SelTeam == 1){
            PRINT(RED[auton_page].Name, 260, 25, pros::Color::white, pros::E_TEXT_MEDIUM_CENTER);
            PRINT(RED[auton_page].Desc, 60, 40, pros::Color::white, pros::E_TEXT_MEDIUM);
        }

        if (SelTeam == 2){
            PRINT(BLUE[auton_page].Name, 260, 25, pros::Color::white, pros::E_TEXT_MEDIUM_CENTER);
            PRINT(BLUE[auton_page].Desc, 60, 40, pros::Color::white, pros::E_TEXT_MEDIUM);
        }

        if (SelTeam == 3){
            PRINT(SKILS[auton_page].Name, 260, 25, pros::Color::white, pros::E_TEXT_MEDIUM_CENTER);
            PRINT(SKILS[auton_page].Desc, 60, 40, pros::Color::white, pros::E_TEXT_MEDIUM);
        }
    }
}

// touch interpretation
pros::touch_event_cb_fn_t onPress(int Xpos, int Ypos){
    if (RedSelBox.Touching(Xpos, Ypos) && !autoTest){SelTeam = 1; auton_selector.auton_page_current = 0;}
    if (BlueSelBox.Touching(Xpos, Ypos) && !autoTest){SelTeam = 2; auton_selector.auton_page_current = 0;}
    if (SkilsSelBox.Touching(Xpos, Ypos) && !autoTest){SelTeam = 3; auton_selector.auton_page_current = 0;}
    if (up.Touching(Xpos, Ypos, false) && !autoTest){
        if (SelTeam == 1 && auton_selector.auton_page_current<auton_selector.RED_autons.size()){
            auton_selector.auton_page_current++;
        }
        if (SelTeam == 2 && auton_selector.auton_page_current<auton_selector.BLUE_autons.size()){
            auton_selector.auton_page_current++;
        }
        if (SelTeam == 3 && auton_selector.auton_page_current<auton_selector.SKILS_auton.size()){
            auton_selector.auton_page_current++;
        }
    }
    if (dn.Touching(Xpos, Ypos, false) && auton_selector.auton_page_current>0 && !autoTest){auton_selector.auton_page_current--;}

    if (ToNormalMode.Touching(Xpos, Ypos) && autoTest){autoTest = false;}
    if (VirtualField.Touching(Xpos, Ypos) && autoTest){
        if (ang_place){
            angleset = true;
            runto_test_ang_X = Xpos;
            runto_test_ang_Y = Ypos;
        } else {
            placeset = true;
            runto_test_X = Xpos;
            runto_test_Y = Ypos;
        }
    }
    if (runTest.Touching(Xpos, Ypos) && autoTest){runautotest(runto_test_X, runto_test_Y, runto_test_ang_X, runto_test_ang_Y);}

    updateScreen();
    return NULL;
}

pros::touch_event_cb_fn_t onHold(int Xpos, int Ypos){
    if (RedSelBox.Touching(Xpos, Ypos)){autoTest = true;}

    updateScreen();
    return NULL;
}

void VIS::S::AutonSelector::auton_print(){
    using namespace VIS::SCREEN::DRAW;
    pros::screen::set_eraser(pros::Color::black);
    TeamPlate.Rect_fill(true);
    ToNormalMode.Rect_fill(true);
    runTest.Rect_fill(true);
    ang_place_sw.Rect_fill(true);

    //touch interpretation
    status = pros::screen::touch_status();
    pros::screen::touch_callback(onPress(status.x, status.y), pros::E_TOUCH_PRESSED);
    pros::screen::touch_callback(onHold(status.x, status.y), pros::E_TOUCH_HELD);
}
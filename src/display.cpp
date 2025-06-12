#include "Visual VEX/VISUAL API.hpp"
#include "Visual VEX\LemLib_setup.hpp"
<<<<<<< Updated upstream
#include "pros/misc.h"
#include <cstdio>
=======
#include "liblvgl/core/lv_disp.h"
#include "liblvgl/core/lv_event.h"
#include "liblvgl/core/lv_obj.h"
#include "liblvgl/core/lv_obj_pos.h"
#include "liblvgl/core/lv_obj_style.h"
#include "liblvgl/misc/lv_area.h"
#include "liblvgl/misc/lv_color.h"
#include "liblvgl/widgets/lv_btn.h"
#include "liblvgl/widgets/lv_label.h"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <vector>
>>>>>>> Stashed changes

VIS::S::AutonSelector auton_selector;

//if you came here from the auton file follow these steps

//for adding an auton go to the end of the line above the team comment
//then type comma > enter/return > {} end

//The first item is the title of the auton, it will show on the next and prev buttons as well as in the desc box
//the second item is the desc, it is a longer string that will be shown as in the desc box only for the selected auton
//The third item is the callback, this is the function the auton will call. You will have to go to Visual VEX/AutonFunc.hpp and add the function deff, then add the code in src/AutonCode.cpp
void VIS::Setup_Autons(){
    auton_selector.autons_add(
    {{"red team test 1", "This is a red team auton function", drivefunc},
          {"red team test 2", "This is another red team function", drivefunc2},
          {"red team  test 3", "This is another test for red", drivefunc},
          {"red team test 4", "This is another test for red team", drivefunc}
    }, // ^^^ Red Team autons ^^^ (this is a team comment)
    {{"blue team test", "This is a blue team auton function", turnfunc},
           {"blue team test 2", "This is another blue team function", turnfunc2}
    }, // ^^^ Blue team autons ^^^
    {{"skils test", "This is a Skils function it has no team", skils},
            {"skils test 2", "This is another Skils function you probably wont ever need another of these", skils2}
<<<<<<< Updated upstream
    } // ^^^ Skils autons ^^^
    );
=======
    }); // ^^^ Skils autons ^^^
>>>>>>> Stashed changes
start();
}


//this is selector display code -- forms the selector

    //these are the colors used by the brain you can change the RGB code for the colors but do not chage the name of the variable
    //colors made by me
    lv_color_t Grey = lv_color_make(70, 70, 70);
    lv_color_t LightGrey = lv_color_make(110, 110, 110);
    lv_color_t RedTeam = lv_color_make(255, 74, 61);
    lv_color_t BlueTeam = lv_color_make(38, 60, 255);
    lv_color_t SkilsTeam = lv_color_make(96, 222, 73);
<<<<<<< Updated upstream
=======
    lv_color_t Yellow = lv_color_make(255, 255, 45);
>>>>>>> Stashed changes
    //end of colors made by me


//don't change code below this line you could really mess somthing up and then I have to try to fix it

//team plate def
lv_obj_t *btnmtx = lv_btnmatrix_create(lv_scr_act());
static const char *buttonmtxlayout[] = {"Red Team", "\n", "Blue Team", "\n", "Skils Team", ""};
    lv_obj_t* rselbox = lv_obj_create(btnmtx);
    lv_obj_t* bselbox = lv_obj_create(btnmtx);
    lv_obj_t* sselbox = lv_obj_create(btnmtx);

//team auton sel def
lv_obj_t *AutoDesc = lv_label_create(lv_scr_act());

//auton selection buttons
lv_obj_t *upbtn = lv_btn_create(lv_scr_act());
    lv_obj_t *nextautoup = lv_label_create(upbtn);
lv_obj_t *dnbtn = lv_btn_create(lv_scr_act());
    lv_obj_t *nextautodn = lv_label_create(dnbtn);

<<<<<<< Updated upstream
    char upbtntext[64];
    char dnbtntext[64];
    char autodesctext[256];

    int minbatterycap = 40;

const char* setERRflags(bool control, int batterycap){
    bool conERR = !control;
    bool batERR = batterycap < minbatterycap;

    if (batERR && conERR){
        return "!|Controler Disconected - Low Battery|!\n";//both errors
    } else {
        if (batERR){
            return "!|Low Battery|!\n";//low battery
        } else if (conERR){
            return "!|Controler Not Conected|!\n";//controler not conected
        } else {
            return "";
        }
    }
=======
//notifaction button
lv_obj_t *notbtn = lv_btn_create(lv_scr_act());
    lv_obj_t *noticon = lv_label_create(notbtn);

    bool showNotif = false;

    //error flags
    bool batERR, conERR, generalERR;
    int portstat[21];
    int conDC_NUM = -1;
    std::vector<VIS::S::controllerDC_DATA_STRUCT> conDC_DATA;

    char upbtntext[64];
    char dnbtntext[64];
    char autodesctext[2048];

    int minbatterycap = 40;

    int OT_inC = 55;

const char* isDT(int x, bool isfordc){
    for (int y = 0; y < 3; y++){
        if (x == abs(rightMotors.get_port(y)) || x == abs(leftMotors.get_port(y))){
            return isfordc? "(DT)":"DT, ";
        }
    }
    return "";
}

const char* setERRtext(){
    static char errbuf[2048];

    snprintf(errbuf, sizeof(errbuf), "Errors: (DT is DriveTrain)\n");

    if (batERR){
        if (pros::c::battery_get_capacity() < 15){
            strncat(errbuf, "The Battery is dead damn it\n", sizeof(errbuf) - strlen(errbuf) - 1);
        } else {
            strncat(errbuf, "Battery Low\n", sizeof(errbuf) - strlen(errbuf) - 1);
        }
    }

    if (conERR){
        strncat(errbuf, "Controller Disconected\n", sizeof(errbuf) - strlen(errbuf) - 1);
    }

    if (conDC_NUM >= 0){
        char temp[128];
        snprintf(temp, sizeof(temp), "(Start and end time is Match clock)");
        for (int x = 0; x < conDC_NUM; x++){
            snprintf(temp, sizeof(temp), "Controller DC Event%d\n   Start Time: %f\n   End Time: %f\n   Duration: %f\n", x+1, conDC_DATA[x].G_START(), conDC_DATA[x].G_END(), conDC_DATA[x].G_DURATION());
            strncat(errbuf, temp, sizeof(errbuf) - strlen(errbuf) - 1);
        }
    }

    for (int x = 0; x < 21; x++){
        if (portstat[x] == 1){
            char temp[64];
            snprintf(temp, sizeof(temp), "Motor %i is Disconected %s\n", x, isDT(x, true));
            strncat(errbuf, temp, sizeof(errbuf) - strlen(errbuf) - 1);
        } else if (portstat[x] == 2){
            char temp[64];
            snprintf(temp, sizeof(temp), "Motor %i is Overheating (%s%i)\n", x, isDT(x, false), int(pros::c::motor_get_temperature(x)));
            strncat(errbuf, temp, sizeof(errbuf) - strlen(errbuf) - 1);
        }
    }
    
    return errbuf;
>>>>>>> Stashed changes
}

void pushud(int btn){
    std::vector<VIS::S::Auton> AUTON = auton_selector.RED_autons;
    int maxpage = auton_selector.RED_AC-1;
    
    if (auton_selector.SelTeam == 1){
        AUTON = auton_selector.RED_autons;
        maxpage = auton_selector.RED_AC-1;
    } else if (auton_selector.SelTeam == 2){
        AUTON = auton_selector.BLUE_autons;
        maxpage = auton_selector.BLUE_AC-1;
    } else if (auton_selector.SelTeam == 3){
        AUTON = auton_selector.SKILS_auton;
        maxpage = auton_selector.SKILS_AC-1;
    }

    // property changing
    if (auton_selector.auton_page_current < maxpage && btn == 1){
        auton_selector.auton_page_current++;
    }

    if (auton_selector.auton_page_current > 0 && btn == 2){
        auton_selector.auton_page_current--;
    }

    int auton_page = auton_selector.auton_page_current;

    if (auton_selector.auton_page_current < maxpage){
        snprintf(upbtntext, sizeof(upbtntext), "Next Auton (%s)", AUTON[auton_page+1].Name);
    } else {
        snprintf(upbtntext, sizeof(upbtntext), "No Auton Here");
    }

    if (auton_selector.auton_page_current > 0){
        snprintf(dnbtntext, sizeof(dnbtntext), "Prev Auton (%s)", AUTON[auton_page-1].Name);
    } else {
        snprintf(dnbtntext, sizeof(dnbtntext), "No Auton Here");
    }

<<<<<<< Updated upstream
    snprintf(autodesctext, sizeof(autodesctext), "%sAuton Title: %s\nDesc: %s", setERRflags(controller.is_connected(), pros::c::battery_get_capacity()), AUTON[auton_page].Name, AUTON[auton_page].Desc);
=======
    if (showNotif){
        lv_obj_clear_flag(dnbtn, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_clear_flag(upbtn, LV_OBJ_FLAG_CLICKABLE);
        snprintf(autodesctext, sizeof(autodesctext), "%s", setERRtext());
    } else {
        lv_obj_add_flag(dnbtn, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_flag(upbtn, LV_OBJ_FLAG_CLICKABLE);
        snprintf(autodesctext, sizeof(autodesctext), "Auton Title: %s\nDesc: %s", AUTON[auton_page].Name, AUTON[auton_page].Desc);
    }
>>>>>>> Stashed changes
    
    lv_label_set_text(nextautoup, upbtntext);
    lv_label_set_text(nextautodn, dnbtntext);
    lv_label_set_text(AutoDesc, autodesctext);
}

void updateScreen(lv_event_t *e){
    lv_obj_t *TD = lv_event_get_target(e);
    uint32_t btnid = lv_btnmatrix_get_selected_btn(TD);

    //logic
    
    if (btnid != LV_BTNMATRIX_BTN_NONE){
        if (lv_btnmatrix_get_btn_text(btnmtx, btnid) == buttonmtxlayout[0]){
            auton_selector.SelTeam = 1;
            auton_selector.auton_page_current = 0;

            lv_obj_clear_flag(rselbox, LV_OBJ_FLAG_HIDDEN);

            lv_obj_add_flag(bselbox, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(sselbox, LV_OBJ_FLAG_HIDDEN);

        } else if (lv_btnmatrix_get_btn_text(btnmtx, btnid) == buttonmtxlayout[2]){
            auton_selector.SelTeam = 2;
            auton_selector.auton_page_current = 0;

            lv_obj_clear_flag(bselbox, LV_OBJ_FLAG_HIDDEN);

            lv_obj_add_flag(rselbox, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(sselbox, LV_OBJ_FLAG_HIDDEN);

        } else if (lv_btnmatrix_get_btn_text(btnmtx, btnid) == buttonmtxlayout[4]){
            auton_selector.SelTeam = 3;
            auton_selector.auton_page_current = 0;

            lv_obj_clear_flag(sselbox, LV_OBJ_FLAG_HIDDEN);

            lv_obj_add_flag(rselbox, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(bselbox, LV_OBJ_FLAG_HIDDEN);

        } else {
            auton_selector.SelTeam = 1;
            lv_obj_add_flag(rselbox, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(bselbox, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(sselbox, LV_OBJ_FLAG_HIDDEN);
        }
        pushud(0);//flags as a null trigger (to bypass the button system)
    }
}

void dnbtnhand(lv_event_t * e){
    pushud(2);//flags as a down trigger
}

void upbtnhand(lv_event_t * e){
    pushud(1);//flags as an up trigger
}

<<<<<<< Updated upstream
void start(){
    pros::Task lvglruntime([](void) {
        bool lastrun = false, lastrunbat = false;
        while (true){
            if (controller.is_connected() != lastrun){pushud(0);}
            if ((pros::c::battery_get_capacity() < minbatterycap) != lastrunbat){pushud(0);}
            pros::delay(20);
=======
void notbtnhand(lv_event_t * e){
    showNotif = !showNotif;
    pushud(0);
}

int M_MOT_PORT[12];

bool checkx(int x){
    for (int y = 0; y < 12; y++){
        if (x == abs(M_MOT_PORT[y])){
            return true;
        }
    }
    return false;
}

void start(){
    for (int x = 0; x < 9; x++){ // this gives me a list in proper format of ports with motors on them
        if (x <= 5){
            //x is less than 6
            M_MOT_PORT[x] = motorports[x] == 0? motorports[1]:motorports[x];//adds your motor ports to the master list
        } else {
            //x must be 6 or greater
            M_MOT_PORT[x] = rightMotors.get_port(x-6);
            M_MOT_PORT[x+3] = leftMotors.get_port(x-6);
        }
    }

    pros::Task errorDetector([](void) { // this is an error detector that trys to find any error in the bot
        bool once;
        bool Gonce = true;
        int s_t = 0;
        int S_MatchTime = pros::millis();//brain time at start of match in milliseconds
        double minTimefordc = 30/1000.0;
        while (true){

            conERR = !controller.is_connected(); // checks if the contoller is conected
            batERR = pros::c::battery_get_capacity() < minbatterycap; // checks for low battery

            if (!pros::competition::is_disabled() && !pros::competition::is_autonomous() && Gonce){
                S_MatchTime = pros::millis();//brain time at start of match in milliseconds +- 30 mills
            }

            if (!pros::competition::is_disabled() && !pros::competition::is_autonomous()){
                if (conERR){
                    if (once){
                        once = false;
                        conDC_NUM++;
                        conDC_DATA.emplace_back();
                        conDC_DATA[conDC_NUM].S_START(S_MatchTime - pros::millis());
                    }
                } else {
                    if (!once){
                        once = true;
                        conDC_DATA[conDC_NUM].S_END(S_MatchTime - pros::millis()/1000.0);
                        conDC_DATA[conDC_NUM].S_START(conDC_DATA[conDC_NUM].G_START()/1000.0);
                        conDC_DATA[conDC_NUM].S_DURATION();

                        conDC_DATA[conDC_NUM].S_END(105-S_MatchTime - pros::millis()/1000.0);
                        conDC_DATA[conDC_NUM].S_START(105-conDC_DATA[conDC_NUM].G_START()/1000.0);

                        if (conDC_DATA[conDC_NUM].G_DURATION()<minTimefordc){
                            conDC_DATA.erase(conDC_DATA.begin() + conDC_NUM);
                            conDC_NUM--;
                        }
                    }
                }
            }

            for (int x = 0; x < 21; x++){
                if (checkx(x)){ // makes sure x is a motor port rather than an IMU or other device, bassed on motors you entered on setup
                    if (pros::c::motor_get_actual_velocity(x) == ENODEV){
                        portstat[x] = 1; // this sets a motor as disconected
                    } else {
                        if (pros::c::motor_get_temperature(x) > OT_inC){
                            if (pros::c::motor_get_temperature(x) > 100){
                                portstat[x] = 1; // this sets a motor as too damn hot
                            } else {
                                portstat[x] = 2; // this sets a motor as DC due to to high temp
                            }
                        } else {
                            portstat[x] = 0; // this tells me the motor is fine, this is also the flag for a port that is not included in the motor list
                        }
                    }
                }
            }

            generalERR = conERR || batERR || conDC_NUM >= 0;
            if (!generalERR){
                for (int x = 0; x < 21; x++){
                    if (portstat[x] != 0){
                        generalERR = true;
                        break;
                    }
                }
            }

            if (generalERR){
                lv_obj_clear_flag(notbtn, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_add_flag(notbtn, LV_OBJ_FLAG_HIDDEN);
                showNotif = false;
            }

            pushud(0);
            pros::delay(30);
>>>>>>> Stashed changes
        }
    });

    //This function sets defulat values for objects on screen

    //Team selection plate creation
    //button matrix
    lv_obj_set_size(btnmtx, 160, 240);
    lv_obj_set_style_bg_color(btnmtx, Grey, LV_STATE_ANY);
    lv_obj_set_style_opa(btnmtx, 100, LV_STATE_ANY);
    lv_btnmatrix_set_map(btnmtx, buttonmtxlayout);
    lv_obj_set_style_bg_color(btnmtx, LightGrey, LV_PART_ITEMS);
    lv_obj_set_style_text_font(btnmtx, &lv_font_montserrat_18, LV_PART_ITEMS);
    lv_obj_add_event_cb(btnmtx, updateScreen, LV_EVENT_ALL, lv_obj_get_user_data(btnmtx));

    //Curently selected team outline
        //red team
            lv_obj_set_size(rselbox, 115, 55);
            lv_obj_align(rselbox, LV_ALIGN_TOP_LEFT, 2, 1);
            lv_obj_set_style_radius(rselbox, 8, LV_PART_MAIN);
            lv_obj_set_style_bg_opa(rselbox, 0, LV_PART_MAIN);
            lv_obj_set_style_border_opa(rselbox, 255, LV_STATE_ANY);
            lv_obj_set_style_border_color(rselbox, RedTeam, LV_PART_MAIN);
            lv_obj_set_style_border_width(rselbox, 4, LV_PART_MAIN);
            lv_obj_add_flag(rselbox, LV_OBJ_FLAG_HIDDEN);

        //blue team
            lv_obj_set_size(bselbox, 115, 55);
            lv_obj_align(bselbox, LV_ALIGN_LEFT_MID, 2, -3);
            lv_obj_set_style_radius(bselbox, 8, LV_PART_MAIN);
            lv_obj_set_style_bg_opa(bselbox, 0, LV_PART_MAIN);
            lv_obj_set_style_border_opa(bselbox, 255, LV_STATE_ANY);
            lv_obj_set_style_border_color(bselbox, BlueTeam, LV_PART_MAIN);
            lv_obj_set_style_border_width(bselbox, 4, LV_PART_MAIN);
            lv_obj_add_flag(bselbox, LV_OBJ_FLAG_HIDDEN);
            
        //skils team
            lv_obj_set_size(sselbox, 115, 55);
            lv_obj_align(sselbox, LV_ALIGN_BOTTOM_LEFT, 2, -6);
            lv_obj_set_style_radius(sselbox, 8, LV_PART_MAIN);
            lv_obj_set_style_bg_opa(sselbox, 0, LV_PART_MAIN);
            lv_obj_set_style_border_opa(sselbox, 255, LV_STATE_ANY);
            lv_obj_set_style_border_color(sselbox, SkilsTeam, LV_PART_MAIN);
            lv_obj_set_style_border_width(sselbox, 4, LV_PART_MAIN);
            lv_obj_add_flag(sselbox, LV_OBJ_FLAG_HIDDEN);

    //auton desc box
    lv_obj_align(AutoDesc, LV_ALIGN_CENTER, 80, 0);
    lv_obj_set_size(AutoDesc, 300, 140);
<<<<<<< Updated upstream
=======
    lv_obj_add_flag(AutoDesc, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(AutoDesc, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_add_flag(AutoDesc, LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    lv_obj_add_flag(AutoDesc, LV_OBJ_FLAG_SCROLL_MOMENTUM);
    lv_obj_add_flag(AutoDesc, LV_OBJ_FLAG_SCROLLABLE);
>>>>>>> Stashed changes

    //auton up button
    lv_obj_set_size(upbtn, 280, 40);
    lv_obj_align(upbtn, LV_ALIGN_TOP_MID, 80, 5);
    lv_obj_add_event_cb(upbtn, upbtnhand, LV_EVENT_RELEASED, nullptr);
        lv_obj_align(nextautoup, LV_ALIGN_CENTER, 0, 0);
        lv_label_set_text(nextautoup, "Next Auton");

    //auton dn button
    lv_obj_set_size(dnbtn, 280, 40);
    lv_obj_align(dnbtn, LV_ALIGN_BOTTOM_MID, 80, -5);
    lv_obj_add_event_cb(dnbtn, dnbtnhand, LV_EVENT_RELEASED, nullptr);
        lv_obj_align(nextautodn, LV_ALIGN_CENTER, 0, 0);
        lv_label_set_text(nextautodn, "Prev Auton");
<<<<<<< Updated upstream
=======

    //notifaction button
    lv_obj_align(notbtn, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_size(notbtn, 35, 140);
    lv_obj_add_event_cb(notbtn, notbtnhand, LV_EVENT_PRESSED, nullptr);
    lv_obj_set_style_bg_opa(notbtn, 150, LV_PART_ANY);
    lv_obj_set_style_bg_color(notbtn, Yellow, LV_PART_MAIN);
        lv_obj_align(noticon, LV_ALIGN_CENTER, 0, 0);
        lv_label_set_text(noticon, "!");
>>>>>>> Stashed changes
}

void VIS::S::run(){
    auton_selector.selected_auton_run();
}
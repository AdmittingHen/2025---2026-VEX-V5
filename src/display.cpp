#include "Visual VEX/VISUAL API.hpp"
#include "Visual VEX\LemLib_setup.hpp"
#include "pros/misc.h"
#include <cstdio>

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
    } // ^^^ Skils autons ^^^
    );
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

    snprintf(autodesctext, sizeof(autodesctext), "%sAuton Title: %s\nDesc: %s", setERRflags(controller.is_connected(), pros::c::battery_get_capacity()), AUTON[auton_page].Name, AUTON[auton_page].Desc);
    
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

void start(){
    pros::Task lvglruntime([](void) {
        bool lastrun = false, lastrunbat = false;
        while (true){
            if (controller.is_connected() != lastrun){pushud(0);}
            if ((pros::c::battery_get_capacity() < minbatterycap) != lastrunbat){pushud(0);}
            pros::delay(20);
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
}

void VIS::S::run(){
    auton_selector.selected_auton_run();
}
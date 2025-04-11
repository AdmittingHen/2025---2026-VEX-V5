#include "pros/screen.hpp"
#include "lemlib/util.hpp"
#include "pros/colors.hpp"
#include "pros/screen.h"
#include "Visual VEX/VISUAL API.hpp" // IWYU pragma: keep
#include <cmath>

//sets pen color
void pencol(pros::Color col){
    pros::screen::set_pen(col);
}

using namespace VIS::SCREEN::DRAW;

//line functions
void makeline(int x1, int y1, int x2, int y2){
    pros::screen::draw_line(x1, y1, x2, y2);
}

void makeline(int x1, int y1, int x2, int y2, pros::Color col){
    pencol(col);
    pros::screen::draw_line(x1, y1, x2, y2);
}

//rect drawing functions
void makerect(int x1, int y1, int width, int height){
    pros::screen::draw_rect(x1, y1, x1 +  width, y1 + height);
}

void makerect(int x1, int y1, int width, int height, bool fill){
    if (fill){
        pros::screen::fill_rect(x1, y1, x1 +  width, y1 + height);
    } else {
        pros::screen::draw_rect(x1, y1, x1 +  width, y1 + height);
    }
}

void makerect(int x1, int y1, int width, int height, pros::Color col){
    pencol(col);
    pros::screen::draw_rect(x1, y1, x1 +  width, y1 + height);
}

void makerect(int x1, int y1, int width, int height, pros::Color col, bool fill){
    pencol(col);
    if (fill){
        pros::screen::fill_rect(x1, y1, x1 +  width, y1 + height);
    } else {
        pros::screen::draw_rect(x1, y1, x1 +  width, y1 + height);
    }
}

//rounded rect functions
void MakeRoundedRect(int x1, int y1, int width, int height, int rounding){
    //sides of rectangle
    pros::screen::draw_line(x1+rounding, y1, (x1+width)-rounding, y1); // top
    pros::screen::draw_line(x1, y1+rounding, x1, (y1+height)-rounding); // left side
    pros::screen::draw_line(x1+width, y1+rounding, x1+width, (y1+height)-rounding); // right side
    pros::screen::draw_line(x1+rounding, y1+height, (x1+width)-rounding, y1+height); // bottom

    //corners
    pros::screen::draw_line(x1+rounding, y1, x1, y1+rounding); // top left
    pros::screen::draw_line(x1, (y1+height)-rounding, x1+rounding, y1+height); // bottom left
    pros::screen::draw_line((x1+width)-rounding, y1+height, x1+width, (y1+height)-rounding); // bottom right
    pros::screen::draw_line((x1+width)-rounding, y1, x1+width, y1+rounding);
}

void MakeRoundedRect(int x1, int y1, int width, int height, int rounding, pros::Color col){
    pencol(col);
    //sides of rectangle
    pros::screen::draw_line(x1+rounding, y1, (x1+width)-rounding, y1); // top
    pros::screen::draw_line(x1, y1+rounding, x1, (y1+height)-rounding); // left side
    pros::screen::draw_line(x1+width, y1+rounding, x1+width, (y1+height)-rounding); // right side
    pros::screen::draw_line(x1+rounding, y1+height, (x1+width)-rounding, y1+height); // bottom

    //corners
    pros::screen::draw_line(x1+rounding, y1, x1, y1+rounding); // top left
    pros::screen::draw_line(x1, (y1+height)-rounding, x1+rounding, y1+height); // bottom left
    pros::screen::draw_line((x1+width)-rounding, y1+height, x1+width, (y1+height)-rounding); // bottom right
    pros::screen::draw_line((x1+width)-rounding, y1, x1+width, y1+rounding);
}

//text printing functions
void PRINT(const char* text, int line, pros::text_format_e_t textfmt){
    pros::screen::print(textfmt, line, text);
}

void PRINT(const char* text, int line, pros::Color col, pros::text_format_e_t textfmt){
    pencol(col);
    pros::screen::print(textfmt, line, text);
}

void PRINT(const char* text, int x, int y, pros::text_format_e_t textfmt){
    pros::screen::print(textfmt, x, y, text);
}

void PRINT(const char* text, int x, int y, pros::Color col, pros::text_format_e_t textfmt){
    pencol(col);
    pros::screen::print(textfmt, x, y, text);
}

//rect class functions

//rect constructor
rect::rect(int x, int y, int width, int height){
    x1=x;
    y1=y;
    x2=x+width;
    y2=y+height;
    w=width;
    h=height;
}

rect::rect(int x, int y, int width, int height, pros::Color col){
    x1=x;
    y1=y;
    x2=x+width;
    y2=y+height;
    w=width;
    h=height;
    color=col;
}

//modyfying rect funcitons
void rect::Rect(int x, int y, int width, int height){
    x=x1;
    y=y1;
    x2=x+width;
    y2=y+height;
    w=width;
    h=height;
}

void rect::Rect(int x, int y, int width, int height, pros::Color col){
    x=x1;
    y=y1;
    x2=x+width;
    y2=y+height;
    w=width;
    h=height;
    color=col;
}

void rect::Rect_x(int x){
    x1=x;
    x2=x+w;
}

void rect::Rect_y(int y){
    y1=y;
    y2=y+h;
}

void rect::Rect_width(int width){
    w=width;
    x2=x1+width;
}

void rect::Rect_height(int height){
    h=height;
    y2=y1+height;
}

void rect::Rect_color(pros::Color col){
    color=col;
}

void rect::Rect_fill(bool Do_fill){
    fill=Do_fill;
}

void rect::print(){
    makerect(x1, x2, w, h, color);
}

bool rect::Touching(int X, int Y){
    return (X>x1 && X<x2 && Y>y1 && Y<y2);
}

//rounded rect class functions

//rounded rect constructor
rrect::rrect(int x, int y, int width, int height, int rounding){
    x1=x;
    y1=y;
    x2=x+width;
    y2=y+height;
    w=width;
    h=height;
    r=rounding;
}

rrect::rrect(int x, int y, int width, int height, int rounding, pros::Color col){
    x1=x;
    y1=y;
    x2=x+width;
    y2=y+height;
    w=width;
    h=height;
    r=rounding;
    color=col;
}

//rounded rect modyfying functions
void rrect::Rect(int x, int y, int width, int height, int rounding){
    x1=x;
    y1=y;
    x2=x+width;
    y2=y+height;
    w=width;
    h=height;
    r=rounding;
}

void rrect::Rect(int x, int y, int width, int height, int rounding, pros::Color col){
    x1=x;
    y1=y;
    x2=x+width;
    y2=y+height;
    w=width;
    h=height;
    r=rounding;
    color=col;
}

void rrect::Rect_x(int x){
    x1=x;
    x2=x+w;
}

void rrect::Rect_y(int y){
    y1=y;
    y2=y+h;
}

void rrect::Rect_width(int width){
    w=width;
    x2=x1+width;
}

void rrect::Rect_height(int height){
    h=height;
    y2=y1+height;
}

void rrect::Rect_color(pros::Color col){
    color=col;
}

void rrect::print(){
    MakeRoundedRect(x1, x2, w, h, r, color);
}

bool rrect::Touching(int X, int Y){
    return (X>x1 && X<x2 && Y>y1 && Y<y2);
}

//arrrow class functions

//constructor
arrow::arrow(int point_x, int point_y, int Tails_Dist, int openingAngle, int angleOffset){
    pX = point_x;
    pY = point_y;
    tdist = Tails_Dist;
    openang = openingAngle;
    angoff = angleOffset-openingAngle/2;
}

arrow::arrow(int point_x, int point_y, int Tails_Dist, int openingAngle, int angleOffset, pros::Color col){
    pX = point_x;
    pY = point_y;
    tdist = Tails_Dist;
    openang = openingAngle;
    angoff = angleOffset-openingAngle/2;
    color = col;
}

void arrow::ResetWith(int point_x, int point_y, int Tails_Dist, int openingAngle, int angleOffset){
    pX = point_x;
    pY = point_y;
    tdist = Tails_Dist;
    openang = openingAngle;
    angoff = angleOffset-openingAngle/2;
}

void arrow::ResetWith(int point_x, int point_y, int Tails_Dist, int openingAngle, int angleOffset, pros::Color col){
    pX = point_x;
    pY = point_y;
    tdist = Tails_Dist;
    openang = openingAngle;
    angoff = angleOffset-openingAngle/2;
    color = col;
}

void arrow::arr_point_x(int point_x){
    pX = point_x;
}

void arrow::arr_point_y(int point_y){
    pY = point_y;
}

void arrow::arr_tail_Dist(int tail_dist){
    tdist = tail_dist;
}

void arrow::arr_tail_openang(int openingAngle){
    openang = openingAngle;
    angoff = angoff-openingAngle/2;
}

void arrow::arr_angleoff(int angle){
    angoff = angle-openang/2;
}

void arrow::arr_color(pros::Color col){
    color = col;
}

void arrow::print(){
    int angoff_rad = lemlib::degToRad(angoff);
    int openang_rad = lemlib::degToRad(openang);
    makeline(pX, pY, (cos(angoff_rad)*tdist)+pX, (sin(angoff_rad)*tdist)+pY);
    makeline(pX, pY, (cos(angoff_rad+openang_rad)*tdist)+pX, (sin(angoff_rad+openang_rad)*tdist)+pY);
}

bool arrow::Touching(int X, int Y, bool dont_check_rect){
    double val = lemlib::radToDeg(atan2(X-pX, Y-pY)); // angle of touch relative to point
    double opp = tdist/tan(lemlib::degToRad(openang/2.0)); // this is the opposite of one side mutli by 2 for full side
    double adjacent = opp/tan(lemlib::degToRad(openang/2.0)); // this is the distance from point to end
    double dist = sqrt(pow(abs(pX-X), 2) + pow(abs(pY-Y), 2)); // dist to touch from point

    if (!dont_check_rect){
        return val>0+angoff && val<180+angoff && dist<tdist && sqrt(pow(adjacent-dist, 2)+pow(opp, 2))<dist;
    } else {
        return angoff>val && val<angoff+openang && dist<adjacent;
    }
}

//this is selector display code -- forms the selector

VIS::S::AutonSelector auton_selector;

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

void start(){
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
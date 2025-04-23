#include "pros/screen.hpp"
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
arrow::arrow(int pX, int pY, int px_out, int px_back, int orientation){
    px = pX;
    py = pY;
    pxout = px_out;
    pxback = px_back;
    ori = orientation;
}

arrow::arrow(int pX, int pY, int px_out, int px_back, int orientation, pros::Color color){
    px = pX;
    py = pY;
    pxout = px_out;
    pxback = px_back;
    ori = orientation;
    col = color;
}

void arrow::point_x(int pX){
    px = pX;
}

void arrow::point_y(int pY){
    py = pY;
}

void arrow::px_out_set(int px_out){
    pxout = px_out;
}

void arrow::px_back_set(int px_back){
    pxback = px_back;
}

void arrow::angle_set(int orientation){//value 0 - 3 dictating the direction
    ori = orientation;
}

void arrow::color_set(pros::Color color){
    col = color;
}

void arrow::print(){
    if (ori == 0){
        makeline(px, py, px+pxout, py+pxback);
        makeline(px, py, px-pxout, py+pxback);
    }

    if (ori == 1){
        makeline(px, py, px+pxout, py-pxback);
        makeline(px, py, px-pxout, py-pxback);
    }

    if (ori == 2){
        makeline(px, py, px-pxback, py+pxout);
        makeline(px, py, px-pxback, py-pxout);
    }

    if (ori == 3){
        makeline(px, py, px+pxback, py+pxout);
        makeline(px, py, px+pxback, py-pxout);
    }
}

bool arrow::Touching(int x, int y){
    bool ret = false;
    if (ori == 0){
        ret = x>px-pxout && x<px+pxout && y>py+pxback && y<py;
    }

    if (ori == 1){
        ret = x>px-pxout && x<px+pxout && y<py+pxback && y>py;
    }

    if (ori == 2){
        ret = x<px && x>px-pxback && y>py-pxout && y<py+pxout;
    }

    if (ori == 3){
        ret = x>px && x<px-pxback && y>py-pxout && y<py+pxout;
    }
    return ret;
}
#include "pros/colors.hpp"
#include "pros/screen.h"

namespace VIS{
    namespace SCREEN{
        namespace DRAW{
            //line drawing functions
            void makeline(int x1, int y1, int x2, int y2);
            void makeline(int x1, int y1, int x2, int y2, pros::Color col);
            //rect drawing functions
            void makerect(int x1, int y1, int width, int height);
            void makerect(int x1, int y1, int width, int height, bool fill);
            void makerect(int x1, int y1, int width, int height, pros::Color col);
            void makerect(int x1, int y1, int width, int height, pros::Color col, bool fill);
            //rounded rect functions
            void MakeRoundedRect(int x1, int y1, int width, int height, int rounding);
            void MakeRoundedRect(int x1, int y1, int width, int height, int rounding, pros::Color col);
            //text printing functions
            void PRINT(const char* text, int line, pros::text_format_e_t textfmt);
            void PRINT(const char* text, int line, pros::Color col, pros::text_format_e_t textfmt);
            void PRINT(const char* text, int x, int y, pros::text_format_e_t textfmt);
            void PRINT(const char* text, int x, int y, pros::Color col, pros::text_format_e_t textfmt);

            class rect{
                public:
                rect(int x, int y, int width, int height);
                rect(int x, int y, int width, int height, pros::Color col);
                void Rect(int x, int y, int width, int height);
                void Rect(int x, int y, int width, int height, pros::Color col);
                void Rect_x(int x);
                void Rect_y(int y);
                void Rect_width(int width);
                void Rect_height(int height);
                void Rect_color(pros::Color col);
                void Rect_fill(bool fill);
                void print();
                bool Touching(int X, int Y);

                private:
                int x1;
                int y1;
                int x2;
                int y2;
                int w;
                int h;
                bool fill = false;
                pros::Color color = pros::Color::white;
            };

            class rrect{
                public:
                rrect(int x, int y, int width, int height, int rounding);
                rrect(int x, int y, int width, int height, int rounding, pros::Color col);
                void Rect(int x, int y, int width, int height, int rounding);
                void Rect(int x, int y, int width, int height, int rounding, pros::Color col);
                void Rect_x(int x);
                void Rect_y(int y);
                void Rect_width(int width);
                void Rect_height(int height);
                void Rect_color(pros::Color col);
                void print();
                bool Touching(int X, int Y);

                private:
                int x1;
                int y1;
                int x2;
                int y2;
                int w;
                int h;
                int r;
                pros::Color color = pros::Color::white;
            };

            class arrow{
                public: 
                arrow(int pX, int pY, int px_out, int px_back, int ori);
                arrow(int pX, int pY, int px_out, int px_back, int ori, pros::Color color);
                void point_x(int pX);
                void point_y(int pY);
                void px_out_set(int px_out);
                void px_back_set(int px_back);
                void angle_set(int angle);
                void color_set(pros::Color color);
                void print();
                bool Touching(int x, int y);

                private:
                int px;
                int py;
                int pxback;
                int pxout;
                int ori;
                pros::Color col = pros::Color::white;
            };
        }
    }
}
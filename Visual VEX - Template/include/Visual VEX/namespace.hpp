#include "main.h" // IWYU pragma: keep

namespace VIS{
    namespace INTERFACE {
        class NON{
            public:
                void set(bool value);
                void toggle();
                bool getState();

            private:
        };
    }
    namespace DRIVE{
        //drive functions
        void Drive(int dist, float speed);
        void Drive_to_point(float X, float Y);
        void Drive_to_point(float X, float Y, float maxspeed);
        void Drive_to_point_and_face(float X, float Y, int angle);
        void Drive_to_point_and_face(float X, float Y, int angle, float maxspeed);
        void Drive_to_point_and_face(float X, float Y, float X2, float Y2);
        void Drive_to_point_and_face(float X, float Y, float X2, float Y2, float DriveMaxSpeed, int TurnMaxSpeed);
        void stop();
        void stopall();
        namespace SETUP {
            void Set_timeout_mult(float newmult);
            void Set_ToPoint_timeout(int newtime);
        }
    } // namespcae VIS::DRIVE

    namespace TURN {
        //turn functions
        void turn(int DegToTurn);
        void turn(int DegToTurn, int maxspeed);
        void Turn_to_Heading(int TargetHeading);
        void Turn_to_Heading(int TargetHeading, int maxspeed);
        void Turn_to_Point(float point_x, float point_y);
        void Turn_to_Point(float point_x, float point_y, int maxspeed);
        void right_swing(float heading_to_end);
        void left_swing(float heading_to_end);
        void waitfor(float value_to_wait_for);
        namespace SETUP{
            //turn value setup functions
            void SetTurnTimeoutMinimum(int NewTimeout);
            void SetTurnTimeoutMult(int NewTimeout);
        }
    } // namespace VIS::TURN

    namespace S {
        class Auton {
            public:
             Auton();
             Auton(const char*, const char*, std::function<void()>);
             const char* Name;
             const char* Desc;
             std::function<void()> auton_call;
            private:
        };

        class AutonSelector {
         public:
          std::vector<Auton> RED_autons;
          std::vector<Auton> BLUE_autons;
          std::vector<Auton> SKILS_auton;
          int auton_page_current;
          int RED_AC, BLUE_AC, SKILS_AC;
          int last_auton_page_current;
          AutonSelector();
          AutonSelector(std::vector<Auton> RED, std::vector<Auton> BLUE, std::vector<Auton> SKILS);
          void selected_auton_run();
          void auton_print();
          void autons_add(std::vector<Auton> RED, std::vector<Auton> BLUE, std::vector<Auton> SKILS);
        };
    }  // namespace ez

    namespace SCREEN{
        namespace DRAW{
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
                arrow(int point_x, int point_y, int Tails_Dist, int openingAngle, int angleOffset);
                arrow(int point_x, int point_y, int Tails_Dist, int openingAngle, int angleOffset, pros::Color col);
                void ResetWith(int point_x, int point_y, int Tails_Dist, int openingAngle, int angleOffset);
                void ResetWith(int point_x, int point_y, int Tails_Dist, int openingAngle, int angleOffsete, pros::Color col);
                void arr_point_x(int point_x);
                void arr_point_y(int point_y);
                void arr_tail_Dist(int tail_dist);
                void arr_tail_openang(int Tail_yDist);
                void arr_angleoff(int angle);
                void arr_color(pros::Color col);
                void print();
                bool Touching(int X, int Y, bool do_rect_check);

                private:
                int pX;
                int pY;
                int tdist;
                int openang;
                int angoff;
                pros::Color color = pros::Color::white;
            };
        } // namespace VIS::SCREEN::DRAW
    } // namespace VIS::SCREEN
} // namespace VIS
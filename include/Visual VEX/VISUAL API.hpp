#include "lemlib/asset.hpp"
#include "lemlib/pose.hpp"
#include "AutonFunc.hpp"
#include "main.h" // IWYU pragma: keep
#include <cstdio>

#pragma once

void start();

namespace VIS{
    void Setup_Autons();
    lemlib::Pose position();
    int CalcTimeout(int angulardist);
    int CalcTimeout(int angulardist, int speed);
    int calcTimoutDrive(int Xdist, int Ydist, float speed);

    namespace INTERFACE {
        class piston{
            public:
                void set(bool value);
                void toggle();
                bool getState();
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
        void runodomfile(const asset, int);
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
        void run();
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
          int SelTeam;
          AutonSelector();
          AutonSelector(std::vector<Auton> RED, std::vector<Auton> BLUE, std::vector<Auton> SKILS);
          void selected_auton_run();
          void autons_add(std::vector<Auton> RED, std::vector<Auton> BLUE, std::vector<Auton> SKILS);
        };
    }  // namespace S
} // namespace VIS
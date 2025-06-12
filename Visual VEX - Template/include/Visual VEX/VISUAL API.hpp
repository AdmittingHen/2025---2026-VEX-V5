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
    
    void waitfor(float value_to_wait_for);
    /*
        waitfor will wait for the current funciton to reach a coresponding value
        (inches, degrees, etc)
    */
    
    namespace DRIVE{
        void Drive(int dist, float speed);
        /*
            Drive simply drives in a line at a speed for a distance
        
            \param dist
                Dist is the dictance in inches the bot will drive

            \param speed
                Speed is the max speed the bot will drive out of 127
        */

        void Drive_to_point(float X, float Y);
        /*
            Drive_to_point will drive to x and y in inches on the field
        
            \param X
                This is the x point in inches that the bot will try to drive to
            
            \param Y
                This is the Y point in inches that the bot will try to drive to 
        */

        void Drive_to_point(float X, float Y, float maxspeed);
        /*
            Drive_to_point will drive to x and y in inches on the field
        
            \param X
                This is the x point in inches that the bot will try to drive to
            
            \param Y
                This is the Y point in inches that the bot will try to drive to 
        
            \param maxspeed
                This is the max speed (0-127) the bot will travel at
        */

        void Drive_to_point_and_face(float X, float Y, int angle);
        /*
            Drive_to_point_and_face will trive to a point and face an angle when it is done

             \param X
                This is the x point in inches that the bot will try to drive to
            
            \param Y
                This is the Y point in inches that the bot will try to drive to 
        
            \param angle
                This is the angle the bot will try to face at the end of driving
        */

        void Drive_to_point_and_face(float X, float Y, int angle, float maxspeed);
        /*
            Drive_to_point_and_face will trive to a point and face an angle when it is done

             \param X
                This is the x point in inches that the bot will try to drive to
            
            \param Y
                This is the Y point in inches that the bot will try to drive to 
        
            \param angle
                This is the angle the bot will try to face at the end of driving

            \param maxspeed
                This is the max speed the bot will use to travel to the point
        */
        void Drive_to_point_and_face(float X, float Y, float X2, float Y2);
        /*
            Drive_to _point_and_face will drive to a point and then face a point

            \param X
                This is the x point to drive to in inches

            \param Y
                This is the y point to drive to in inches

            \param X2
                This is the x point to face in inches
            
            \param Y2
                This is the y point to face in inches
        */

        void Drive_to_point_and_face(float X, float Y, float X2, float Y2, float DriveMaxSpeed, int TurnMaxSpeed);
        /*
            Drive_to _point_and_face will drive to a point and then face a point

            \param X
                This is the x point to drive to in inches

            \param Y
                This is the y point to drive to in inches

            \param X2
                This is the x point to face in inches
            
            \param Y2
                This is the y point to face in inches
            
            \param DriveMaxSpeed
                This will limit the max speed of driving (0-127)

            \param TurnMaxSpeed
                This will limit the max speed of Turning (0-127)
        */

        void stop();
        /*
            stop is quite easy to understand
                it stops the curent motion
        */

        void stopall();
        /*
            stopall does the same for stop but targes the entire plan of events
        */

        void runodomfile(const asset, int lookAhead);
        /*
            runodomfile runs a file giving to the function

            \param asset
                This is the file name that should be located in static folder

            \param lookAhead
                This changes how the far the bot will target
                for motions with need for acuracy use a higher value
                for motions with less need for acuracy use a smaller value
        */
        namespace SETUP {
            void Set_timeout_mult(float newmult);
            void Set_ToPoint_timeout(int newtime);
        }
    } // namespcae VIS::DRIVE

    namespace TURN {
        void turn(double DegToTurn);
        /*
            turn will turn the bot a giving number of degrees

            \param DegToTurn
                This is the amount of degrees the bot will turn
        */

        void turn(double DegToTurn, int maxspeed);
        /*
            turn will turn the bot a giving number of degrees

            \param DegToTurn
                This is the amount of degrees the bot will turn
            
            \param maxspeed
                This is the max speed the bot will turn at (0-127)
        */

        void Turn_to_Heading(int TargetHeading);
        /*
            Turn_to_heading will turn the bot to the givin heading

            \param TargetHeading
                This is the heading target for the bot (0-360)
        */

        void Turn_to_Heading(int TargetHeading, int maxspeed);
        /*
            Turn_to_heading will turn the bot to the givin heading

            \param TargetHeading
                This is the heading target for the bot (0-360)
            
            \param maxspeed
                This is the max speed the bot will turn at (0-127)
        */
        
        void Turn_to_Point(float point_x, float point_y);
        /*
            Turn_to_point will turn to a point

            \param point_x
                This is the x point to face in inches

            \param point_y
                This is the y point to face in inches
        */

        void Turn_to_Point(float point_x, float point_y, int maxspeed);
        /*
            Turn_to_point will turn to a point

            \param point_x
                This is the x point to face in inches

            \param point_y
                This is the y point to face in inches

            \param maxspeed
                This is the max speed the bot will turn at (0-127)
        */

        void right_swing(float heading_to_end);
        /*
            right_swing locks the right motors and spins the left

            \param heading_to_end
                This is the heading that the turn will be ended
        */

        void left_swing(float heading_to_end);
        /*
            left_swing locks the left motors and spins the right

            \param heading_to_end
                This is the heading that the turn will be ended
        */

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
          int SelTeam;
          AutonSelector();
          AutonSelector(std::vector<Auton> RED, std::vector<Auton> BLUE, std::vector<Auton> SKILS);
          void selected_auton_run();
          void autons_add(std::vector<Auton> RED, std::vector<Auton> BLUE, std::vector<Auton> SKILS);
        };

        class controllerDC_DATA_STRUCT{
            public:
                controllerDC_DATA_STRUCT();
                double G_START();
                double G_END();
                double G_DURATION();
                void S_START(double T);
                void S_END(double T);
                void S_DURATION();
            private:
                double S_TIME;//this is start time of match clock in seconds
                double E_TIME;//this is end time of match clock in seconds
                double DURATION;//this is the duration the controller disconcted for in seconds
        };
    }  // namespace S
} // namespace VIS
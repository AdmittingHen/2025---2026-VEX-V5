#include "Visual API.hpp"
#include <optional>
#include <vector>

namespace VIS{
    namespace MASTER{
        namespace Control{
            class PID{
                public:
                    PID(float p, float i, float d);
                    PID(float p, float i, float d, std::optional<float> antiwindup, std::optional<bool> SginFlipReset);
                    void S_target();
                    float Compute();
                    int P,I,D;
                    float ANTIWINDUP = 0;
                    bool SGINFLIPRESET = false;
                private:
                    float err = 0;
            };
        }

        namespace CHASS{
            namespace Tracker{
                class IMU{
                    public:
                    private:
                };

                class TrackWheel{
                    public:
                    private:
                };
            }

            namespace odom {
                class ODOMDATA{
                    public:
                        ODOMDATA();
                        void ODOM_reset();
                        void set(float X, float Y, float Theda);
                        ODOMDATA get();
                        float x, y, theda;
                    private:

                };

                class ODOMCOM{
                    public:
                        ODOMCOM(Tracker::TrackWheel horizEnc, Tracker::TrackWheel vertEnc, Tracker::IMU IMUdevice, ODOMDATA data);
                        const ODOMDATA fetch();
                    private:
                };
            }

            namespace ConSettings{
                class settings{
                    public:
                    private:
                };

                class Curves{
                    public:
                    private:
                };

                class ActiveBrake{
                    public:
                        ActiveBrake(VIS::MASTER::Control::PID leftpid, VIS::MASTER::Control::PID rightpid);
                        std::vector<VIS::MASTER::Control::PID> G_Data();
                    private:
                        std::vector<VIS::MASTER::Control::PID> PIDS;
                };
            }

            namespace CONST{
                namespace WHEEL{
                    constexpr float NEW_2 = 2.125;
                    constexpr float NEW_275 = 2.75;
                    constexpr float OLD_275 = 2.75;
                    constexpr float NEW_275_HALF = 2.744;
                    constexpr float OLD_275_HALF = 2.74;
                    constexpr float NEW_325 = 3.25;
                    constexpr float OLD_325 = 3.25;
                    constexpr float NEW_325_HALF = 3.246;
                    constexpr float OLD_325_HALF = 3.246;
                    constexpr float NEW_4 = 4;
                    constexpr float OLD_4 = 4.18;
                    constexpr float NEW_4_HALF = 3.995;
                    constexpr float OLD_4_HALF = 4.175;
                }
            }

            class DriveTrain{
                public:
                    DriveTrain(pros::MotorGroup leftmotors, pros::MotorGroup rightmotors, VIS::MASTER::CHASS::ConSettings::ActiveBrake AB , float wheelsize, double DriveTrainRPM, double TrackWidth);
                    pros::MotorGroup G_left_motors();
                    pros::MotorGroup G_right_motors();
                    pros::MotorGroup G_all_motors();
                    void S_Speed(double right, double left);
                private:
                    pros::MotorGroup LEFTM;
                    pros::MotorGroup RIGHTM;
                    double DTrpm;
                    double TWidth;
                    float wheelDiameter;
            };

            class chassis{
                public:
                private:
            };
        }
    }
}
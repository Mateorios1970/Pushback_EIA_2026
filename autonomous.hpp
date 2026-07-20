
#include "main.h"
#include <cmath>
#include <iostream>
#include <algorithm>

class Auto {

    public:

        Auto(pros::MotorGroup *motDer, pros::MotorGroup *motLeft, pros::IMU *sensor, 
            pros::Rotation *horizontal, pros::Rotation *vertical, float horizontalOffset, float verticalOffset,
            float kP, float kI, float kD, float dT);
        //Prefer units for calculations are radians and inches, for showing information degrees and inches
        pros::MotorGroup *rightM;
        pros::MotorGroup *leftM;
        pros::IMU        *imu;
        pros::Rotation   *horEnc;
        pros::Rotation   *verEnc;
        float             horOff;
        float             verOff;
        //PID setting 
        float kp;
        float ki;
        float kd;
        float integrative;
        float dt; 
        //imu & tracking calibration
        void calibrate_sensors();
        //auton functions
        void get_poses();
        //square any number 
        float square(float num);
        //Gets the distance between a xf,yf coordinate and the current poses
        float getDist(float xf, float yf);

        void move_to_pose(int x, int y, float heading);

        double wrapToPi(double num);

        float newBound(float oldAng);
        void reset_integrative();

        //Structure to keep global  x,y and rotation position
        
        //!GLOBAL POSES
        double xPos  {};
        double yPos  {};
        double theta {};

        double xPos_p {};
        double yPos_p {};
        double theta_p {};

        double xVel {};
        double yVel {};
        double thetaVel {};
        
        double velMag {};

        double dtvel {};
        double prev_t {};
    private:

        //total distance traveled by the tracking wheels 
        double hDist {};
        double vDist {};

        //Stores previous angles 
        double prevTheta  {};
        double prevHorAng {};
        double prevVerAng {};

        const double to_rad {M_PI/18000.};
        
};

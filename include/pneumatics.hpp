#pragma once
#include "main.h"


class Brazo{

    public: 

        Brazo(pros::Controller *mi_control, pros::ADIDigitalOut *pneu1, 
        pros::ADIDigitalOut *pneu2, pros::ADIDigitalOut *pneu3);

        pros::Controller *control;
        //!CHANGE FOR NEW PNEUMATIC SYSTEMS 
        pros::ADIDigitalOut *pistAnota;
        pros::ADIDigitalOut *pistWill;
        pros::ADIDigitalOut *pistArm;

        void initialize_pneu();
        //Up arm pose func
        void arm_up();
        //Down arm pose func
        void arm_down();

        //Set pneumatic state functions 
        void set_Will(bool state);
        void set_Anota(bool state);
        void set_Arm(bool state);

        bool isAnotaUp = false; 
        bool isArmUp = false;
        bool isWillUp = false;  

};

    
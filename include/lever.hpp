#pragma once
#include "main.h"

class Lever{ 

    public: 
        Lever(pros::Controller *controller, pros::Motor *motor_lever);

        pros::Controller *control;
        pros::Motor *lever;

        void start_Comp();
        void move_lever();
};
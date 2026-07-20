#include "main.h"
#include "lemlib/api.hpp"
#include <cmath>
#include <iostream>
#include "tankdrive.hpp"
#include "intake.hpp"
#include "pneumatics.hpp"
//#include "thunder_params.hpp"
#include "lighthing_params.hpp"
#include "autoMove.hpp"
#include "lever.hpp"


//!Se define el brazo
Brazo arm(&mi_control, &pist1, &pist2, &pist3); //(littleWill, arm, anota)

//!Se define el intake 
Intake intake(&motorInt1, &motorInt2, &mi_control); 

TankDrive tk(&right_m, &left_m,
    &mi_control);

//!Autonomous using lemlib
lemlib::Chassis chassis(drivetrain, linearController, angularController, 
    sensors, &throttleCurve, &steerCurve); // -> CHECK PID SETTINGS

Lever lever(&mi_control, &motor_lever);

//!Autonomous movement
AutoMove auton(&intake, &arm, &chassis);

void initialize() {

	pros::lcd::initialize();
    chassis.calibrate();


	/*pros::Task screenTask([&]() {

        while (true) {

            // print robot location to the brain screen
            pros::lcd::print(0, "X: %.2f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %.2f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %.2f", chassis.getPose().theta); // heading
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            pros::delay(50);
        }

    });*/


}

void autonomous() {

    chassis.setPose(0, 0, 0.);
    auton.startAuton();

}

void opcontrol() {

    intake.set_compOn();
    arm.initialize_pneu();
    tk.oneJoy(); 
    //tk.twoJoy(); //!Para jotica 

}
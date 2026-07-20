#include "main.h" 
#include "lemlib/api.hpp"
#include "intake.hpp"
#include "pneumatics.hpp"

class AutoMove{

    public: 
        AutoMove(Intake *intakee, Brazo *armm, lemlib::Chassis *chassiss);

        Intake *intake;
        Brazo *arm; 
        lemlib::Chassis *chassis;
        void startAuton(); 

};

AutoMove::AutoMove(Intake *intakee, Brazo *arm, lemlib::Chassis *chassis){

    this->intake = intakee;
    this->arm = arm;
    this->chassis = chassis;

}

void AutoMove::startAuton(){
    bool moving = true;
    this->chassis->turnToHeading(90, 800);
    pros::delay(150);
    this->chassis->moveToPoint(32, 0, 1300);
    pros::delay(150);
    this->chassis->turnToHeading(175, 800); 
    pros::delay(300);
    this->arm->set_Will(true);
    pros::delay(300);
    moving = true;
    pros::Task moveIntake{[&]{
        while(moving){
            this->intake->move_intake(2600);
            moving = false;
        }
    }};
    pros::delay(50);
    this->chassis->moveToPoint(32, -20, 1300);
    pros::delay(1500);
    this->chassis->moveToPoint(32, 3, 1300, {.forwards = false}, true);
    pros::delay(150);
    this->arm->set_Will(false);
    pros::delay(300);
    this->chassis->turnToHeading(310, 800);
    pros::delay(200);
    this->chassis->moveToPose(-12, 44, 312, 2300);
    pros::delay(2000);
    this->intake->move_outake(3000);
    pros::delay(200);
    this->chassis->moveToPoint(30, 3, 2000, {.forwards = false}, true);
    pros::delay(150);
    this->chassis->turnToHeading(180, 600);
    pros::delay(150);
    this->arm->set_Will(true);
    pros::delay(300);
    pros::Task moveIntake1{[&]{
        while(moving){
            this->intake->move_intake(2600);
            moving = false;
        }
    }};
    this->chassis->moveToPoint(30, -20, 1300);
    pros::delay(150);
    this->chassis->moveToPoint(30, 3, 1300, {.forwards = false}, true);
    this->chassis->turnToHeading(270, 800);
    pros::delay(150);
    this->arm->set_Will(false);
    pros::delay(100);
    this->intake->move_outake(2000);
    pros::delay(100);
    this->chassis->turnToHeading(180, 800); 
    pros::delay(150);
    this->arm->set_Will(true);
    pros::delay(300);
    pros::Task moveIntake2{[&]{
        while(moving){
            this->intake->move_intake(3000);
            moving = false;
        }
    }};
    pros::delay(100);
    this->chassis->moveToPoint(30, -20, 1300); 
    pros::delay(1000); 
    this->chassis->moveToPoint(30, 3, 1300, {.forwards = false}, true);
    pros::delay(150);
    this->chassis->turnToHeading(0, 800);
    pros::delay(150);
    this->arm->set_Anota(true);
    this->arm->set_Will(false);
    pros::delay(300);
    this->chassis->moveToPoint(30, 35, 1300);
    pros::delay(150);
    this->intake->move_intake(4500);
    pros::delay(300);
    this->chassis = nullptr;
   
}
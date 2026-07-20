#include "lever.hpp" 

Lever::Lever(pros::Controller *controller, pros::Motor *motor_lever){
    this->control = controller;
    this->lever = motor_lever;
}
void Lever::start_Comp(){

    pros::Task lever{[=]{

        if(this->lever == nullptr){
        }
        else{
            while(1){
                if(this->control->get_digital_new_press(DIGITAL_A) == true){
                    this->lever->move_voltage(7000.);
                    pros::delay(900);
                    this->lever->move_voltage(-5000.);
                    pros::delay(800);
                    this->lever->move_voltage(0.);
            }
        }
        }
    }};
}

void Lever::move_lever(){
    this->lever->move_voltage(7000.);
    pros::delay(900);
    this->lever->move_voltage(-5000.);
    pros::delay(800);
    this->lever->move_voltage(0.);
} 
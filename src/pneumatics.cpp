#include "pneumatics.hpp"

Brazo::Brazo(pros::Controller *mi_control, pros::ADIDigitalOut *pneu1, pros::ADIDigitalOut *pneu2, pros::ADIDigitalOut *pneu3){

        this->control = mi_control;

        this->pistWill = pneu1;
        this->pistWill->set_value(false);

        this->pistArm = pneu2;
        this->pistArm->set_value(false);

        this->pistAnota= pneu3;
        this->pistAnota->set_value(false);
    
    };

void Brazo::initialize_pneu(){
    pros::Task lift{[=]{

            while(1){
                if(this->control->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
                    this->isAnotaUp = !this->isAnotaUp;
                    this->pistAnota->set_value(this->isAnotaUp);
            }
            pros::delay(20);
            }
        }};

        pros::Task littleWill{[=]{
            while(1){
                if(this->control->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
                    this->isWillUp = !this->isWillUp;
                    this->pistWill->set_value(this->isWillUp);
            }
            pros::delay(20);
            }
        }};

        pros::Task armAndGate{[=]{
            while(1){
                if(this->control->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
                    this->isArmUp = !this->isArmUp;
                    this->pistArm->set_value(this->isArmUp);
            }
            pros::delay(20);
            }
        }};
}

void Brazo::set_Anota(bool state){
    this->isAnotaUp = state;
    this->pistAnota->set_value(this->isAnotaUp);
}

void Brazo::set_Arm(bool state){
    this->isArmUp = state;
    this->pistArm->set_value(this->isArmUp);
}

void Brazo::set_Will(bool state){
    this->isWillUp = state;
    this->pistWill->set_value(this->isWillUp);
}

#include "intake.hpp"


Intake::Intake(pros::Motor *motor1, pros::Motor *motor2, 
			 pros::Controller *control_intake){ 

	this->control = control_intake;
	this->mot1 = motor1;
	this->mot2 = motor2;
}

void Intake::set_compOn(){


		pros::Task intake{[=]{

			while(1){

				if(this->control->get_digital(DIGITAL_R1) == true ){
					this->mot1->move_velocity(this->vel);
					this->mot2->move_velocity(this->vel);
				}
				else if(this->control->get_digital(DIGITAL_R2) == true){
					this->mot1->move_velocity(-this->vel);
					this->mot2->move_velocity(-this->vel);
				}
				else{
					this->mot1->move_velocity(0.);
					this->mot2->move_velocity(0.);
				}
			pros::delay(20);

		}
	}}; 
}

void Intake::move_intake(uint32_t move_t){

	uint32_t start_time = pros::millis();
	
	while(pros::millis() - start_time < move_t){

		this->mot1->move_voltage(this->volt);
		this->mot2->move_voltage(this->volt);
		pros::delay(20);
	}
	this->mot1->move_voltage(0.);
	this->mot2->move_voltage(0.);
	
};

void Intake::move_outake(int mov_t){
	uint32_t start_time = pros::millis();
	while(pros::millis() - start_time < mov_t){
		this->mot1->move_voltage(-this->volt);
		this->mot2->move_voltage(-this->volt);
		pros::delay(20);
	}
	this->mot1->move_voltage(0.);
	this->mot2->move_voltage(0.);
};



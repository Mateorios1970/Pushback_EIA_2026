#pragma once
#include "main.h"
#include "pneumatics.hpp"



class Intake{ 

	public: 
		Intake(pros::Motor *motor1, pros::Motor *motor2,
			 pros::Controller *control_intake); 

		pros::Controller *control;
		pros::Motor *mot1;
		pros::Motor *mot2; 

		//Movement functions in ms
		void move_intake(uint32_t move_t);
		void move_outake(int move_t);
		void set_compOn();

	
	private: 

		const float vel {600.}; //!CHECK PROPER ORIENTATION
		const float volt {9000.};	

};



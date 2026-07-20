#include "main.h"
#include "lemlib/api.hpp"



class TankDrive{

	public:
		TankDrive(pros::MotorGroup *motorDer, pros::MotorGroup *motorIzq,
				pros::Controller *mi_control);
		

		pros::MotorGroup *right_mot;
		pros::MotorGroup *left_mot;
	
		pros::Controller *control;

		void oneJoy();
		void twoJoy();

		//Mapeo del joystick
		float mapeo(float val, float x, float y, float min, float max);
		//Mapeo function taken from Andres Muñoz, EIA, tqm andy

		float square(float value);
		
		float rightVolt {};
		float leftVolt {};

	private: 	

		//anti drift info
		float x_AD {};
		float y_AD {};
		float prev_time {};
		float velx {};
		float vely {};

		//control var.
		float x {};
		float y {};
		float joyDist {};
		float rotation_speed {};
		float forward_speed {};
		float toMilV {1000.};
		float p_cte {1.};  //Change depending on driver 

};
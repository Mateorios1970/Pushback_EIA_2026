#include "tankdrive.hpp"

TankDrive::TankDrive(pros::MotorGroup *motorDer, pros::MotorGroup *motorIzq,
					pros::Controller *mi_control){
		
		this->right_mot = motorDer;
		this->left_mot  = motorIzq;
		this->control   = mi_control;
		
};

float TankDrive::mapeo(float val, float x, float y, float min, float max){

	return ((val-x)*(max-min)/(y-x) +min);
		
}

float TankDrive::square(float value){

	return value*value;

}

void TankDrive::oneJoy(){

	pros::Task manejo1{[=]{

			while(1){

				this->x = this->control->get_analog(ANALOG_LEFT_X);
				this->y = this->control->get_analog(ANALOG_LEFT_Y);

				this->joyDist = sqrt( (x*x) + (y*y) ) ;
				float newDist {}; 
				//No permite mov. antes de cierto punto del analog 

				if (joyDist < 5 ){
					
					this->right_mot->move_voltage(0.);
					
					this->left_mot->move_voltage(0.);

					pros::delay(10);
					
				}
				else {

					newDist = mapeo(joyDist, 0., 127., 0. , 1. );  

					rotation_speed = toMilV*newDist*p_cte*mapeo(this->x,-127, 127,-1,1 );
					forward_speed  = toMilV*newDist*mapeo(this->y,-127, 127,-1,1 );

					//Change rot_speed multplier depending on driver
					
					this->right_mot->move_voltage(12.*forward_speed - 7.*rotation_speed);		

					this->left_mot->move_voltage(12.*forward_speed + 7.*rotation_speed);
			
				}
				
			pros::delay(15);

			 }
		}};
	
}


void TankDrive::twoJoy(){


	pros::Task manejoJ{[=]{
		
		while(1){

			float left = this->control->get_analog(ANALOG_LEFT_Y);
			float right = this->control->get_analog(ANALOG_RIGHT_Y);
			
			if ( (std::abs(left) < 3) && (std::abs(right) < 3) ){

				this->right_mot->move_voltage(0.);
				this->left_mot->move_voltage(0.);

				pros::delay(10);
			}
			/*else if ( (std::abs(left) < 115) && (std::abs(right) < 115) ){

				float rightJoy = square(mapeo( std::sqrt(right*right), 0., 110., -1., 1.));
				float leftJoy  = square(mapeo(std::sqrt(left*left), 0., 110., -1., 1.));
			
				this->rightVolt = mapeo(right, -127.,127,-12000., 12000.) * rightJoy;
				this->leftVolt   = mapeo(left, -127., 127, -12000., 12000.) * leftJoy; 
			
				this->right_mot->move_voltage(rightVolt);
				this->left_mot->move_voltage(leftVolt);
				pros::delay(10);


			}*/

			else {
				float rightJoy = square(mapeo( std::sqrt(right*right), 0., 127., -1., 1.));
				float leftJoy  = square(mapeo(std::sqrt(left*left), 0., 127., -1., 1.));
			
				this->rightVolt = mapeo(right, -127.,127,-12000., 12000.) * rightJoy;
				this->leftVolt   = mapeo(left, -127., 127, -12000., 12000.) * leftJoy; 
			
				this->right_mot->move_voltage(rightVolt);
				this->left_mot->move_voltage(leftVolt);

				pros::delay(15);
			}

		}
	}};

}

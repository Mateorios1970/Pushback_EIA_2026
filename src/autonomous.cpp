#include "autonomous.hpp"

Auto::Auto(pros::MotorGroup *motDer, pros::MotorGroup *motLeft, pros::IMU *sensor, 
            pros::Rotation *horizontal, pros::Rotation *vertical, float horizontalOffset, float verticalOffset,
          float kP, float kI, float kD, float dT){
        
        this-> rightM   = motDer;
        this-> leftM    = motLeft;
        this-> imu      = sensor;
        this-> horEnc   = horizontal;
        this-> verEnc   = vertical;
        this-> horOff   = horizontalOffset;
        this-> verOff   = verticalOffset; 
        this-> kp       = kP;
        this-> ki       = kI;
        this-> kd       = kD;
        this-> dt       = dT;

        //set odom task

        //!!!! to_rad is for centidegrees not degrees
        
        pros::Task odom{[this]{

            while(1){

            if (this->imu->is_calibrating() == true ) {
                pros::delay(200);
            }
            else{
                
                //Change in heading in radians 
                double curHorAng = float(horEnc->get_position()) * to_rad;          
                double curVerAng = float(-verEnc->get_position()) * to_rad;          
                double curTheta  = this->imu->get_heading() * (100*to_rad);      

                //Checks if the difference of the angle is within the expected boundaries 
                double dTheta = curTheta - prevTheta;
                if (dTheta > M_PI) {
                    dTheta -= 2.0 * M_PI;
                } else if (dTheta < -M_PI) {
                    dTheta += 2.0 * M_PI;
                }
                //Instantaneous displacement dX = dSv - rv*dTheta
                //Checks for the same expected boundaries
                double dF = (curVerAng - prevVerAng) - verOff*dTheta;  

                //Checks for the same expected boundaries

                double dH = (curHorAng - prevHorAng) - horOff*dTheta;

                double dy = dF;
                double dx = dH;

                //Total length traveled stored in local x,y

                this->hDist += dx;
                this->vDist += dy;

                //avg ang converting theta to radians as its stored in degrees
                double avgAng = theta * (100*to_rad) + (dTheta / 2.0);

                //Changes global values of position, converting dTheta back to degrees 
                this->xPos  += dx * std::cos(avgAng) - dy * std::sin(avgAng);
                this->yPos  += dx * std::sin(avgAng) + dy * std::cos(avgAng);
                this->theta =  360. - this->imu->get_heading();

                //! Performing derivative

                this->xVel = (this->xPos - this->xPos_p)/this->dtvel;
                this->yVel = (this->yPos - this->yPos_p)/this->dtvel;
                this->thetaVel = (this->theta - this->theta_p)/this->dtvel;

                this->dtvel = (pros::millis() - this->prev_t);

                //Changes values for new iteration
                this->prevVerAng = curVerAng;
                this->prevHorAng = curHorAng;
                this->prevTheta  = curTheta;
    
                this->xPos_p = this->xPos;
                this->yPos_p = this->yPos;
                this->theta_p = this->theta;

                this->velMag = sqrt(pow(this->xVel,2) + pow(this->yVel,2));

                this->prev_t = pros::millis();
                pros::delay(30);

            }
        }
    }};
         
}

float Auto::square(float num){

    float res = num*num;
    return res;

}

float Auto::getDist(float xf, float yf){

    float dist = sqrt(square(xf - this->xPos) + square(yf - this->yPos));
    return dist;

}

double Auto::wrapToPi(double num){ 

    if (num > M_PI){
        num -= 2*M_PI;
    }
            
    else if (num <= M_PI) {
        num += 2*M_PI;
    }
    return num; 

}

void Auto::reset_integrative(){

    this->integrative = 0.; 

}

void Auto::calibrate_sensors(){

    //reseting sensor 
    this->horEnc->reset_position();
    this->verEnc->reset_position();
    this->imu->reset();
            
            
    while(this->imu->is_calibrating() == true){

        pros::lcd::set_text(0, "Calibrating pls wait love u. ");
        pros::delay(500);
        pros::lcd::set_text(0, "Calibrating pls wait love u.. ");
        pros::delay(500);
        pros::lcd::set_text(0, "Calibrating pls wait love u... ");
        pros::delay(500);

    }

    pros::lcd::print(0, "Sensors are calibrated");

    //setting the current angle of the rotation sensors in radians
    this->prevHorAng = float(horEnc->get_position()) * to_rad;
    this->prevVerAng = float(verEnc->get_position()) * to_rad;

    //Sets the first to be used in calculations as the initial angle in radians 
    this->prevTheta = this->imu->get_heading() * (100*to_rad); //!MAYBE THE REFERENCE POINT HAS TO BE CHANGED DEPENDING ON WHERE DID THE ROBOT START

    //Set the initial coordinates to (0,0,0)
    xPos  = 0.;
    yPos  = 0.;
    theta = 0.;

};


void Auto::get_poses(){

    pros::Task getPoses{[=]{

        //Shows poses every 50 ms
        while(1){

            pros::lcd::print(1, "X: %.2f", this->xPos);
		    pros::lcd::print(2, "Y: %.2f", this->yPos);
		    pros::lcd::print(3, "Theta: %.2f", this->theta);
		    pros::delay(50);

        }
    }};

};

float Auto::newBound(float oldAng){

    float newB {};
    if ( oldAng >= M_PI ){

        newB = oldAng - (2 * M_PI);
    };

    return newB;

}
void Auto::move_to_pose(int x, int y, float heading){

    float xVect = x - this->xPos;
    float yVect = y - this->yPos; 
    float curAng = newBound((int(450. - this->imu->get_heading()) % 360) * (M_PI / 180.)) ;

    //obj ang in radians, (-pi, pi)
    float vectAng = atan2(yVect, xVect);

    

    float error = vectAng - curAng; 
    float prevE {};

    float retrieve {};
    
    while(std::abs(error) > 0.20 ){ 

        float prop = error*this->kp;
        this->integrative =+ std::clamp(double(this->ki*error*this->dt), -1000., 1000.);
        float derv = (this->kd * (error - prevE))/this->dt;

        float res = std::clamp(double(prop + this->integrative + derv), -7000., 7000.);

        this->rightM->move_voltage(res);
        this->leftM->move_voltage(-res);
        pros::delay(50);
        
        prevE = error;
        curAng = newBound((int(450. - this->imu->get_heading()) % 360) * (M_PI / 180.)); 

        error = vectAng - curAng ;

        retrieve = -res;

    }

    this->rightM->move_voltage(retrieve);
    this->leftM->move_voltage(-retrieve);
    pros::delay(400);

    this->rightM->move_voltage(0.);
    this->leftM->move_voltage(0.);
    
    Auto::reset_integrative();

    

    float dist = Auto::getDist(x,y); 

    float curPos = this->verEnc->get_position() * (2*M_PI);
    float objPos = curAng + std::abs(dist); 

    while (std::abs(objPos - curPos) > 1.5){

        this->rightM->move_voltage(12000.);
        this->rightM->move_voltage(12000.);

        curPos = this->verEnc->get_position() * (2*M_PI);

    }

    this->rightM->move_voltage(11000.);
    this->rightM->move_voltage(11000.);
    pros::delay(150);

    this->rightM->move_voltage(0.);
    this->rightM->move_voltage(0.);

};


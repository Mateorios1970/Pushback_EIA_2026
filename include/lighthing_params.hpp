#pragma once
#include "main.h"
#include "lemlib/api.hpp"

const float VYD {-0.8};
const float HXD {2.3};

//!Control 
pros::Controller mi_control(pros::E_CONTROLLER_MASTER); 

//!PUERTO MOTORES DERECHA
int8_t port_m1 {3} ; //
int8_t port_m2 {6} ; // 
int8_t port_m3 {-5} ; // 
int8_t port_m4 {18} ; //

//!PUERTOS MOTORES IZQUIERDA

int8_t port_m6  {-1} ;// 
int8_t port_m7  {8} ; //
int8_t port_m8  {0} ; //
int8_t port_m9  {} ;//  

//!GRUPO DE MOTORES

pros::MotorGroup right_m({port_m1,port_m2, port_m3,port_m4}, 
        pros::MotorGearset::blue);  //! Revisar orientacion de los motores!!

pros::MotorGroup left_m({port_m6,port_m7,port_m8,port_m9},
                pros::MotorGearset::blue); //! Revisar orientacion de los motores!!

//!PUERTOS MOTORES INTAKE
int8_t port_int1 {-9};  //?Mirar la orientacion de motoreeees para que esten synched upp MIRAR PUERTOOOS
int8_t port_int2 {10}; 


pros::Motor motorInt1(port_int1, pros::MotorGearset::blue); //?Mirar la orientacion de motoreeees para que esten synched upp MIRAR PUERTOOOS
pros::Motor motorInt2(port_int2, pros::MotorGearset::blue); //?Mirar la orientacion de motoreeees para que esten synched upp MIRAR PUERTOOOS

//!PUERTOS BRAZO

pros::ADIDigitalOut pist1('G'); //Revisar donde se conecta
pros::ADIDigitalOut pist2('B'); //Revisar donde se conecta, //!Piston anotacion
pros::ADIDigitalOut pist3('H'); //Revisar donde se conecta  //!Piston anotacion


//!MOTOR LEVER

pros::Motor motor_lever(0.); //Revisar puerto y orientacion

//! IMU sensor

pros::Imu imu(20); //CHECK PORTT

// !horizontal & vertical tracking wheel encoder. 


pros::Rotation horizontalEnc(-13); //CHECK PORTT
pros::Rotation verticalEnc(-17); //CHECK PORTT

lemlib::ControllerSettings linearController(3., // proportional gain (kP) HAVE TO TUNE
                                            0, // integral gain (kI)
                                            0.9, // derivative gain (kD)
                                            4, // anti windup
                                            2, // small error range, in inches
                                            1500, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            5500, // large error range timeout, in milliseconds
                                            2.); // maximum acceleration (slew)


// !angular motion controller
lemlib::ControllerSettings angularController(1.502, // proportional gain (kP) HAVE TO TUNE
                                             0, // integral gain (kI)
                                             0.7, // derivative gain (kD)
                                             3, // anti windup
                                             3, // small error range, in degrees
                                             1000, // small error range timeout, in milliseconds
                                             5, // large error range, in degrees
                                             5000, // large error range timeout, in milliseconds
                                             0); // maximum acceleration (slew)


//! input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttleCurve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019); // expo curve gain


lemlib::ExpoDriveCurve steerCurve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019); // expo curve gain

//! TRACKING WHEELS

lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_2, HXD/25.4 );  //Check  OFFSET 
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_2, VYD/25.4);   //Check  OFFSET 


//! LEMLIB DRIVETRAIN
lemlib::Drivetrain drivetrain(&left_m, // left motor group
                              &right_m, // right motor group
                              12.25,
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
                              600, // drivetrain rpm is 600
                              2); // horizontal drift is 2. If we had traction wheels, it would have been 8



//! ODOM SENSORS
lemlib::OdomSensors sensors(&vertical, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            &horizontal, // horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu); // inertial sensor



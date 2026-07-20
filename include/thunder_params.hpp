#pragma once
#include <cstdint>
#include "lemlib/api.hpp"

const float VYD = -24.316;
const float HXD = -72.131;

//!Control 
pros::Controller mi_control(pros::E_CONTROLLER_MASTER); 

//!PUERTO MOTORES DERECHA
int8_t port_m1 {3} ; 
int8_t port_m2 {4} ; 
int8_t port_m3 {10} ; 

pros::Motor mot1 {port_m1};
pros::Motor mot2 {port_m2};
pros::Motor mot3 {port_m3};
pros::Motor mot4 (0);
pros::Motor mot5 (0);

//!PUERTOS MOTORES IZQUIERDA
int8_t port_m6  {-8}  ; 
int8_t port_m7  {-11} ; 
int8_t port_m8  {-12} ; 

pros::Motor mot6(port_m6, pros::MotorGearset::blue);
pros::Motor mot7(port_m7, pros::MotorGearset::blue);
pros::Motor mot8(port_m8, pros::MotorGearset::blue);
pros::Motor mot9 (0);
pros::Motor mot10(0);

//!PUERTOS MOTORES INTAKE

int8_t port_int1 {-2};  //?Mirar la orientacion de motoreeees para que esten synched upp MIRAR PUERTOOOS
int8_t port_int2 {9};

//!Motores intake y annotacion

pros::Motor motorInt1(port_int1, pros::MotorGearset::blue);
pros::Motor motorInt2(port_int2, pros::MotorGearset::blue);
pros::Motor motorInt3(0.);
pros::Motor motorInt4(0.);

//!PUERTO MOTOR LEVER --->NO HAY EN THUNDER 

pros::Motor motor_lever(0);

//!PUERTOS BRAZO

pros::ADIDigitalOut pist1('A'); //Revisar donde se conecta
pros::ADIDigitalOut pist2('B'); //Revisar donde se conecta //!X
pros::ADIDigitalOut pist3('C'); //Revisar donde se conecta, //!L2


//! IMU sensor

pros::Imu imu(-7); //CHECK PORTT

// !horizontal & vertical tracking wheel encoder. 

pros::Rotation horizontalEnc(-5); //CHECK PORTT
pros::Rotation verticalEnc(-16); //CHECK PORTT

lemlib::ControllerSettings linearController(10, // proportional gain (kP) HAVE TO TUNE
                                            3, // integral gain (kI)
                                            160, // derivative gain (kD)
                                            4, // anti windup
                                            1, // small error range, in inches
                                            1500, // small error range timeout, in milliseconds
                                            2, // large error range, in inches
                                            5500, // large error range timeout, in milliseconds
                                            15); // maximum acceleration (slew)


// !angular motion controller
lemlib::ControllerSettings angularController(15, // proportional gain (kP) HAVE TO TUNE
                                             0, // integral gain (kI)
                                             8, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
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
lemlib::Drivetrain drivetrain(nullptr, // left motor group
                              nullptr, // right motor group
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



                            

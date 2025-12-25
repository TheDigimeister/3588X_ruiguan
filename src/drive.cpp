#include "lemlib/chassis/trackingWheel.hpp"
#include "main.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::MotorGroup right_mg({11, 4, 13});    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
pros::MotorGroup left_mg({-9, -15, -17});  // Creates a motor group with forwards port 5 and reversed ports 4 & 6

lemlib::Drivetrain drivetrain(&left_mg, // left motor group
                              &right_mg, // right motor group
                              11.5, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis 96.0/94.136
                              450, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

pros::Rotation vert_odom(-10);
pros::Imu inertial(3);

lemlib::TrackingWheel vertical_tracking_wheel(&vert_odom, lemlib::Omniwheel::NEW_2 * 96.0/100.982, 0.25);

lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &inertial // inertial sensor
);

// PERFECT lateral PID controller
lemlib::ControllerSettings lateral_controller(10.0, // proportional gain (kP)
                                              0.02, // integral gain (kI) // 0.5
                                              67.0, // derivative gain (kD)
                                              2, // anti windup
                                              1, // small error range, in inches
                                              300, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// PERFECT angular PID controller
lemlib::ControllerSettings angular_controller(3, // proportional gain (kP)
                                              0.0, // integral gain (kI) // 0.04
                                              24, // derivative gain (kD)
                                              21, // anti windup
                                              1, // small error range, in degrees
                                              300, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// // angular PID controller
// lemlib::ControllerSettings angular_controller(3, // proportional gain (kP)
//                                               0.01, // integral gain (kI)
//                                               135, // derivative gain (kD)
//                                               24.75, // anti windup
//                                               1, // small error range, in degrees
//                                               100, // small error range timeout, in milliseconds
//                                               3, // large error range, in degrees
//                                               500, // large error range timeout, in milliseconds
//                                               0 // maximum acceleration (slew)
// );



lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);
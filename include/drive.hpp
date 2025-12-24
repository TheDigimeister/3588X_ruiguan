#pragma once

#include "lemlib/chassis/chassis.hpp"
#include "pros/adi.hpp"
#include "pros/ai_vision.hpp"
#include "pros/imu.hpp"
#include "pros/misc.hpp"
#include "pros/vision.hpp"

#define MIDDLESCORE 1
#define LONGSCORE 2
#define TICKLER 3

extern pros::MotorGroup left_mg;
extern pros::MotorGroup right_mg;

extern pros::Rotation odom_sensor;
extern pros::IMU inertial;

extern lemlib::Chassis chassis;

extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;

extern pros::Controller master;

extern pros::AIVision vision;
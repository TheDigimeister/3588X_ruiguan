#pragma once

#include "pros/distance.hpp"
#include "pros/motors.hpp"
#include "pros/adi.hpp"
#include "pros/motor_group.hpp"

extern pros::Distance front_dist;
extern pros::Distance back_dist;
extern pros::Distance left_dist;
extern pros::Distance right_dist;


extern pros::MotorGroup intake;

extern pros::ADIDigitalOut level_1;
extern pros::ADIDigitalOut level_2;
extern pros::ADIDigitalOut matchload;
extern pros::ADIDigitalOut descore;

extern int triple_state;
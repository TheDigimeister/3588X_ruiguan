#include "main.h"
#include "pros/adi.hpp"
#include "pros/ai_vision.hpp"
#include "pros/motor_group.hpp"

pros::Distance front_dist(19);
pros::Distance back_dist(8);
pros::Distance left_dist(20);
pros::Distance right_dist(18);

pros::MotorGroup intake({-1,2});

pros::ADIDigitalOut level_1('A');
pros::ADIDigitalOut level_2('B');
pros::ADIDigitalOut matchload('C');
pros::ADIDigitalOut descore('D');
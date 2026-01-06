#include "main.h"
#include "robot.hpp"

void left9ball() {
    chassis.setPose(positionFromRaycast(back_dist.get() * MM_TO_IN, BACK_DIST_OFFSET, WEST), positionFromRaycast(left_dist.get() * MM_TO_IN, LEFT_DIST_OFFSET, NORTH),90);


    // 9-ball low goal side (37)

    intake.move(127);

    // pick up trio

    chassis.moveToPoint(-18, 28, 250, {.maxSpeed=127, .minSpeed = 60, .earlyExitRange = 36});
    chassis.moveToPoint(-18, 28, 2000, {.maxSpeed = 60, .minSpeed = 60, .earlyExitRange = 8});


    // pick up long goal balls
    
    chassis.moveToPoint(-7, 45, 1200, {.maxSpeed=80, .minSpeed = 5, .earlyExitRange = 3});
    chassis.waitUntil(18);
    matchload.set_value(true);
    pros::delay(100);

    // back up
    chassis.moveToPoint(-20, 36, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 100, .earlyExitRange = 5}, false);
    // matchload.set_value(false);
    intake.move(0);

    // move to goals
    intake.move(127);
    chassis.moveToPoint(-26, 33, 2000, {.forwards = false, .minSpeed=5, .earlyExitRange = 1});
    chassis.turnToHeading(180, 500);
    chassis.moveToPoint(-26, 40, 500, {.forwards=false, .minSpeed=127}, false);
    right_mg.move(-127);
    pros::Task align_score1{[=]{
        while(back_dist.get() > 70) { pros::delay(50);}
    }};
    pros::delay(700);
    left_mg.move(-127);
    pros::delay(1900);


  
    matchload.set_value(true);
    chassis.moveToPoint(-61, 48, 900, {.forwards=true, .maxSpeed=127, .minSpeed = 45, .earlyExitRange=12});
    chassis.moveToPoint(-61, 48, 800, {.forwards=true, .maxSpeed=45, .minSpeed = 45});
    pros::delay(800);

    chassis.moveToPoint(-27, 48.5, 2000, {.forwards=false, .maxSpeed=127});
    chassis.waitUntil(5);
    intake.move(127);
    pros::Task align_score2{[=]{
        while(back_dist.get() > 70) { pros::delay(50);}
    }};
    pros::delay(2000);

    // descore
    matchload.set_value(false);
    chassis.moveToPoint(-46, 37.5, 1500, {.minSpeed=5, .earlyExitRange=1.5});
    // descore.set_value(true);
    chassis.turnToHeading(90, 1000, {.minSpeed=5, .earlyExitRange=1.25});

    chassis.moveToPoint(-7.1, 37.5, 2000, {.forwards=true, .minSpeed = 30, .earlyExitRange = 3});
    chassis.waitUntil(15);
    // descore.set_value(false);
    chassis.turnToHeading(120, 2000);


    



}
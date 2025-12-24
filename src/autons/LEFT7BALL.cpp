#include "main.h"
#include "utils.hpp"

void left7ball() {
    // chassis.setPose(-46.847,-14.278,90);
    chassis.setPose(positionFromRaycast(back_dist.get() * MM_TO_IN, BACK_DIST_OFFSET, WEST), positionFromRaycast(left_dist.get() * MM_TO_IN, LEFT_DIST_OFFSET, NORTH),90);
    // chassis.setPose()


    // 9-ball low goal side (37)

    intake.move(127);

    // pick up trio

    chassis.moveToPoint(-21, 25, 250, {.maxSpeed=127, .minSpeed = 60, .earlyExitRange = 36});
    chassis.moveToPoint(-21, 25, 2000, {.maxSpeed = 60, .minSpeed = 60, .earlyExitRange = 8});
    pros::delay(500);
    chassis.turnToPoint(-45, 48, 500);
    // pick up long goal balls

    // back up
    chassis.moveToPoint(-45, 48, 1500, {.forwards=true, .maxSpeed=127, .minSpeed=5, .earlyExitRange=1});
    matchload.set_value(true);
    chassis.turnToHeading(270, 500, {}, false);
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, WEST), positionFromRaycast(right_dist.get()*MM_TO_IN, RIGHT_DIST_OFFSET, NORTH), chassis.getPose().theta);

    chassis.moveToPoint(-61, 48, 900, {.forwards=true, .maxSpeed=127, .minSpeed = 45, .earlyExitRange=12});
    chassis.moveToPoint(-61, 48, 800, {.forwards=true, .maxSpeed=45, .minSpeed = 45});
    pros::delay(850);
   
    // move to goals
    intake.move(127);
        
    chassis.moveToPoint(-24, 48.5, 2000, {.forwards=false, .maxSpeed=127});
    chassis.waitUntil(5);
    pros::Task align_score2{[=]{
        while(back_dist.get() > 70) { pros::delay(50);}
    }};
    
    pros::delay(2800);

    // descore
    matchload.set_value(false);
    chassis.moveToPoint(-46, 37.5, 1500, {.minSpeed=5, .earlyExitRange=1.5});
    // descore.set_value(true);
    chassis.turnToHeading(90, 700, {.minSpeed=5, .earlyExitRange=1.25});
    chassis.moveToPoint(-11, 37.5, 2000, {.forwards=true, .minSpeed = 30, .earlyExitRange = 3});
    chassis.waitUntil(15.2);
    // descore.set_value(false);
    chassis.turnToHeading(120, 2000);

    



}
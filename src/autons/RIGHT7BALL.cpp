#include "main.h"
#include "pros/rtos.hpp"
#include "robot.hpp"
#include "utils.hpp"

void right7ball() {
    // chassis.setPose(-46.847,-14.278,90);
    chassis.setPose(positionFromRaycast(back_dist.get() * MM_TO_IN, BACK_DIST_OFFSET, WEST), positionFromRaycast(right_dist.get() * MM_TO_IN, RIGHT_DIST_OFFSET, SOUTH),90);
    // chassis.setPose()


    // 7-ball low goal side (31)

    intake.move(127);

    // pick up trio

    chassis.moveToPoint(-22, -26, 250, {.maxSpeed=127, .minSpeed = 60, .earlyExitRange = 36});
    chassis.moveToPoint(-22, -26, 2000, {.maxSpeed = 60, .minSpeed = 60, .earlyExitRange = 4});
    pros::delay(500);
    chassis.turnToPoint(-45, -48, 500);


    // back up
    chassis.moveToPoint(-45, -49, 1000);
    matchload.set_value(true);
    chassis.turnToHeading(270, 500, {}, false);
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, WEST), positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, SOUTH), chassis.getPose().theta);

    chassis.moveToPoint(-61, -48, 900, {.forwards=true, .maxSpeed=127, .minSpeed = 45, .earlyExitRange=12});
    chassis.moveToPoint(-61, -48, 800, {.forwards=true, .maxSpeed=45, .minSpeed = 45});
    pros::delay(800);
    
    
    // move to goals
    intake.move(127);
        
    chassis.moveToPoint(-24, -48.5, 2000, {.forwards=false, .maxSpeed=127});
    chassis.waitUntil(5);
    pros::Task align_score2{[=]{
        while(back_dist.get() > 70) { pros::delay(50);}
    }};
    
    pros::delay(3000);

    // descore
    chassis.moveToPoint(-46, -37.5, 1500, {.minSpeed=5, .earlyExitRange=1.5});
    // descore.set_value(true);
    chassis.turnToHeading(-90, 1000, {.minSpeed=5, .earlyExitRange=1.25});
    chassis.moveToPoint(-17.5, -36.5, 2000, {.forwards=false, .minSpeed = 30, .earlyExitRange = 3});
    chassis.waitUntil(15);
    // descore.set_value(false);
    chassis.turnToHeading(-120, 2000);

    matchload.set_value(false);



}
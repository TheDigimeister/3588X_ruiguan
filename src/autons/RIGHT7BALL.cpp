#include "main.h"
#include "pros/rtos.hpp"
#include "robot.hpp"
#include "utils.hpp"

void right7ball() {

    chassis.setPose(positionFromRaycast(back_dist.get() * MM_TO_IN, BACK_DIST_OFFSET, WEST), positionFromRaycast(right_dist.get() * MM_TO_IN, RIGHT_DIST_OFFSET, SOUTH),90);
    triple_state = TICKLER;
    intake.move(127);


    chassis.moveToPoint(-28, -22, 2000, {.forwards=true, .maxSpeed=127, .minSpeed=5, .earlyExitRange=5}, true);
    chassis.turnToPoint(-55, -45, 1000, {.forwards=true, .maxSpeed=127, .minSpeed=5, .earlyExitRange=5}, true);
    chassis.moveToPoint(-55,-45, 2000, {.forwards=true, .maxSpeed=100, .minSpeed=5, .earlyExitRange=3}, true);
    matchload.set_value(true);
    chassis.turnToHeading(270, 500, {}, false);
    chassis.setPose(positionFromRaycast(front_dist.get() * MM_TO_IN, FRONT_DIST_OFFSET, WEST), positionFromRaycast(left_dist.get() * MM_TO_IN, LEFT_DIST_OFFSET, SOUTH),chassis.getPose().theta);
    chassis.moveToPoint(-65, -48, 700, {.forwards=true, .maxSpeed=80, .minSpeed=45}, true);
    pros::delay(700);
    chassis.turnToHeading(270, 500, {}, false);

    pros::Task align_score2{[=]{
        while(back_dist.get() > 200) { pros::delay(50);}
        intake.move(127);
        triple_state = LONGSCORE;
    }};
    intake.move(0);
    chassis.setPose(chassis.getPose().x, positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, SOUTH), chassis.getPose().theta);
    chassis.moveToPose(-24, -48.3, 270, 3100, {.forwards=false, .maxSpeed=127});
    pros::delay(3100);



    //     // chassis.setPose(-46.847,-14.278,90);
    // chassis.setPose(positionFromRaycast(back_dist.get() * MM_TO_IN, BACK_DIST_OFFSET, WEST), positionFromRaycast(right_dist.get() * MM_TO_IN, RIGHT_DIST_OFFSET, SOUTH),90);
    // // chassis.setPose()


    // // 9-ball low goal side (37)
    // triple_state = TICKLER;
    // intake.move(127);

    // // pick up trio

    // chassis.moveToPoint(-21, -25, 250, {.maxSpeed=127, .minSpeed = 60, .earlyExitRange = 36});
    // chassis.moveToPoint(-21, -25, 2000, {.maxSpeed = 60, .minSpeed = 60, .earlyExitRange = 8});
    // pros::delay(450);
    // chassis.turnToPoint(-54, -47, 1000);
    // // pick up long goal balls

    // // back up
    // chassis.moveToPoint(-54, -47, 800, {.forwards=true, .maxSpeed=127});
    // chassis.moveToPoint(-54, -47, 800, {.forwards=true, .maxSpeed=80});
    // matchload.set_value(true);
    // chassis.turnToHeading(270, 500, {}, false);
    // chassis.setPose(chassis.getPose().x, positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, SOUTH), chassis.getPose().theta);

    // chassis.moveToPoint(-63, -48, 900, {.forwards=true, .maxSpeed=127, .minSpeed = 45, .earlyExitRange=12});
    // chassis.moveToPoint(-65, -48, 500, {.forwards=true, .maxSpeed=80, .minSpeed = 45});
    // pros::delay(500);
   
    // // move to goals
    
    // chassis.turnToHeading(270, 500);
    // chassis.setPose(chassis.getPose().x, positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, SOUTH), chassis.getPose().theta);
    // chassis.moveToPose(-24, -48.5, 270, 2000, {.forwards=false, .maxSpeed=127});
    // pros::Task align_score2{[=]{
    //     while(back_dist.get() > 200) { pros::delay(50);}
    //     triple_state = LONGSCORE;
    // }};
    // pros::delay(2900);

    // descore
    matchload.set_value(false);
    chassis.moveToPoint(-46, -38.25, 1500, {.minSpeed=5, .earlyExitRange=1.5});
    // descore.set_value(true);
    chassis.turnToHeading(270, 700, {.minSpeed=5, .earlyExitRange=1.25});
    chassis.moveToPoint(-13, -38.25, 2000, {.forwards=false, .maxSpeed=90, .minSpeed = 30, .earlyExitRange = 3});
    chassis.waitUntil(15.2);
    // descore.set_value(false);
}
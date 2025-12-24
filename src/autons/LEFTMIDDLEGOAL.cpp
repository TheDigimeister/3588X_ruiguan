#include "main.h"

void leftMiddleGoal(){

    chassis.setPose(positionFromRaycast(back_dist.get() * MM_TO_IN, BACK_DIST_OFFSET, WEST), positionFromRaycast(left_dist.get() * MM_TO_IN, LEFT_DIST_OFFSET, NORTH),90);
    triple_state = TICKLER;
    intake.move(127);

    // chassis.turnToPoint(-22, 22, 1000, {.forwards=true, .maxSpeed=127, .minSpeed=5, .earlyExitRange=5}, true);
    chassis.moveToPoint(-28, 22, 2000, {.forwards=true, .maxSpeed=127, .minSpeed=5, .earlyExitRange=5}, true);
    chassis.turnToPoint(-55, 45, 1000, {.forwards=true, .maxSpeed=127, .minSpeed=5, .earlyExitRange=5}, true);
    chassis.moveToPoint(-55, 45, 2000, {.forwards=true, .maxSpeed=100}, true);
    matchload.set_value(true);
    chassis.turnToHeading(270, 500, {}, false);
    chassis.setPose(positionFromRaycast(front_dist.get() * MM_TO_IN, FRONT_DIST_OFFSET, WEST), positionFromRaycast(right_dist.get() * MM_TO_IN, RIGHT_DIST_OFFSET, NORTH),chassis.getPose().theta);
    chassis.moveToPoint(-65, 48, 700, {.forwards=true, .maxSpeed=80, .minSpeed=45}, true);
    pros::delay(700);
    chassis.turnToHeading(270, 500, {}, false);
    chassis.setPose(positionFromRaycast(front_dist.get() * MM_TO_IN, FRONT_DIST_OFFSET, WEST), positionFromRaycast(right_dist.get() * MM_TO_IN, RIGHT_DIST_OFFSET, NORTH),chassis.getPose().theta);
    // chassis.turnToPoint(-10, 10, 1000, {.forwards=false, .maxSpeed=127, .minSpeed=5, .earlyExitRange=5}, true);
    chassis.moveToPose(-9, 8, 320, 2400, {.forwards=false, .maxSpeed=127}, false);
    matchload.set_value(false);
    intake.move(57);
    triple_state = MIDDLESCORE;
    pros::delay(2000);
    triple_state = TICKLER;
    intake.move(0);
    chassis.turnToPoint(-47, 47, 1000, {.forwards=true, .maxSpeed=127, .minSpeed=5, .earlyExitRange=5}, true);
    chassis.moveToPoint(-47, 47, 2000, {.forwards=true, .maxSpeed=127}, true);
    chassis.turnToHeading(270, 1000, {}, false);
    intake.move(127);
    chassis.setPose(positionFromRaycast(front_dist.get() * MM_TO_IN, FRONT_DIST_OFFSET, WEST), positionFromRaycast(right_dist.get() * MM_TO_IN, RIGHT_DIST_OFFSET, NORTH),chassis.getPose().theta);
    chassis.moveToPoint(-24, 48, 2000, {.forwards=false, .maxSpeed=50}, false);
    triple_state = LONGSCORE;
    pros::delay(800);

    matchload.set_value(false);
    chassis.moveToPoint(-46, 37.5, 1500, {.minSpeed=5, .earlyExitRange=1.5});
    // descore.set_value(true);
    chassis.turnToHeading(90, 700, {.minSpeed=5, .earlyExitRange=1.25});
    chassis.moveToPoint(-11, 37.5, 2000, {.forwards=true, .minSpeed = 30, .earlyExitRange = 3});
    chassis.waitUntil(15.2);
    // descore.set_value(false);
    chassis.turnToHeading(120, 2000);

    intake.move(0);
    
}
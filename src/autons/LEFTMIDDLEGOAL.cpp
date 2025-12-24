#include "main.h"

void leftMiddleGoal(){

    chassis.setPose(positionFromRaycast(back_dist.get() * MM_TO_IN, BACK_DIST_OFFSET, WEST), positionFromRaycast(left_dist.get() * MM_TO_IN, LEFT_DIST_OFFSET, NORTH),90);
    triple_state = TICKLER;
    intake.move(127);

    chassis.turnToPoint(-22, 22, 1000, {.forwards=true, .maxSpeed=127, .minSpeed=5, .earlyExitRange=5}, true);
    chassis.moveToPoint(-22, 22, 2000, {.forwards=true, .maxSpeed=127, .minSpeed=5, .earlyExitRange=5}, true);
    chassis.turnToPoint(-50, 47, 1000, {.forwards=true, .maxSpeed=127, .minSpeed=5, .earlyExitRange=5}, true);
    chassis.moveToPoint(-50, 47, 2000, {.forwards=true, .maxSpeed=127, .minSpeed=5, .earlyExitRange=5}, true);
    chassis.turnToHeading(270, 500, {}, false);
    chassis.setPose(chassis.getPose().x, positionFromRaycast(right_dist.get() * MM_TO_IN, RIGHT_DIST_OFFSET, NORTH),chassis.getPose().theta);
    chassis.moveToPoint(-65, 47, 2000, {.forwards=true, .maxSpeed=127, .minSpeed=5, .earlyExitRange=5}, true);
    pros::delay(1200);
    chassis.turnToPoint(-10, 10, 1000, {.forwards=false, .maxSpeed=127, .minSpeed=5, .earlyExitRange=5}, true);
    chassis.moveToPose(-10, 10, 315, 2000, {.forwards=false, .maxSpeed=127, .minSpeed=5, .earlyExitRange=5}, false);
    triple_state = MIDDLESCORE;
    pros::delay(2000);
    triple_state = TICKLER;
    chassis.turnToPoint(-36, 47, 1000, {.forwards=true, .maxSpeed=127, .minSpeed=5, .earlyExitRange=5}, true);
    chassis.moveToPoint(-36, 47, 2000, {.forwards=true, .maxSpeed=127, .minSpeed=5, .earlyExitRange=5}, true);
    chassis.turnToHeading(270, 500, {}, false);
    chassis.setPose(chassis.getPose().x, positionFromRaycast(right_dist.get() * MM_TO_IN, RIGHT_DIST_OFFSET, NORTH),chassis.getPose().theta);
    chassis.moveToPoint(-24, 47, 2000, {.forwards=true, .maxSpeed=127, .minSpeed=5, .earlyExitRange=5}, false);
    triple_state = LONGSCORE;
    pros::delay(800);

    intake.move(0);
    
}
#include "drive.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/rtos.hpp"
#include "robot.hpp"
#include "utils.hpp"

void skills(){

    chassis.setPose(positionFromRaycast(back_dist.get() * MM_TO_IN, BACK_DIST_OFFSET, WEST), positionFromRaycast(left_dist.get() * MM_TO_IN, LEFT_DIST_OFFSET, NORTH),0);
    descore.set_value(true);
    matchload.set_value(false);
    triple_state = TICKLER;
    intake.move(127);

    // pick up trio
    left_mg.move(70);
    right_mg.move(70);
    pros::delay(1800);
    // 67 derr
    chassis.turnToHeading(90, 1000, {}, false);
    chassis.setPose(positionFromRaycast(back_dist.get() * MM_TO_IN, BACK_DIST_OFFSET, WEST), positionFromRaycast(left_dist.get() * MM_TO_IN, LEFT_DIST_OFFSET, NORTH),chassis.getPose().theta);
    chassis.moveToPose(-29, 31, 90, 2000, {.forwards=true, .maxSpeed=100}, false);
    chassis.setPose(positionFromRaycast(back_dist.get() * MM_TO_IN, BACK_DIST_OFFSET, WEST), positionFromRaycast(left_dist.get() * MM_TO_IN, LEFT_DIST_OFFSET, NORTH),chassis.getPose().theta);

    chassis.turnToHeading(315, 1000, {.direction=lemlib::AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed=80, .minSpeed=5, .earlyExitRange=1}, false);
    
    chassis.moveToPose(-9, 8, 310, 2000, {.forwards=false, .maxSpeed=70}, false);
    // matchload.set_value(true);
    // intake.move(-50);
    // pros::delay(200);
    //old code
    triple_state = MIDDLESCORE;
    intake.move(57);
    left_mg.move(-50);
    right_mg.move(-50);
    pros::delay(200);
    // intake.move(127);
    // pros::delay(200);
    pros::delay(3700);

    triple_state = TICKLER;
    pros::delay(100);
    intake.move(127);

    chassis.turnToPoint(-46, 46, 500, {.minSpeed=5, .earlyExitRange=1});
    matchload.set_value(true);
    chassis.moveToPoint(-46, 46, 1300, {.forwards=true, .maxSpeed=900});
    triple_state = MIDDLESCORE;
    chassis.waitUntil(12);
    descore.set_value(true);
    matchload.set_value(true);
    chassis.turnToHeading(270, 750, {}, false);
    triple_state = TICKLER;
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, WEST), positionFromRaycast(right_dist.get()*MM_TO_IN, RIGHT_DIST_OFFSET, NORTH), chassis.getPose().theta);

    chassis.moveToPoint(-64, 48, 1500, {.forwards=true, .maxSpeed=80, .minSpeed=55});
    pros::delay(1500);
    left_mg.move(-50);
    right_mg.move(-50);
    pros::delay(100);
    left_mg.move(45);
    right_mg.move(45);
    pros::delay(1000);
    matchload.set_value(false);

    chassis.moveToPose(-24, 63, 260, 2000, {.forwards=false, .horizontalDrift=15, .minSpeed=50});
    chassis.moveToPoint(24, 63, 2000, {.forwards=false, .maxSpeed=127, .minSpeed=30, .earlyExitRange=3});
    
    chassis.moveToPoint(36, 49, 1500, {.forwards=false, .maxSpeed=80, .minSpeed=5, .earlyExitRange=1});
    chassis.turnToHeading(90, 1000, {}, false);
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, EAST), positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, NORTH), chassis.getPose().theta);

    pros::Task align_score1{[=]{
    while(back_dist.get() > 200) { pros::delay(50);}
    triple_state = LONGSCORE;
    }};

    chassis.moveToPoint(25, 49, 2300, {.forwards=false, .maxSpeed=80});
    pros::delay(2300);
    intake.move(127);
    matchload.set_value(true);

    triple_state = TICKLER;
    // chassis.turnToHeading(90, 1000, {}, false);
    // chassis.moveToPoint(48, 48, 1000, {.minSpeed=45, .earlyExitRange=5});
    chassis.turnToHeading(90, 1000, {}, false);
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, EAST), positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, NORTH), chassis.getPose().theta);

    chassis.moveToPoint(64, 49, 1500, {.forwards=true, .maxSpeed=70, .minSpeed=55});
    pros::delay(1500);
    left_mg.move(-50);
    right_mg.move(-50);
    pros::delay(100);
    left_mg.move(45);
    right_mg.move(45);
    pros::delay(1000);

    chassis.turnToHeading(90, 1000, {}, false);
    pros::Task align_score2{[=]{
    while(back_dist.get() > 200) { pros::delay(50);}
    triple_state = LONGSCORE;
    }};

    chassis.moveToPoint(25, 49, 2000, {.forwards=false, .maxSpeed=80}, false);
    pros::delay(2000);
    intake.move(127);

    chassis.turnToHeading(90, 1000, {}, false);
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, EAST),positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, NORTH),chassis.getPose().theta);

    matchload.set_value(false);

    chassis.turnToHeading(120, 1000, {}, false);
    chassis.moveToPose(60, 16, 170, 2000, {.horizontalDrift=15, .minSpeed=100}, false);

    triple_state = TICKLER;
    left_mg.move(60);
    right_mg.move(60);
    pros::delay(2000);

    chassis.turnToHeading(90, 1000, {}, false);
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, EAST),positionFromRaycast(right_dist.get()*MM_TO_IN, RIGHT_DIST_OFFSET, SOUTH),chassis.getPose().theta);

    intake.move(-127);
    chassis.moveToPoint(48, -47, 2000, {.forwards=false, .maxSpeed=55});

    chassis.turnToHeading(90, 1000, {.maxSpeed=80}, false);
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, EAST),positionFromRaycast(right_dist.get()*MM_TO_IN, RIGHT_DIST_OFFSET, SOUTH),chassis.getPose().theta);

    // pros::Task align_score6{[=]{
    // while(back_dist.get() > 200) { pros::delay(50);}
    // triple_state = LONGSCORE;
    // intake.move(127);
    // }};
    intake.move(127);
    triple_state = TICKLER;
    matchload.set_value(true);
    chassis.turnToPoint(60, -49, 1500, {.forwards=true, .maxSpeed=67, .minSpeed=50});
    chassis.moveToPoint(60, -49, 2000, {.forwards=true, .maxSpeed=67, .minSpeed=50});
    pros::delay(2000);
    left_mg.move(-50);
    right_mg.move(-50);
    pros::delay(100);
    left_mg.move(45);
    right_mg.move(45);
    pros::delay(1000);

    chassis.moveToPoint(48,-48, 1000, {.forwards=false }, true);
    left_mg.move(50);
    right_mg.move(50);
    pros::delay(200);

    chassis.turnToHeading(90, 1000, {.maxSpeed=80}, false);
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, EAST),positionFromRaycast(right_dist.get()*MM_TO_IN, RIGHT_DIST_OFFSET, SOUTH),chassis.getPose().theta);


    chassis.moveToPose(24, -64, 90, 1000, {.forwards=false, .horizontalDrift=15, .maxSpeed=127, .minSpeed=50});
    matchload.set_value(false);
    chassis.moveToPoint(-24, -72, 3000, {.forwards=false, .minSpeed=20, .earlyExitRange=5});
    triple_state = TICKLER;


    chassis.moveToPoint(-42, -57, 2000, {.forwards=false, .minSpeed=5, .earlyExitRange=1});
    matchload.set_value(true);

    chassis.turnToHeading(270, 1000, {}, false);
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, WEST), positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, SOUTH), chassis.getPose().theta);
    pros::Task align_score3{[=]{
    while(back_dist.get() > 200) { pros::delay(50);}
    triple_state = LONGSCORE;
    }};
    chassis.moveToPoint(-24, -48, 2200, {.forwards=false, .maxSpeed=80});
    pros::delay(2200);

    triple_state = TICKLER;
    chassis.moveToPoint(-62, -48, 2000, {.forwards=true, .maxSpeed=70});
    pros::delay(2000);
    left_mg.move(-50);
    right_mg.move(-50);
    pros::delay(100);
    left_mg.move(45);
    right_mg.move(45);
    pros::delay(1000);
    matchload.set_value(false);

    chassis.turnToPoint(-25, -47.5, 500, {.forwards=false});
    
    pros::Task align_score4{[=]{
    while(back_dist.get() > 200) { pros::delay(50);}
    triple_state = LONGSCORE;
    }};

    chassis.moveToPoint(-25, -48.75, 3000, {.forwards=false, .maxSpeed=900});
    pros::delay(3000);

    triple_state = TICKLER;

    chassis.moveToPose(-39, -0, 0, 1000, {.forwards=true, .horizontalDrift=15, .minSpeed=100}, false);
    chassis.moveToPose(-39, -0, 0, 2000, {.forwards=true, .horizontalDrift=15, .maxSpeed=50}, false);
    chassis.turnToHeading(270, 750, {.minSpeed=5, .earlyExitRange=3}, false);
    left_mg.move(80);
    right_mg.move(80);
    pros::delay(1000);

    left_mg.move(0);
    right_mg.move(0);

}
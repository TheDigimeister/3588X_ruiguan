#include "drive.hpp"
#include "main.h"

void soloAWP(){
    chassis.setPose(positionFromRaycast(left_dist.get() * MM_TO_IN, LEFT_DIST_OFFSET, WEST), positionFromRaycast(back_dist.get() * MM_TO_IN, BACK_DIST_OFFSET, SOUTH),0);
    triple_state = TICKLER;
    intake.move(127);
    
    // push alliance
    left_mg.move(100);
    right_mg.move(100);
    pros::delay(200);
    left_mg.move(0);
    right_mg.move(0);
    pros::delay(300);
    
    // SW matchload
    chassis.moveToPoint(-52,-47, 2000, {.forwards=false, .maxSpeed=100, .minSpeed=5, .earlyExitRange=1}, true);
    pros::delay(500);
    matchload.set_value(true);
    chassis.turnToHeading(270, 500, {}, false);
    chassis.setPose(positionFromRaycast(front_dist.get() * MM_TO_IN, FRONT_DIST_OFFSET, WEST), positionFromRaycast(left_dist.get() * MM_TO_IN, LEFT_DIST_OFFSET, SOUTH),chassis.getPose().theta);
    
    chassis.moveToPoint(-62, -47.9, 600, {.forwards=true, .maxSpeed=60, .minSpeed=45}, true);
    pros::delay(400);

    // SW long goal score
    chassis.turnToHeading(270, 500, {}, false);
    

    pros::Task align_score1{[=]{
        while(back_dist.get() > 200) { pros::delay(50);}
        intake.move(127);
        triple_state = LONGSCORE;
    }};
    intake.move(0);
    chassis.setPose(chassis.getPose().x, positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, SOUTH), chassis.getPose().theta);
    chassis.moveToPose(-24, -50, 270, 2500, {.forwards=false, .maxSpeed=127, .minSpeed=50});
    pros::delay(2500);
    triple_state = TICKLER;
    matchload.set_value(false);
    
    // SW trio grab
    chassis.turnToHeading(0,800,{}, false);
    chassis.setPose(positionFromRaycast(left_dist.get() * MM_TO_IN, LEFT_DIST_OFFSET, WEST), positionFromRaycast(back_dist.get() * MM_TO_IN, BACK_DIST_OFFSET, SOUTH),chassis.getPose().theta);
    chassis.moveToPoint(-24, -24, 2000, {.forwards=true, .maxSpeed=127, .minSpeed=127, .earlyExitRange=5}, true);

    // NW trio grab
    chassis.moveToPoint(-24, 18, 2000, {.forwards=true, .maxSpeed=127}, true);

    // middle goal score
    chassis.turnToHeading(315, 600, {}, false);
    // left_mg.move(-50);
    // right_mg.move(-50);
    // pros::delay(600);
    // left_mg.move(0);
    // right_mg.move(0);
    chassis.moveToPoint(-10, 2, 500, {.forwards=false, .maxSpeed=127}, false);
    matchload.set_value(false);
    intake.move(0);
    triple_state = MIDDLESCORE;
    intake.move(100);
    pros::delay(500);
    intake.move(-57);
    pros::delay(100);
    intake.move(0);
    triple_state = TICKLER;

    // NW matchload (not doing)
    chassis.moveToPoint(-50,47, 850, {.forwards=true, .maxSpeed=127}, false);
    // matchload.set_value(true);
    // chassis.turnToHeading(270, 500, {}, false);
    // chassis.setPose(positionFromRaycast(front_dist.get() * MM_TO_IN, FRONT_DIST_OFFSET, WEST), positionFromRaycast(right_dist.get() * MM_TO_IN, RIGHT_DIST_OFFSET, NORTH),chassis.getPose().theta);
    // chassis.moveToPoint(-65, 48, 600, {.forwards=true, .maxSpeed=80}, true);
    // pros::delay(400);

    // NW long goal score
    chassis.turnToHeading(270, 500, {}, false);
    chassis.setPose(positionFromRaycast(front_dist.get() * MM_TO_IN, FRONT_DIST_OFFSET, WEST), positionFromRaycast(right_dist.get() * MM_TO_IN, RIGHT_DIST_OFFSET, NORTH),chassis.getPose().theta);

    
    pros::Task align_score2{[=]{
        while(back_dist.get() > 200) { pros::delay(50);}
        intake.move(127);
        triple_state = LONGSCORE;
    }};
    intake.move(0);
    chassis.moveToPoint(-24, 47, 67000, {.forwards=false, .maxSpeed=127});
    pros::delay(67000);
    matchload.set_value(false);
}
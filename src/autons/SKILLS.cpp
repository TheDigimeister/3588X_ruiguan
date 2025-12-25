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
    left_mg.move(60);
    right_mg.move(60);
    pros::delay(1800);
    // 67 derr
    chassis.turnToHeading(90, 1000, {}, false);
    chassis.setPose(positionFromRaycast(back_dist.get() * MM_TO_IN, BACK_DIST_OFFSET, WEST), positionFromRaycast(left_dist.get() * MM_TO_IN, LEFT_DIST_OFFSET, NORTH),chassis.getPose().theta);
    chassis.moveToPose(-29, 31, 90, 2000, {.forwards=true, .maxSpeed=100}, false);
    chassis.setPose(positionFromRaycast(back_dist.get() * MM_TO_IN, BACK_DIST_OFFSET, WEST), positionFromRaycast(left_dist.get() * MM_TO_IN, LEFT_DIST_OFFSET, NORTH),chassis.getPose().theta);

    chassis.turnToHeading(315, 1000, {.direction=lemlib::AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed=80, .minSpeed=5, .earlyExitRange=1}, false);
    chassis.moveToPose(-9, 8, 315, 2000, {.forwards=false, .maxSpeed=70}, false);
    intake.move(0);
    pros::delay(100);
    triple_state = MIDDLESCORE;
    intake.move(57);
    pros::delay(4000);

    triple_state = TICKLER;
    pros::delay(100);
    intake.move(127);

    chassis.moveToPoint(-48, 47, 600, {.forwards=true, .maxSpeed=127});
    matchload.set_value(true);
    chassis.moveToPoint(-48, 47, 400, {.forwards=true, .maxSpeed=80});
    triple_state = MIDDLESCORE;
    chassis.waitUntil(12);
    descore.set_value(true);
    matchload.set_value(true);
    chassis.turnToHeading(270, 750, {}, false);
    triple_state = TICKLER;
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, WEST), positionFromRaycast(right_dist.get()*MM_TO_IN, RIGHT_DIST_OFFSET, NORTH), chassis.getPose().theta);

    //MATCHLOAD ONE
    chassis.moveToPoint(-63, 48.5, 1700, {.forwards=true, .maxSpeed=50, .minSpeed=50});
    pros::delay(1700);
    left_mg.move(-50);
    right_mg.move(-50);
    pros::delay(100);
    left_mg.move(45);
    right_mg.move(45);
    pros::delay(200);
    left_mg.move(45);
    right_mg.move(45);
    pros::delay(800);

    chassis.moveToPose(-24, 63, 260, 2000, {.forwards=false, .horizontalDrift=15, .minSpeed=50});
    
    chassis.moveToPoint(24, 63, 2000, {.forwards=false, .maxSpeed=127, .minSpeed=30, .earlyExitRange=3});
    matchload.set_value(false);
    chassis.moveToPoint(36, 49, 1500, {.forwards=false, .maxSpeed=80, .minSpeed=5, .earlyExitRange=1});
    chassis.turnToHeading(90, 1000, {}, false);
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, EAST), positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, NORTH), chassis.getPose().theta);
    matchload.set_value(true);
    intake.move(-50);
    pros::delay(200);
    intake.move(127);

    pros::Task align_score1{[=]{
        int timeout = 0;
        while(back_dist.get() > 200 && timeout <= 40) { 
            pros::delay(50);
            timeout++;
        }
        triple_state = LONGSCORE;
    }};

    chassis.moveToPoint(23, 48.5, 2300, {.forwards=false, .maxSpeed=80});
    pros::delay(2300);
    intake.move(127);
    
    triple_state = TICKLER;
    // chassis.turnToHeading(90, 1000, {}, false);
    // chassis.moveToPoint(48, 48, 1000, {.minSpeed=45, .earlyExitRange=5});
    chassis.turnToHeading(90, 1000, {}, false);
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, EAST), positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, NORTH), chassis.getPose().theta);

    //MATCHLOAD TWO
    chassis.moveToPoint(63, 48, 2000, {.forwards=true, .maxSpeed=50, .minSpeed=50});
    pros::delay(2000);
    left_mg.move(-50);
    right_mg.move(-50);
    pros::delay(100);
    left_mg.move(45);
    right_mg.move(45);
    pros::delay(1000);

    chassis.turnToHeading(90, 1000, {}, false);

    pros::Task align_score2{[=]{
        int timeout = 0;
        while(back_dist.get() > 200 && timeout <= 40) { 
            pros::delay(50);
            timeout++;
        }
        triple_state = LONGSCORE;
    }};

    chassis.moveToPoint(23, 49, 2200, {.forwards=false, .maxSpeed=80}, false);
    pros::delay(2200);
    intake.move(127);

    chassis.turnToHeading(90, 1000, {}, false);
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, EAST),positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, NORTH),chassis.getPose().theta);

    matchload.set_value(false);

    chassis.turnToHeading(180, 1000, {}, false);
    // chassis.moveToPose(60, 16, 170, 2000, {.horizontalDrift=15, .minSpeed=100}, false);

    // triple_state = TICKLER;
    // left_mg.move(70);
    // right_mg.move(70);
    // pros::delay(1800);

    // chassis.turnToHeading(90, 1000, {}, false);
    // chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, EAST),positionFromRaycast(right_dist.get()*MM_TO_IN, RIGHT_DIST_OFFSET, SOUTH),chassis.getPose().theta);

    // intake.move(-100);
    chassis.moveToPoint(49, -49, 1500, {.forwards=true, .maxSpeed=127});

    chassis.turnToHeading(90, 1000, {.maxSpeed=80}, false);
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, EAST),positionFromRaycast(right_dist.get()*MM_TO_IN, RIGHT_DIST_OFFSET, SOUTH),chassis.getPose().theta);

    // pros::Task align_score6{[=]{
    // while(back_dist.get() > 200) { pros::delay(50);}
    // triple_state = LONGSCORE;
    // intake.move(127);
    // }};
    intake.move(127);
    triple_state = TICKLER;
    //Matchload Three
    matchload.set_value(true);
    chassis.turnToPoint(62, -49, 1500, {.forwards=true, .maxSpeed=127, .minSpeed=50});
    chassis.moveToPoint(62, -49, 2000, {.forwards=true, .maxSpeed=50, .minSpeed=50});
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
    // pros::Task align_score3{[=]{
    // while(back_dist.get() > 200) { pros::delay(50);}
    // triple_state = LONGSCORE;
    // }};

    //SCORE number 3
    pros::Task align_score3{[=]{
        int timeout = 0;
        while(back_dist.get() > 200 && timeout <= 40) { 
            pros::delay(50);
            timeout++;
        }
        triple_state = LONGSCORE;
    }};

    chassis.moveToPoint(-24, -49, 2500, {.forwards=false, .maxSpeed=80});
    pros::delay(2500);
    intake.move(127);

    triple_state = TICKLER;
    //MATCHLOAD FOUR
    chassis.moveToPoint(-62, -48, 2000, {.forwards=true, .maxSpeed=55});
    pros::delay(2000);
    left_mg.move(-50);
    right_mg.move(-50);
    pros::delay(100);
    left_mg.move(45);
    right_mg.move(45);
    pros::delay(1000);
    matchload.set_value(false);

    chassis.turnToPoint(-25, -49, 1000, {.forwards=false});

    //score number 4
    pros::Task align_score4{[=]{
        int timeout = 0;
        while(back_dist.get() > 200 && timeout <= 40) { 
            pros::delay(50);
            timeout++;
        }
        triple_state = LONGSCORE;
    }};

    chassis.moveToPoint(-24, -49, 2200, {.forwards=false, .maxSpeed=80});
    pros::delay(2200);
    intake.move(127);

    // chassis.turnToHeading(90, 1000, {}, false);
    // chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, EAST),positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, NORTH),chassis.getPose().theta);

    // matchload.set_value(false);

    // chassis.turnToHeading(120, 1000, {}, false);
    // chassis.moveToPose(60, 16, 170, 2000, {.horizontalDrift=15, .minSpeed=100}, false);

    // triple_state = TICKLER;
    // left_mg.move(60);
    // right_mg.move(60);
    // pros::delay(800);
    // triple_state = TICKLER;

    chassis.moveToPose(-38, -0, 0, 1100, {.forwards=true, .horizontalDrift=15, .minSpeed=127}, false);
    chassis.moveToPose(-38, -0, 0, 1000, {.forwards=true, .horizontalDrift=15, .maxSpeed=60}, false);
    chassis.turnToHeading(270, 500, {.minSpeed=5, .earlyExitRange=3}, false);
    left_mg.move(80);
    right_mg.move(80);
    pros::delay(1200);

    // chassis.turnToHeading(90, 1000, {}, false);
    // chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, EAST),positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, NORTH),chassis.getPose().theta);

    // matchload.set_value(false);

    // chassis.turnToHeading(180, 1000, {}, false);
    // chassis.moveToPose(60, 16, 170, 2000, {.horizontalDrift=15, .minSpeed=100}, false);

    // triple_state = TICKLER;
    // left_mg.move(70);
    // right_mg.move(70);
    // pros::delay(1800);


    left_mg.move(0);
    right_mg.move(0);

}
#include "drive.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/rtos.hpp"
#include "robot.hpp"
#include "utils.hpp"

void skills(){
    bool scoredSeven = false;

     chassis.setPose(positionFromRaycast(back_dist.get() * MM_TO_IN, BACK_DIST_OFFSET, WEST), positionFromRaycast(left_dist.get() * MM_TO_IN, LEFT_DIST_OFFSET, NORTH),0);
    descore.set_value(true);
    matchload.set_value(false);
    triple_state = 3;
    intake.move(127);

    // pick up trio
    left_mg.move(70);
    right_mg.move(70);
    pros::delay(1800);
    // 67 derr
    chassis.turnToHeading(90, 1000, {}, false);
    chassis.setPose(positionFromRaycast(back_dist.get() * MM_TO_IN, BACK_DIST_OFFSET, WEST), positionFromRaycast(left_dist.get() * MM_TO_IN, LEFT_DIST_OFFSET, NORTH),chassis.getPose().theta);
    // intake.move(0);
    chassis.moveToPose(-24, 30, 90, 2500, {.forwards=true, .maxSpeed=100}, false);
    // chassis.turnToHeading(90, 1000, {}, false);
    chassis.setPose(positionFromRaycast(back_dist.get() * MM_TO_IN, BACK_DIST_OFFSET, WEST), positionFromRaycast(left_dist.get() * MM_TO_IN, LEFT_DIST_OFFSET, NORTH),chassis.getPose().theta);
    // chassis.turnToHeading(135, 1000, {}, false);
    // chassis.moveToPoint(-25, 25, 1000, {.forwards=true, .maxSpeed=50}, false);
    // chassis.moveToPoint(-25, 25, 1000, {.forwards=true, .maxSpeed=50});
    // left_mg.move(70);
    // right_mg.move(70);
    // pros::delay(210);
    // intake.move(127);
    // pros::delay(110);
    // left_mg.move(0);
    // // right_mg.move(0);
    // left_mg.move(-50);
    // right_mg.move(-50);
    // pros::delay(200);
    chassis.turnToHeading(315, 1300, {.direction=lemlib::AngularDirection::CW_CLOCKWISE, .maxSpeed=80, .minSpeed=5, .earlyExitRange=1});
    chassis.moveToPose(-8, 7, 320, 2000, {.forwards=false, .maxSpeed=80},false);
    // left_mg.move(-80);
    // right_mg.move(-80);
    
    // pros::delay(200);

    // left_mg.move(0);
    // right_mg.move(0);

    triple_state = 1;
    pros::delay(900);
    intake.move(57);
    // descore.set_value(false);
    pros::delay(300);
    intake.move(50);
 
    pros::delay(1400);

    intake.move(57);
    pros::delay(1500);
    triple_state = TICKLER;
    intake.move(127);
    // chassis.moveToPoint(-37, 36, 2000, {.forwards=true, .maxSpeed=80});
    // chassis.turnToPoint(-26, 26, 500);
    // chassis.moveToPoint(-26, 26, 2000, {.minSpeed=50}, true);
    // chassis.waitUntil(24);
    // intake.move(127);
    // pros::delay(700);
    // intake.move(0);

    // chassis.turnToHeading(315, 1000);
    // chassis.turnToHeading(320, 1000, {}, false);
    // intake.move(76);
    // left_mg.move(-50);
    // right_mg.move(-50);
    // pros::delay(300);
    // intake.move(127);
    // upper.move(127);
    // pros::delay(300);
    // intake.move(100);
    // upper.move(100);
    // pros::delay(200);
    // intake.move(76);
    // upper.move(76);
    // pros::delay(500);

    chassis.turnToPoint(-46, 46, 500, {.minSpeed=5, .earlyExitRange=1});
    matchload.set_value(true);
    chassis.moveToPoint(-46, 46, 1800, {.forwards=true, .maxSpeed=100});
    triple_state = MIDDLESCORE;
    chassis.waitUntil(12);
    descore.set_value(true);
    matchload.set_value(true);
    chassis.turnToHeading(270, 1000, {}, false);
    triple_state = TICKLER;
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, WEST), positionFromRaycast(right_dist.get()*MM_TO_IN, RIGHT_DIST_OFFSET, NORTH), chassis.getPose().theta);

    chassis.moveToPoint(-64, 48, 2000, {.forwards=true, .maxSpeed=55, .minSpeed=55});
    pros::delay(2000);
    left_mg.move(-50);
    right_mg.move(-50);
    pros::delay(100);
    left_mg.move(45);
    right_mg.move(45);
    pros::delay(1000);
    matchload.set_value(false);

    // descore.set_value(false);

    chassis.moveToPose(-24, 63, 260, 2000, {.forwards=false, .horizontalDrift=15, .minSpeed=50});
    chassis.moveToPoint(24, 63, 2000, {.forwards=false, .maxSpeed=127, .minSpeed=30, .earlyExitRange=3});
    
    chassis.moveToPoint(36, 49, 1500, {.forwards=false, .maxSpeed=80, .minSpeed=5, .earlyExitRange=1});
    chassis.turnToHeading(90, 1000, {}, false);
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, EAST), positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, NORTH), chassis.getPose().theta);

    chassis.moveToPoint(25, 49, 3000, {.forwards=false, .maxSpeed=80}, false);
    triple_state = 2;
    intake.move(127);
    matchload.set_value(true);
    pros::delay(2000);
    triple_state = 3;
    chassis.turnToHeading(90, 1000, {}, false);
    chassis.moveToPoint(48, 48, 1000, {.minSpeed=45, .earlyExitRange=5});
    chassis.turnToHeading(90, 1000, {}, false);
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, EAST), positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, NORTH), chassis.getPose().theta);

    chassis.moveToPoint(64, 48, 2000, {.forwards=true, .maxSpeed=55, .minSpeed=55});
    pros::delay(2000);
    left_mg.move(-50);
    right_mg.move(-50);
    pros::delay(100);
    left_mg.move(45);
    right_mg.move(45);
    pros::delay(2000);

    chassis.turnToHeading(90, 1000, {}, false);

    chassis.moveToPoint(25, 49, 3000, {.forwards=false, .maxSpeed=80}, false);
    triple_state = 2;
    intake.move(127);
    pros::delay(2000);
    triple_state = 3;

    chassis.turnToHeading(90, 1000, {}, false);
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, EAST),positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, NORTH),chassis.getPose().theta);

    matchload.set_value(false);

    chassis.turnToHeading(120, 1000, {}, false);
    chassis.moveToPose(60, 16, 170, 2000, {.horizontalDrift=15, .minSpeed=100}, false);
    // chassis.turnToHeading(135, 500,{},false);

    left_mg.move(60);
    right_mg.move(60);
    pros::delay(2500);

    // derrrrrrrr
    // chassis.turnToHeading(270, 1000, {}, false);
    
    // chassis.setPose(positionFromRaycast(back_dist.get()*MM_TO_IN, BACK_DIST_OFFSET, EAST), positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, SOUTH), chassis.getPose().theta);
    // chassis.moveToPoint(24, -24, 2000, {.forwards=true, .maxSpeed=80});
    // chassis.turnToPoint(11, -11, 1000, {.forwards=false, .maxSpeed=80}, false);
    // chassis.moveToPoint(11, -11, 2000, {.forwards=false, .maxSpeed=80}, false);
    // pros::delay(2000);
    // triple_state = 1;
    // pros::delay(2000);
    // matchload.set_value(true);
    // chassis.moveToPoint(48, -48, 1800, {.forwards=true, .maxSpeed=80});
    // chassis.turnToHeading(90, 1000,{}, false);
    // chassis.moveToPoint(60, -48.75, 1000, {.maxSpeed=45, .minSpeed=45, .earlyExitRange=5});
    // chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, EAST), positionFromRaycast(right_dist.get()*MM_TO_IN, RIGHT_DIST_OFFSET, SOUTH), chassis.getPose().theta);
    // pros::delay(800);
    
    // chassis.moveToPoint(25, -48, 2500, {.forwards=false, .maxSpeed=80});
    // // chassis.moveToPoint(42, -48, 2000, {.forwards=false}, true);
    // // chassis.turnToHeading(90, 500, {}, false);
    // // chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, EAST), positionFromRaycast(right_dist.get()*MM_TO_IN, RIGHT_DIST_OFFSET, SOUTH), chassis.getPose().theta);
    // // chassis.swingToHeading(90, lemlib::DriveSide::RIGHT, 500);
    // pros::delay(1000);
    // intake.move(127);
    // upper.move(127);
    // pros::delay(1500);


    chassis.moveToPoint(64, -48, 2000, {.forwards=true, .maxSpeed=55, .minSpeed=55});
    pros::delay(2000);
    left_mg.move(-50);
    right_mg.move(-50);
    pros::delay(100);
    left_mg.move(45);
    right_mg.move(45);
    pros::delay(2000);

    chassis.moveToPoint(56, -48, 1000, {.forwards=false, .minSpeed=50, .earlyExitRange=5});
    chassis.turnToHeading(190, 1000, {.minSpeed=50, .earlyExitRange=5});
   

    chassis.moveToPose(24, -68,270, 1000, {.forwards=true, .horizontalDrift=15, .maxSpeed=127, .minSpeed=50});
    matchload.set_value(false);
    // chassis.turnToHeading(270, 200);
    chassis.moveToPoint(-24, -72, 3000, {.forwards=true, .minSpeed=20, .earlyExitRange=5});

    // chassis.turnToHeading(135, 500);

    // chassis.moveToPoint(10, -10, 2500, {.forwards=false, .maxSpeed=70}, false);
    // intake.move(0);
    // upper.move(64);
    // matchload.set_value(false);
    // pros::delay(800);
    // intake.move(0);
    // upper.move(0);

    // chassis.moveToPoint(24, -24, 3000, {.forwards=true});
    // chassis.turnToHeading(270, 1000);
    chassis.moveToPoint(-42, -55, 2000, {.forwards=true, .minSpeed=5, .earlyExitRange=1});
    matchload.set_value(true);

    // chassis.turnToHeading(270,500);

    // pros::Task discard_blue ([&] {
    //     int timeout = 0;
    //     bool redDetected = false;
    //     while (timeout <= 50 && redDetected == false) {
    //         upper.move(100);
    //         intake.move(100);

    //         if(fabs(roller_optical.get_hue() - 15) < 15){
    //             redDetected = true;
    //         }
    //         timeout++;
    //         pros::delay(20);
    //     }
    //     intake.move(0);
    //     upper.move(0);
    // });

    // pros::delay(1000);
    
    // intake.move(127);

    chassis.turnToHeading(270, 1000, {}, false);
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, WEST), positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, SOUTH), chassis.getPose().theta);

    // pros::Task align_score5{[=]{
    //     while(back_dist.get() > 90) { pros::delay(50);}
    //     intake.move(127);
    //     upper.move(127);
    // }}; 
    
    // chassis.moveToPoint(-25, -48, 1500, {.forwards=false, .maxSpeed=60});
    // matchload.set_value(true);
    // pros::delay(1500);

    // chassis.turnToHeading(270, 500, {}, false);
    // chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, WEST), positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, SOUTH), chassis.getPose().theta);

    chassis.turnToPoint(-25, -48.75, 500, {.forwards=false});
    chassis.moveToPoint(-25, -48.75, 3000, {.forwards=false, .maxSpeed=60});
    pros::delay(1000);
    pros::delay(2000);
    
    chassis.turnToHeading(270, 500, {}, false);
    chassis.setPose(positionFromRaycast(front_dist.get()*MM_TO_IN, FRONT_DIST_OFFSET, WEST), positionFromRaycast(left_dist.get()*MM_TO_IN, LEFT_DIST_OFFSET, SOUTH), chassis.getPose().theta);
    chassis.moveToPoint(-62, -48.75, 3000, {.forwards=true, .maxSpeed=60});
    pros::delay(1500);
    left_mg.move(-50);
    right_mg.move(-50);
    pros::delay(100);
    left_mg.move(45);
    right_mg.move(45);
    pros::delay(500);
    matchload.set_value(false);

    chassis.turnToPoint(-25, -48.75, 500, {.forwards=false});
    chassis.moveToPoint(-25, -48.75, 3000, {.forwards=false, .maxSpeed=60});
    pros::delay(1000);
    pros::delay(2000);
    // chassis.moveToPoint(-48, -48, 2000, {.forwards=true, .minSpeed=5, .earlyExitRange=1});
    // matchload.set_value(false);

    chassis.moveToPose(-60, -24, 350, 1000, {.horizontalDrift=15, .minSpeed=100}, false);
    chassis.moveToPose(-60, -24, 350, 2000, {.horizontalDrift=15, .maxSpeed=50}, false);
    // chassis.turnToHeading(135, 500,{},false);
    left_mg.move(80);
    right_mg.move(80);
    pros::delay(1250);

    // chassis.moveToPoint(-42, 0, 3000, {.maxSpeed=127, .minSpeed=5, .earlyExitRange=1}, false);
    // chassis.turnToHeading(270, 1000, {}, false);

    // left_mg.move(70);
    // right_mg.move(70);
    // pros::delay(2000);

    left_mg.move(0);
    right_mg.move(0);

}
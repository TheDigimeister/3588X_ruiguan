#include "main.h"
#include "autons.hpp"
#include "lemlib/api.hpp"
#include "liblvgl/llemu.hpp"


bool descore_pressed = false;
bool matchload_pressed = false;
bool intake_speed_pressed = false;

bool descore_state = false;
bool matchload_state = false;
bool intake_speed_state = false;

bool prev_descore_state = false;
bool prev_matchload_state = false;
bool prev_intake_speed_state = false;

int intake_speed = 127;

int selected_auton = 6;
bool auton_selected = false;

const float RAYCAST_RESET_ANGLE_RANGE = 20.0; // ± degrees from 0°/360° or 90°/270° 
const float RAYCAST_RESET_MIN_ERROR = 0.0; // minimum error required before applying correction
const float RAYCAST_RESET_MAX_ERROR = 3.0; // maximum error to restrict correction (e.g. matchloader depth)

const int ALLIANCECOLOR = RED;

const char* auton_names[] = {
    "None",
    "Left 9 Ball",
    "Left 7 Ball", 
    "Left Middle Goal",
    "Right 9 Ball",
    "Right 7 Ball",
    "Skills",
	"PID Tune",
};

int triple_state = 3;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
    auton_selected = true;
}

void on_left_button() {
    if (!auton_selected) {
        selected_auton--;
        if (selected_auton < 1) selected_auton = 7; // Wrap to last auton
    }
}

void on_right_button() {
    if (!auton_selected) {
        selected_auton++;
        if (selected_auton > 7) selected_auton = 1; // Wrap to first auton
    }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::register_btn0_cb(on_left_button);   // Left button
    pros::lcd::register_btn1_cb(on_center_button); // Center button  
    pros::lcd::register_btn2_cb(on_right_button);  // Right button

	chassis.calibrate();

    // chassis.setPose(positionFromRaycast(back_dist.get() * MM_TO_IN, BACK_DIST_OFFSET, WEST), positionFromRaycast(right_dist.get() * MM_TO_IN, RIGHT_DIST_OFFSET, SOUTH),90);
	chassis.setPose(0,0,90);

	left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

	pros::Task triple_state_task([&] {
		while(true){
			switch(triple_state){
			case 1:
				level_1.set_value(true);
				level_2.set_value(false);
				break;
			case 2:
				level_1.set_value(false);
				level_2.set_value(true);
				break;
			case 3:
				level_1.set_value(false);
				level_2.set_value(false);
				break;
			}
			pros::delay(50);
		}
	});

	pros::Task screen_task([&] {
		while (!auton_selected) {
		// pros::lcd::clear();
		pros::lcd::print(0, "Auton Selector");
		pros::lcd::print(1, "< %s >", auton_names[selected_auton]);
		pros::lcd::print(2, "Press center to select");
		pros::lcd::print(3, "Selected: %d", selected_auton);
		pros::delay(100);
	}
        
		// Display selected auton
		pros::lcd::print(0, "Auton Selected!");
		pros::lcd::print(1, "%s", auton_names[selected_auton]);
		pros::lcd::print(2, "ID: %i", selected_auton);
		pros::lcd::clear_line(3);
	});
	

	// vision.start_awb();
	// vision.enable_detection_types(pros::AivisionModeType::objects);

	// vision.set_color({1,109,157,195,40,0.23});
	// vision.set_color({2,175,36,73,40,0.25});

	// pros::Task ai_vision([&] {
	// 	while(true){
	// 		int num_objects = vision.get_object_count();
	// 		std::printf("Number of objects: %3i\n", num_objects);

	// 		auto objects = vision.get_all_objects();
	// 		for (const auto& object: objects) {
	// 			std::printf("Object id is: %1i, object type is: %1i\n", object.id, object.type);
	// 		}

	// 		pros::delay(1000);
	// 	}
	// });

	pros::Task distance_resets([&] {

		while(true) {

			float frontReading = front_dist.get() * MM_TO_IN;
			float leftReading = left_dist.get() * MM_TO_IN;
			float rightReading = right_dist.get() * MM_TO_IN;
			float backReading = back_dist.get() * MM_TO_IN;

			float frontConfidence = front_dist.get_confidence();
			float leftConfidence = left_dist.get_confidence();
			float rightConfidence = right_dist.get_confidence();
			float backConfidence = back_dist.get_confidence();

			lemlib::Pose currentPose = chassis.getPose();
					
			float estimated_x = currentPose.x;
			float estimated_y = currentPose.y;

			float x_deviation = 144;
			float y_deviation = 144;

			float normalizedTheta = normalizeAngle(currentPose.theta);
			// std::printf("Normalized Theta: %.3f", normalizedTheta);

			float estimatedRightPos = 0;
			float estimatedFrontPos = 0;
			float estimatedLeftPos = 0;
			float estimatedBackPos = 0;

			WALL wallDirection = NORTH;
			bool parallel = false;

			float error_x = 144.0;
			float error_y = 144.0;

			if (fabs(normalizedTheta) < RAYCAST_RESET_ANGLE_RANGE/2.0) {
				parallel = true;
				wallDirection = NORTH;
			}
			else if (fabs(normalizedTheta - 180) < RAYCAST_RESET_ANGLE_RANGE/2.0) {
				parallel = true;
				wallDirection = SOUTH;
			}
			else if (fabs(normalizedTheta - 90) < RAYCAST_RESET_ANGLE_RANGE/2.0) {
				parallel = true;
				wallDirection = EAST;
			}
			else if (fabs(normalizedTheta - 270) < RAYCAST_RESET_ANGLE_RANGE/2.0) {
				parallel = true;
				wallDirection = WEST;
			}
			else {
				parallel = false;
			}
			
			if (parallel) {
				switch (wallDirection) {
					case NORTH:
						estimatedRightPos = positionFromRaycast(rightReading, RIGHT_DIST_OFFSET, EAST);
						estimatedFrontPos = positionFromRaycast(frontReading, FRONT_DIST_OFFSET, NORTH);
						estimatedLeftPos = positionFromRaycast(leftReading, LEFT_DIST_OFFSET, WEST);
						estimatedBackPos = positionFromRaycast(backReading, BACK_DIST_OFFSET, SOUTH);
						x_deviation = fabs(estimatedLeftPos - estimatedRightPos);
						y_deviation = fabs(estimatedFrontPos - estimatedBackPos);
						estimated_x = (leftConfidence * estimatedLeftPos + rightConfidence * estimatedRightPos) / (leftConfidence + rightConfidence);
						estimated_y = (frontConfidence * estimatedFrontPos + backConfidence * estimatedBackPos) / (frontConfidence + backConfidence);
						break;
					case SOUTH:
						estimatedRightPos = positionFromRaycast(rightReading, RIGHT_DIST_OFFSET, WEST);
						estimatedFrontPos = positionFromRaycast(frontReading, FRONT_DIST_OFFSET, SOUTH);
						estimatedLeftPos = positionFromRaycast(leftReading, LEFT_DIST_OFFSET, EAST);
						estimatedBackPos = positionFromRaycast(backReading, BACK_DIST_OFFSET, NORTH);
						x_deviation = fabs(estimatedLeftPos - estimatedRightPos);
						y_deviation = fabs(estimatedFrontPos - estimatedBackPos);
						estimated_x = (leftConfidence * estimatedLeftPos + rightConfidence * estimatedRightPos) / (leftConfidence + rightConfidence);
						estimated_y = (frontConfidence * estimatedFrontPos + backConfidence * estimatedBackPos) / (frontConfidence + backConfidence);
						break;
					case EAST:
						estimatedRightPos = positionFromRaycast(rightReading, RIGHT_DIST_OFFSET, SOUTH);
						estimatedFrontPos = positionFromRaycast(frontReading, FRONT_DIST_OFFSET, EAST);
						estimatedLeftPos = positionFromRaycast(leftReading, LEFT_DIST_OFFSET, NORTH);
						estimatedBackPos = positionFromRaycast(backReading, BACK_DIST_OFFSET, WEST);
						x_deviation = fabs(estimatedFrontPos - estimatedBackPos);
						y_deviation = fabs(estimatedLeftPos - estimatedRightPos);
						estimated_y = (leftConfidence * estimatedLeftPos + rightConfidence * estimatedRightPos) / (leftConfidence + rightConfidence);
						estimated_x = (frontConfidence * estimatedFrontPos + backConfidence * estimatedBackPos) / (frontConfidence + backConfidence);
						break;
					case WEST:
						estimatedRightPos = positionFromRaycast(rightReading, RIGHT_DIST_OFFSET, NORTH);
						estimatedFrontPos = positionFromRaycast(frontReading, FRONT_DIST_OFFSET, WEST);
						estimatedLeftPos = positionFromRaycast(leftReading, LEFT_DIST_OFFSET, SOUTH);
						estimatedBackPos = positionFromRaycast(backReading, BACK_DIST_OFFSET, EAST);
						x_deviation = fabs(estimatedFrontPos - estimatedBackPos);
						y_deviation = fabs(estimatedLeftPos - estimatedRightPos);
						estimated_y = (leftConfidence * estimatedLeftPos + rightConfidence * estimatedRightPos) / (leftConfidence + rightConfidence);
						estimated_x = (frontConfidence * estimatedFrontPos + backConfidence * estimatedBackPos) / (frontConfidence + backConfidence);
						break;
					default:
						std::printf("Invalid wall direction");
						break;
				}

				error_x = fabs(estimated_x - currentPose.x);
				error_y = fabs(estimated_y - currentPose.y);
				// std::printf("X_deviation: %.3f\nY_deviation: %.3f\n", x_deviation, y_deviation);

				// std::printf("X Error: %.3f, Y Error: %.3f\n", error_x, error_y);

				if (x_deviation >= RAYCAST_RESET_MIN_ERROR && x_deviation <= RAYCAST_RESET_MAX_ERROR && error_x > 0.3){
					chassis.setPose(estimated_x, chassis.getPose().y, chassis.getPose().theta);
					std::printf("X pos reset! %.3f Deviation: %.3f\n",estimated_x, x_deviation);
				}

				if (y_deviation >= RAYCAST_RESET_MIN_ERROR && y_deviation <= RAYCAST_RESET_MAX_ERROR && error_y > 0.3){
					chassis.setPose(chassis.getPose().x, estimated_y, chassis.getPose().theta);
					std::printf("Y pos reset! %.3f Deviation: %.3f\n", estimated_y, y_deviation);
				}
			}

		pros::delay(50);
	}
	});

	pros::Task print_coordinates([=](){
		while (true) {
			// std::cout << "Estimated pose: x=" << chassis.getPose().x << ", y=" << chassis.getPose().y << ", theta=" << chassis.getPose().theta;
			if (true) {
				// std::cout << std::endl;
				// std::printf("Estimated pose: x=%.3f, y=%.3f, theta=%.3f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
				// pros::lcd::print(0, "X:%.2f, Y:%.2f, Theta:%.2f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
				master.print(0, 0, "X:%.2fY:%.2fT:%.2f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
				// master.print(0,0,"Dist Theta: %.3f", calculateHeading(chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta, -5.289,5.503,-5.63,-2.028,front_dist.get() * MM_TO_IN,left_dist.get() * MM_TO_IN, NORTH, WEST));
				pros::delay(100);
			}
		}
	});
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {

	switch (selected_auton) {

		case 2:
			left7ball();
			break;
		case 3:
			leftMiddleGoal();
			break;
		case 5:
			right7ball();
			break;
		case 6:
			skills();
			break;
		case 7:
			pidTune();
			break;
	}

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

 #pragma region opcontrol
void opcontrol() {

	left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);


	while (true) {

		descore_pressed = master.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
		matchload_pressed = master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
		intake_speed_pressed = master.get_digital(pros::E_CONTROLLER_DIGITAL_A);

		
		// Arcade control scheme
		int dir = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
		int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
		
		if (abs(dir) + abs(turn) > 5) {
			left_mg.move(dir + turn);                      // Sets left motor voltage
			right_mg.move(dir - turn);                     // Sets right motor voltage
		}
		else {
			left_mg.brake();
			right_mg.brake();
		}

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			intake.move(127);
			triple_state = 3;
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			intake.move(57);
			triple_state = 1;
		}

		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			intake.move(intake_speed);
			triple_state = 2;
		}
		
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			intake.move(-127);
		}

		else {
			intake.move(0);
		}

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
			descore.set_value(false);
			descore_state = false;
			prev_descore_state = true;
			float current_heading = normalizeAngle(chassis.getPose().theta);
			float error90 = fabs(current_heading - 90);
			float error270 = fabs(current_heading - 270);
			if (error270 < error90) {
    			chassis.turnToHeading(270, 500, {}, false);
				left_mg.move(50);
				right_mg.move(50);
				pros::delay(150);
				chassis.turnToHeading(340, 500, {.minSpeed=5, .earlyExitRange=1}, false);
				left_mg.move(-50);
				right_mg.move(-50);
				pros::delay(300);
				chassis.turnToHeading(270, 500, {.maxSpeed=80, .minSpeed=5, .earlyExitRange=1}, false);
				// left_mg.move(-100);
				// right_mg.move(-100);
				// pros::delay(450);
				// chassis.turnToHeading(270, 500, {}, false);
			} else {
				chassis.turnToHeading(90, 500, {}, false);
				left_mg.move(50);
				right_mg.move(50);
				pros::delay(150);
				chassis.turnToHeading(160, 500, {.minSpeed=5, .earlyExitRange=1}, false);
				left_mg.move(-50);
				right_mg.move(-50);
				pros::delay(300);
				chassis.turnToHeading(90, 500, {.maxSpeed=80, .minSpeed=5, .earlyExitRange=1}, false);
				// left_mg.move(-100);
				// right_mg.move(-100);
				// pros::delay(450);
				// chassis.turnToHeading(90, 500, {}, false);
			} }

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
			descore.set_value(false);
			descore_state = false;
			prev_descore_state = true;
			float current_heading = normalizeAngle(chassis.getPose().theta);
			float error90 = fabs(current_heading - 90);
			float error270 = fabs(current_heading - 270);
			if (error270 < error90) {
				chassis.turnToHeading(270, 500, {}, false);
				left_mg.move(50);
				right_mg.move(50);
				pros::delay(150);
    			chassis.turnToHeading(350, 500, {}, false);
				left_mg.move(50);
				right_mg.move(50);
				pros::delay(300);
				// chassis.turnToHeading(340, 500, {.minSpeed=5, .earlyExitRange=1}, false);
				// left_mg.move(50);
				// right_mg.move(50);
				// pros::delay(300);
				chassis.turnToHeading(90, 500, {.direction=lemlib::AngularDirection::CW_CLOCKWISE, .maxSpeed=80}, false);
				// left_mg.move(-100);
				// right_mg.move(-100);
				// pros::delay(450);
				// chassis.turnToHeading(270, 500, {}, false);
			} else {
				chassis.turnToHeading(90, 500, {}, false);
				left_mg.move(50);
				right_mg.move(50);
				pros::delay(150);
				chassis.turnToHeading(170, 500, {}, false);
				left_mg.move(50);
				right_mg.move(50);
				pros::delay(300);
				chassis.turnToHeading(270, 500, {.direction=lemlib::AngularDirection::CW_CLOCKWISE, .maxSpeed=80}, false);
				// left_mg.move(-100);
				// right_mg.move(-100);
				// pros::delay(450);
				// chassis.turnToHeading(90, 500, {}, false);
			}
		}
		


		// Pneumatics

		if (matchload_pressed && !prev_matchload_state) {
			matchload_state = !matchload_state;
			matchload.set_value(matchload_state);
		}

		if (descore_pressed && !prev_descore_state) {
			descore_state = !descore_state;
			descore.set_value(descore_state);
		}

		if (intake_speed_pressed && !prev_intake_speed_state) {
			intake_speed_state = !intake_speed_state;
			if(intake_speed_state) {intake_speed = 80;}
			else {intake_speed = 127;}
		}

		prev_matchload_state = matchload_pressed;
		prev_descore_state = descore_pressed;
		prev_intake_speed_state = intake_speed_pressed;
		
		pros::delay(20);                               // Run for 20 ms then update
	}
}
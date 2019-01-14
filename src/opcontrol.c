/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl() {
	int intakeState;
	int catState;
	int descoreState;
	int driveState;
	while (1) {

		driveState = DRIVE_W_JOY;

		updateDriveWjoy((joystickGetAnalog(1, 2) + joystickGetAnalog(1, 1)), (joystickGetAnalog(1, 2) - joystickGetAnalog(1, 2)), STD_SLEW);

		if(joystickGetDigital(1, 5, JOY_UP)){
			intakeState = INTAKE_INTAKE;
			if(joystickGetDigital(1, 5, JOY_DOWN)){
				intakeState = INTAKE_ONE;
			}
		} else if(joystickGetDigital(1, 5, JOY_DOWN)){
			intakeState = INTAKE_OUTTAKE;
		} else {
			intakeState = INTAKE_STOP;
		}

		if(joystickGetDigital(1, 6, JOY_UP)){
			if(joystickGetDigital(1, 6, JOY_DOWN)){ // if les deux
				catState = CAT_MOVE_BALL;
			} else {
				catState = CAT_FIRE;
			}
		} else if(joystickGetDigital(1, 6, JOY_DOWN)){
			catState = CAT_STOP;
		} else {
			catState = CAT_RELOAD;
		}

		if(joystickGetDigital(1, 7, JOY_UP)){
			descoreState = DESCORE_BACK;
		} else if(joystickGetDigital(1, 7, JOY_DOWN)){
			descoreState = DESCORE_GROUND;
		} else if(joystickGetDigital(1, 7, JOY_LEFT)){
			descoreState = DESCORE_UP_FRONT;
		} else{
			descoreState = DESCORE_JOY_CTRL;
		}

		descoreCtrl(descoreState, joystickGetAnalog(1, 3));
		intakeCtrl(intakeState);
		catCtrl(catState);
		driveCtrl(driveState);
	}
}

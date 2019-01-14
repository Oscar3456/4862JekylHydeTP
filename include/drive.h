#ifndef _DRIVE_H_
#define _DRIVE_H_

#define DRIVE_W_JOY 0
#define TURN_TO_ANGLE 1
#define DRIVE_TO_DISTANCE 2

extern float angleGoal;
extern float distGoal;

#define STD_SLEW 5

float getDriveAngle(float leftStart, float rightStart);

void startMovement();

void updateTurnToAngle(float angleGoal);

void doTurnToAngle(float angleGoal, float kp, float kd, int slew, int maxPow);

void updateDriveStraight(float distGoal, float kp, float kd, int slew, int maxPow);

void doDriveStraight(float distGoal);

void updateDriveWjoy(int leftJoy, int rightJoy, int slew);

void initDriveEnc();

float getLeftInches();

float getRightInches();

float getPerpInches();

void setDriveMtr(int leftPower, int rightPower);

void driveSlew(int leftGoal, int rightGoal, int slew);

void driveCtrl(int state);

#endif // _DRIVE_H_

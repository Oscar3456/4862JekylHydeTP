#include "main.h"
#include "drive.h"
// d_ = drive
#define LEFT_TO_INCHES 0.04799655442984406336540149613344
#define RIGHT_TO_INCHES 0.04799655442984406336540149613344
#define PERP_TO_INCHES 0.04799655442984406336540149613344
#define INCHES_TO_RAD 12

#define FRIKING_ANGLE_CONST 1

int driveState;

Encoder leftTrack;
Encoder rightTrack;
Encoder perpTrack;

float d_angleGoal;
float d_distGoal;
float d_angleKp;
float d_angleKd;
float d_distKp;
float d_distKd;
int d_slew;
int d_maxPow;
float d_angleError;
float d_angleLastError;
float d_distError;
float d_distLastError;

float d_leftStart;
float d_rightStart;
float d_startAngle;

float d_angleRange;
float d_distRange;

int d_leftJoy;
int d_rightJoy;

float getDriveAngle(){
  return (getLeftInches() - getRightInches()) * FRIKING_ANGLE_CONST;
}

float degreesToRad(int degrees){
  return degrees * 0.01745329;
}

void startMovement(){
  d_leftStart = getLeftInches();
  d_rightStart = getRightInches();
  d_startAngle = getDriveAngle();
  d_angleError = 0;
  d_angleLastError = 0;
  d_distError = 0;
  d_distLastError = 0;
}

void updateTurnToAngle(float angleGoal, float kp, float kd, int slew, int maxPow, float angleRange){
  d_angleGoal = angleGoal;
  d_angleKp = kp;
  d_angleKd = kd;
  d_slew = slew;
  d_maxPow = maxPow;
  d_angleRange = angleRange;
  driveState = TURN_TO_ANGLE;
}

void doTurnToAngle(float angleGoal){
  d_angleError = d_angleGoal - getDriveAngle();
  float derivative = d_angleError - d_angleLastError;
  d_angleLastError = d_angleError;
  int power = (d_angleError * d_angleKp) + (derivative * d_angleKd);

  if (power > d_maxPow){
    power = d_maxPow;
  } else if(power < d_maxPow * -1){
    power =  d_maxPow * -1;
  }

  driveSlew(power, power * -1, d_slew);
}

void updateDriveStraight(float distGoal, float angleKp, float angleKd, float distKp, float distKd, int slew, int maxPow, float distRange){
  d_distGoal = distGoal;
  d_angleKp = angleKp;
  d_angleKd = angleKd;
  d_distKp = distKp;
  d_distKd = distKd;
  d_slew = slew;
  d_maxPow = maxPow;
  d_distRange = distRange;
  driveState = DRIVE_TO_DISTANCE;
}

void doDriveStraight(float distGoal){
  int distancePower;
  int leftPower;
  int rightPower;
  float distDerivative;
  float angleDerivative;

  int distance = (getRightInches() + getLeftInches())/2;
  d_distError = distGoal - distance;
  distDerivative = d_distError - d_distLastError;
  d_distLastError = d_distError;
  distancePower = (d_distError * d_distKp) + (distDerivative * d_distKd);

  if (distancePower > d_maxPow){
    distancePower = d_maxPow;
  } else if(distancePower < d_maxPow * -1){
    distancePower =  d_maxPow * -1;
  }
  leftPower = distancePower;
  rightPower = distancePower;

  d_angleError = d_startAngle - getDriveAngle();
  if(d_angleError != 0){
    angleDerivative = d_angleError - d_angleLastError;
    d_angleLastError = d_angleError;
    int anglePower = (d_angleError * d_angleKp) + (angleDerivative * d_angleKd);
    if(distancePower > 0){
      if(d_angleError < 0){
        leftPower += anglePower;
      } else if (d_angleError > 0){
        rightPower -= anglePower;
      }
    } else {
      if(d_angleError < 0){
        leftPower -= anglePower;
      } else if (d_angleError > 0){
        rightPower += anglePower;
      }
    }
  }
  driveSlew(leftPower, rightPower, d_slew);
}


void updateDriveWjoy(int leftJoy, int rightJoy, int slew){
  d_leftJoy = leftJoy;
  d_rightJoy = rightJoy;
  d_slew = slew;
  d_maxPow = 127;
  driveState = DRIVE_W_JOY;
}

void initDriveEnc(){
  leftTrack = encoderInit(LEFT_ENC_TOP, LEFT_ENC_BOT, false);
  rightTrack = encoderInit(RIGHT_ENC_TOP, RIGHT_ENC_BOT, false);
  perpTrack = encoderInit(PERP_ENC_TOP, PERP_ENC_BOT, false);
}

float getLeftInches(){
  return encoderGet(leftTrack) * LEFT_TO_INCHES;
}

float getRightInches(){
  return encoderGet(rightTrack) * RIGHT_TO_INCHES;
}

float getPerpInches(){
  return encoderGet(perpTrack) * PERP_TO_INCHES;
}

void setDriveMtr(int leftPower, int rightPower){
  motorSet(DRIVE_LEFT_A_MTR, leftPower);
  motorSet(DRIVE_LEFT_B_MTR, leftPower);

  motorSet(DRIVE_RIGHT_A_MTR, rightPower);
  motorSet(DRIVE_RIGHT_B_MTR, rightPower);
}

void driveSlew(int leftGoal, int rightGoal, int slew){
  int leftDrive = motorGet(DRIVE_LEFT_A_MTR);
  int rightDrive = motorGet(DRIVE_RIGHT_A_MTR);

  if(leftDrive + slew < leftGoal){ // left slew
    leftDrive += slew;
  } else if(leftDrive - slew > leftGoal){
    leftDrive -= slew;
  } else{
    leftDrive = leftGoal;
  }

  if(rightDrive + slew < rightGoal){ // right slew
    rightDrive += slew;
  } else if(rightDrive - slew > rightGoal){
    rightDrive -= slew;
  } else{
    rightDrive = rightGoal;
  }

  setDriveMtr(leftDrive, rightDrive);
}

void driveCtrl(int state){
  switch(state){
    case DRIVE_W_JOY:
      driveSlew(d_leftJoy, d_rightJoy, d_slew);
      break;
    case TURN_TO_ANGLE:
      doTurnToAngle(d_angleGoal);
      break;
    case DRIVE_TO_DISTANCE:
      doDriveStraight(d_distGoal);
  }
}

#include "main.h"
#include "auton.h"
#include "math.h"

int catState;
int intakeState;
int descoreState;
int driveState;

void robotAutonCtrl(){
  catCtrl(catState);
  intakeCtrl(intakeState);
  descoreCtrl(descoreState, 0);
}

bool catIsDone(){
  bool isDone = false;

  switch(catState){
    case CAT_STOP:
      if(motorGet(CAT_A_MTR) == 0){
        isDone = true;
      }
      break;
    case CAT_MOVE_BALL:
      if(abs(getCatPot() - CAT_MOVE_BALL_POS) < CAT_DEADBAND){
        isDone = true;
      }
      break;
    case CAT_RELOAD:
      if(abs(getCatPot() - CAT_DOWN_POS) < CAT_DEADBAND){
        isDone = true;
      }
      break;
    case CAT_FIRE:
      if(abs(getCatPot() - CAT_FIRE_POS) < CAT_DEADBAND){
        isDone = true;
      }
      break;
  }
  return isDone;
}

bool descoreIsDone(){
  bool isDone = false;
  switch(descoreState){
    case DESCORE_BACK:
      if(abs(getDescorePot() - DESCORE_BACK_POS) < DESCORE_DEADBAND){
        isDone = true;
      }
      break;
    case DESCORE_UP_FRONT:
      if(abs(getDescorePot() - DESCORE_UP_FRONT_POS) < DESCORE_DEADBAND){
        isDone = true;
      }
      break;
    case DESCORE_GROUND:
      if(abs(getDescorePot() - DESCORE_GROUND_POS) < DESCORE_DEADBAND){
      isDone = true;
      }
      break;
  }
  return isDone;
}

bool intakeIsDone(){
  bool isDone = false;
  switch (intakeState){
    case INTAKE_ONE:
      if(ballsInCat > 0) { // if balls are in intake
        isDone = true;
      }
      break;
    case INTAKE_TWO:
      if(ballsInCat >= 2) { // 2 balls are in intake
        isDone = true;
      }
  }
  return isDone;
}

bool driveIsDone(){
  bool isDone = false;
  float error;
  switch(driveState){
    case TURN_TO_ANGLE:
      error = angleGoal - getDriveAngle();
      if(fabs(error) < d_angleRange){
        isDone = true;
      }
      break;
    case DRIVE_TO_DISTANCE:
    error = distGoal - ((getLeftInches() + getRightInches()) / 2);
      if(fabs(error) < d_distRange){
        isDone = true;
      }
  }
  return isDone;
}

void await(bool (*isDone)){
  while(!(*isDone)){
    robotAutonCtrl();
  }
}

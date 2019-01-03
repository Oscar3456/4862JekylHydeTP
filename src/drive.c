#include "main.h"
#include "drive.h"

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

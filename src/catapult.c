#include "main.h"
#include "catapult.h"

#define KP 1
#define KI 0
#define KD 0

#define INTEGRAL_RANGE 100

#define CAT_UP_POS 0
#define CAT_DOWN_POS 1000
#define CAT_FIRE_POS 1500

int catPosGoal;

int error;
int lastError;

int integral;
int derivative;

void setCatMtr(int power){
  motorSet(CAT_A_MTR, power);
  motorSet(CAT_B_MTR, power);
}

int getCatPot();

void setCatPos(int goal){
  int pos = getCatPot();
  error = goal - pos;

  if(KP != 0){
    if(abs(error ) < INTEGRAL_RANGE){
      integral += error;
    } else {
      integral = 0;
    }
  } else {
    integral = 0;
  }

  derivative = error - lastError;
  lastError = error;
  setCatMtr((error * KP) + (derivative * KD));
}

void catCtrl(int state){
  switch(state){
    case STOP_CAT:
      setCatMtr(0);
      break;
    case MOVE_BALL:
      setCatPos(CAT_UP_POS);
      break;
    case RELOAD_CAT:
      setCatPos(CAT_DOWN_POS);
      break;
    case FIRE_CAT:
      setCatPos(CAT_FIRE_POS);
      ballsInCat -= 2;
      break;
  }
} // 0(stop all), 1(move ball to inner slot), 2(reload), 3(fire)

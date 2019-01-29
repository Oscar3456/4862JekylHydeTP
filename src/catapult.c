#include "main.h"
#include "catapult.h"

#define KP 1
#define KI 0
#define KD 0

#define BOT_HOLD_POW 20
#define TOP_HOLD_POW 15

#define INTEGRAL_RANGE 100

int catState;

int catPotZero =0;

int catPosGoal;

int error;
int lastError;

int integral;
int derivative;

void setCatMtr(int power){
  motorSet(CAT_A_MTR, power);
  motorSet(CAT_B_MTR, power);
}

void zeroCatPot(){
  catPotZero = analogRead(CAT_POT);
}

int getCatPot(){
  return analogRead(CAT_POT) - catPotZero;
}

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
  setCatMtr((error * KP) + (integral * KI) + (derivative * KD));
}

void catCtrl(int state){
  switch(state){
    case CAT_STOP:
      setCatMtr(0);
      break;
    case CAT_MOVE_BALL:
      if(getCatPot() > CAT_MOVE_BALL_POS - 10){
        setCatMtr(TOP_HOLD_POW);
      } else {
        setCatMtr(0);
      }
      break;
    case CAT_RELOAD:
      if(getCatPot() < CAT_DOWN_POS){
        setCatMtr(BOT_HOLD_POW);
      } else {
        setCatMtr(-120);
      }
      break;
    case CAT_FIRE:
      setCatMtr(-120);
      ballsInCat = 0;
      break;
  }
} // 0(stop all), 1(move ball to inner slot), 2(reload), 3(fire)

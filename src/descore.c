#include "main.h"
#include "descore.h"


#define KP 1

int getDescorePot(){
  return analogRead(DESCORE_POT);
}

void setDescoreMtr(int power){
  motorSet(DESCORE_MTR, power);
}

void setDescorePos(int posGoal){
  int error;
  error = posGoal - getDescorePot();
  setDescoreMtr(error * KP);
}

void descoreCtrl(int state, int joy){
  switch(state){
    case DESCORE_JOY_CTRL:
      setDescoreMtr(joy);
      break;
    case DESCORE_BACK:
      setDescorePos(DESCORE_BACK_POS);
      break;
    case DESCORE_UP_FRONT:
      setDescorePos(DESCORE_UP_FRONT_POS);
      break;
    case DESCORE_GROUND:
      setDescorePos(DESCORE_GROUND_POS);
      break;
  }
}

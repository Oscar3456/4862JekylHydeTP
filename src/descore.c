#include "main.h"
#include "descore.h"

#define BACK_POS 1
#define UP_FRONT_POS 2
#define DOWN_FRONT_POS 3

#define KP 1

int getDescorePos();

void setDescoreMtr(int power){
  motorSet(DESCORE_MTR, power);
}

void setDescorePos(int posGoal){
  int error;
  error = posGoal - getDescorePos();
  setDescoreMtr(error * KP);
}

void descoreCtrl(int state, int joy){
  switch(state){
    case DESCORE_JOY:
      setDescoreMtr(joy);
      break;
    case DESCORE_BACK:
      setDescorePos(BACK_POS);
      break;
    case DESCORE_UP_FRONT:
      setDescorePos(UP_FRONT_POS);
      break;
    case DESCORE_DOWN_FRONT:
      setDescorePos(DOWN_FRONT_POS);
      break;
  }
}

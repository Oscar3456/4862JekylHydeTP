#ifndef _DESCORE_H_
#define _DESCORE_H_

#define DESCORE_JOY 0
#define DESCORE_BACK 1
#define DESCORE_UP_FRONT 2
#define DESCORE_DOWN_FRONT 3

int getDescorePos();

void setDescoreMtr(int power);

void setDescorePos(int posGoal);

void descoreCtrl(int state, int joy);

#endif //_DESCORE_H_

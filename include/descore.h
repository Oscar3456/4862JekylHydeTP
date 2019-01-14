#ifndef _DESCORE_H_
#define _DESCORE_H_

#define DESCORE_JOY_CTRL 0
#define DESCORE_BACK 1
#define DESCORE_UP_FRONT 2
#define DESCORE_GROUND 3

#define DESCORE_BACK_POS 1
#define DESCORE_UP_FRONT_POS 2
#define DESCORE_GROUND_POS 3

#define DESCORE_DEADBAND 20

int getDescorePot();

void setDescoreMtr(int power);

void setDescorePos(int posGoal);

void descoreCtrl(int state, int joy);

#endif //_DESCORE_H_

#ifndef _CATAPULT_H_
#define _CATAPULT_H_

#define CAT_STOP 0
#define CAT_MOVE_BALL 1
#define CAT_RELOAD 2
#define CAT_FIRE 3

#define CAT_UP_POS 0
#define CAT_DOWN_POS 1000
#define CAT_FIRE_POS 1500
#define CAT_MOVE_BALL_POS 100

#define CAT_DEADBAND 20

void zeroCatPot();

void setCatMtr(int power);

int getCatPot();

void setCatPos(int goal);

void catCtrl(int state); // 0(stop all), 1(move ball to inner slot), 2(reload), 3(fire)

#endif //_CATAPULT_H_

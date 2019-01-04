#ifndef _CATAPULT_H_
#define _CATAPULT_H_

#define STOP_CAT 0
#define MOVE_BALL 1
#define RELOAD_CAT 2
#define FIRE_CAT 3

void setCatMtr(int power);

int getCatPot();

void setCatPos(int goal);

void catCtrl(int state); // 0(stop all), 1(move ball to inner slot), 2(reload), 3(fire)

#endif //_CATAPULT_H_

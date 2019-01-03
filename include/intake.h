#ifndef _INTAKE_H_
#define _INTAKE_H_

extern int ballsInCat;

#define OUTTAKE -1
#define STOP_INTAKE 0
#define ONE_INTAKE 1
#define INTAKE 2

void setIntakeMtr(int power);

void intakeSlew(int goal, int slew);

bool getIntakeSensor();

void updateBallPos(int intakePower);

void intakeCtrl(int state); // -1 (backwards), 0 (stop), 1 (load one ball), 2 (forewards)

#endif //_INTAKE_H_

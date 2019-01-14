#ifndef _INTAKE_H_
#define _INTAKE_H_

extern int ballsInCat;

#define INTAKE_OUTTAKE -1
#define INTAKE_STOP 0
#define INTAKE_ONE 1
#define INTAKE_TWO 2
#define INTAKE_INTAKE 3

void setIntakeMtr(int power);

void intakeSlew(int goal, int slew);

bool getIntakeSensor();

void updateBallPos(int intakePower);

void intakeCtrl(int state); // -1 (backwards), 0 (stop), 1 (load one ball), 2 (forewards)

#endif //_INTAKE_H_

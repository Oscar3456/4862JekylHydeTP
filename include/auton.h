#ifndef _AUTON_H_
#define _AUTON_H_

#define NUM_AUTONS 2


#define TWO_FLAG 1
#define THREE_FLAG 2

void twoFlagRed();

void twoFlagBlue();

void robotAutonCtrl();

bool catIsDone();

bool intakeIsDone();

bool descoreIsDone();

bool driveIsDone();

void startTimer(int goal);

bool timer();

void await(bool (*isDone_ptr)() );

#endif //_AUTON_H_

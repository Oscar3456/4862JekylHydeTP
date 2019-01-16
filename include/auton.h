#ifndef _AUTON_H_
#define _AUTON_H_

#define NUM_AUTONS 2

void robotAutonCtrl();

bool catIsDone();

bool intakeIsDone();

bool descoreIsDone();

bool driveIsDone();

void await(bool (*isDone_ptr));

#endif //_AUTON_H_

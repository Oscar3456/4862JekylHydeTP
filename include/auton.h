#ifndef _AUTON_H_
#define _AUTON_H_

void robotAutonCtrl();

bool catIsDone();

bool intakeIsDone();

bool descoreIsDone();

bool driveIsDone();

void await(bool (*isDone_ptr));

#endif //_AUTON_H_

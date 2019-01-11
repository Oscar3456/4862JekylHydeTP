#ifndef _DRIVE_H_
#define _DRIVE_H_

#define DEFAULT_SLEW 5

void setDriveMtr(int leftPower, int rightPower);

void driveSlew(int leftGoal, int rightGoal, int slew);

#endif // _DRIVE_H_

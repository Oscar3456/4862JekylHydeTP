#include "main.h"
#include "intake.h"

#define STD_INTAKE_POW 110

#define STD_INTAKE_SLEW 5
#define FAST_INTAKE_SLEW 255

int ballsInCat;
bool ballInIntake; // ball is right at the top of the intake
int lastState;

void setIntakeMtr(int power){
  motorSet(BALL_INTAKE_MTR, power);
}

void intakeSlew(int goal, int slew){
  int power = motorGet(BALL_INTAKE_MTR);

  if(power + slew < goal){ // left slew
    power += slew;
  } else if(power - slew > goal){
    power -= slew;
  } else{
    power = goal;
  }

  setIntakeMtr(power);
}

bool getIntakeSensor();

void updateBallPos(int intakePower){
  if (intakePower > 0) {
    if (!ballInIntake && getIntakeSensor()){// if ball has entered intake
      ballInIntake = true;
    } else if(ballInIntake && !getIntakeSensor()){// if ball has entered cat
      ballInIntake = false;
      ballsInCat += 1;
    }
  } else{
    if(ballInIntake && !getIntakeSensor()){ // if ball has exited intake
      ballInIntake = false;
    }
  }
}

void intakeCtrl(int state){ // -1 (backwards), 0 (stop), 1 (load one ball), 2 (forewards)
  switch (state){
    case OUTTAKE:
      intakeSlew(STD_INTAKE_POW * -1, STD_INTAKE_SLEW);
      break;

    case STOP_INTAKE:
      intakeSlew(0, FAST_INTAKE_SLEW); // stop immediately
      break;

    case ONE_INTAKE:
      if(ballsInCat > 0) { // if balls are in intake
        intakeSlew(0, FAST_INTAKE_SLEW); // stop immediately
      } else {
        intakeSlew(STD_INTAKE_POW, STD_INTAKE_SLEW); // keep intaking
      }
      break;
    case INTAKE:
    intakeSlew(STD_INTAKE_POW, STD_INTAKE_SLEW);
      break;
  }

  updateBallPos(motorGet(BALL_INTAKE_MTR));
}

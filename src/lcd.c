#include "lcd.h"
#include "main.h"

#define LCD_AUTON 2
#define LCD_BAT 1
#define LCD_SENS 0
#define DEFAULT_AUTON 0

int lcdState = 1;

int autonChosen;
bool autonIsSelected = false;

int finalAuton;

int btnPressed;
int lastBtnPressed;

char autonNames[NUM_AUTONS][13] = {"2FLAG", "3FLAG"};

int getAuton(){
  int pot = analogRead(AUTON_POT);
  return pot / (4090/NUM_AUTONS);
}

void lcdCtrl(){
  btnPressed = lcdReadButtons(uart1);
  if(lastBtnPressed != btnPressed){
    switch(btnPressed){
      case 1:
        lcdState ++;
        break;
      case 2:
        switch(lcdState){
          case LCD_AUTON:
            autonIsSelected = !autonIsSelected;
            break;
          case LCD_SENS:
            zeroCatPot();
            break;
        }
      case 4:
        lcdState --;
    }
  }

  if(lcdState > 2){
    lcdState = 0;
  } else if(lcdState < 0){
    lcdState = 2;
  }

  switch(lcdState){
    case LCD_BAT:
      lcdClear(uart1);
      lcdPrint(uart1, 1, "M:%1.3f B:%1.3f", (double)powerLevelMain() / 1000, (double)powerLevelBackup() / 1000);
      lcdPrint(uart1, 2, "EXP:%1.3f", (double)analogRead(POWER_EXP_STATUS) / 270);
      break;
    case LCD_AUTON:
      lcdClear(uart1);
      autonChosen = getAuton();
      lcdPrint(uart1, 1, "%1i", autonChosen);
      if(autonIsSelected){
        lcdPrint(uart1, 2, "LOCKED");
        finalAuton = autonChosen;
      } else {
        finalAuton = DEFAULT_AUTON;
      }
      break;
    case LCD_SENS:
      lcdClear(uart1);
      lcdPrint(uart1, 1, "CAT: %4i", getCatPot());
      lcdPrint(uart1, 2, "BALLS: %1i", ballsInCat);
  }
}

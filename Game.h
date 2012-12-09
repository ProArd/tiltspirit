#ifndef Game_h
#define Game_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <LiquidCrystal.h>

#define GAME_TITLE 0
#define GAME_INTRO 1
#define GAME_INSTR 2
#define GAME_START 3
#define GAME_PLAY 4
#define GAME_DEATH 5
#define GAME_WIN 6
#define GAME_RESTART 7


#define WIDTH 16
#define HEIGHT 2
#define RED_BG 12
#define GREEN_BG 14
#define BLUE_BG 15

#define TILT_PINA 16
#define TILT_PINB 17
#define TILT_MID 1
#define TILT_L 0
#define TILT_R 2

extern unsigned long gTime;
extern long gPrevTime;

extern int tiltAState;
extern int tiltBState;
extern int tiltAVal;
extern int tiltBVal;
extern int tiltACnt;
extern int tiltBCnt;

extern int gameState; //Start, Play, DEATH, SUCCESS, Restart
extern int numGhosts;
extern int playerHealth;
extern int tiltStatus;  //0 = left, 1 = middle ,2 = right 
//combat
extern int leftEnergy;
extern int rightEnergy;

extern char combatBuff[17];
extern char spaces[17];
extern char bars[17];
  
extern byte squiGhost1L[8];
extern byte squiGhost1R[8];
extern byte squiGhost2L[8];
extern byte squiGhost2R[8];
extern byte squiGhost3L[8];
extern byte squiGhost3R[8];
  

//Enable the LCD object with the controls pins
extern LiquidCrystal lcd;


  int gameTitle();
  int gameIntro();
  int gameInstr();
  int gameStart();
  int gamePlay();
  int gameDeath();
  int gameWin() ;
  int gameRestart();
  int getTilt();
  int getGap(int star, int bar);
  void printGhost(int col, int row, int wait);

  
#endif

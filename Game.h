#ifndef Game_h
#define Game_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

//#include <LiquidCrystal.h>

//*	Nov  2,	2012	<MLS> Changed defines to enum
enum 
{
	GAME_TITLE	=	0,
	GAME_INTRO,
	GAME_INSTR,
	GAME_START,
	GAME_PLAY,
	GAME_DEATH,
	GAME_WIN,
	GAME_RESTART
};



extern unsigned long	gTime;
extern long	gPrevTime;

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

#define	kCombatBuffLen	17

extern char combatBuff[kCombatBuffLen];
extern char spaces[kCombatBuffLen];
extern char bars[kCombatBuffLen];
  
extern byte squiGhost1L[8];
extern byte squiGhost1R[8];
extern byte squiGhost2L[8];
extern byte squiGhost2R[8];
extern byte squiGhost3L[8];
extern byte squiGhost3R[8];
  

//Enable the LCD object with the controls pins
//extern LiquidCrystal lcd;


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

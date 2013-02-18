//************************************************************************
//*	
//*	I made a small tilt game for Arduiuno called "TIlt Spirit"
//*	
//*	It uses an Teensy or  Arduino Leonardo with a 3 pin tilt sensor that 
//*	triggers at 45 degrees, and displays the game on an standard 2x16 LCD screen.
//*	
//************************************************************************
//*	Edit History
//************************************************************************
//*	Nov  1,	2012	<ROA> Wrote Tilt Spirit game
//*	Nov  2,	2012	<MLS> Code review
//************************************************************************
#include <LiquidCrystal.h>
#include "Hardware.h"
#include "Game.h"


//************************************************************************
void setup() 
{
	pinMode(TILT_PINA, INPUT_PULLUP);
	pinMode(TILT_PINB, INPUT_PULLUP);
	tiltAState	=	digitalRead(TILT_PINA);
	tiltBState	=	digitalRead(TILT_PINB);

	//Enable the LCD layout information
	lcd.begin(WIDTH, HEIGHT);
	lcd.createChar(0, squiGhost1L);
	lcd.createChar(1, squiGhost1R);
	lcd.createChar(2, squiGhost2L);
	lcd.createChar(3, squiGhost2R);
	lcd.createChar(4, squiGhost3L);
	lcd.createChar(5, squiGhost3R);

}

//************************************************************************
//* The game status loop
//************************************************************************
//Note: shake to start
void loop() 
{
 
	switch (gameState) 
	{
		case GAME_TITLE:
			gameState	=	gameTitle();  
			break;

		case GAME_INTRO:
			gameState	=	gameIntro();  
			break;

		case GAME_INSTR:  
			gameState	=	gameInstr();  
			break;

		case GAME_START:  
			gameState	=	gameStart();  
			break;

		case GAME_PLAY:
			gameState	=	gamePlay();  
			break;

		case GAME_DEATH:
			gameState	=	gameDeath(); 
			break;

		case GAME_WIN:  
			gameState	=	gameWin(); 
			break;

		case GAME_RESTART:
			gameState	=	gameRestart();
			break;
	}
}

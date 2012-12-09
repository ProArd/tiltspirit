/*
* The game status loop
 */
#include <LiquidCrystal.h>
#include "Game.h"
#include "Memory.h"


void setup() 
{
  Serial.begin(9600);
  pinMode(TILT_PINA, INPUT_PULLUP);
  pinMode(TILT_PINB, INPUT_PULLUP);
  tiltAState = digitalRead(TILT_PINA);
  tiltBState = digitalRead(TILT_PINB);

  //Enable the LCD layout information
  lcd.begin(WIDTH, HEIGHT);
  lcd.createChar(0, squiGhost1L);
  lcd.createChar(1, squiGhost1R);
  lcd.createChar(2, squiGhost2L);
  lcd.createChar(3, squiGhost2R);
  lcd.createChar(4, squiGhost3L);
  lcd.createChar(5, squiGhost3R);

}

void loop() 
{
 
  switch (gameState) 
{
  case GAME_TITLE:
    gameState = gameTitle();  
    Serial.print("freeMemory()=");
    Serial.println(freeMemory());
    break;

  case GAME_INTRO:
    gameState = gameIntro();
   Serial.print("freeMemory()=");
    Serial.println(freeMemory());  
    break;

  case GAME_INSTR:  
    gameState = gameInstr();  
    break;

  case GAME_START:  
    gameState = gameStart();  
    break;

  case GAME_PLAY:
    gameState = gamePlay();  
    break;

  case GAME_DEATH:
    gameState = gameDeath(); 
    break;

  case GAME_WIN:  
    gameState = gameWin(); 
    break;

  case GAME_RESTART:
    gameState = gameRestart();
    Serial.print("freeMemory()=");
    Serial.println(freeMemory());
    break;
  }

}

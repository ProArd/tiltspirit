#include "Game.h"
#include "Hardware.h"

//Enable the LCD object with the controls pins
//LiquidCrystal lcd(7,8,9,10,11,12);

unsigned long gTime;
long gPrevTime		=	0;

int tiltAState;
int tiltBState;
int tiltAVal;
int tiltBVal;
int tiltACnt		=	0;
int tiltBCnt		=	0;

int gameState		=	0; //Start, Play, DEATH, SUCCESS, Restart
int numGhosts		=	3;
int playerHealth	=	3;
int tiltStatus;  //0 = left, 1 = middle ,2 = right 
//combat
int leftEnergy;
int rightEnergy;



char combatBuff[kCombatBuffLen]	=	{ "               "        };
char spaces[kCombatBuffLen]		=	{"                "};
char stars[kCombatBuffLen]		=	{ "****************"};
char bars[kCombatBuffLen]		=	{ "################"};


byte squiGhost1L[8]	=	
{
  B00111,
  B00110,
  B00111,
  B00001,
  B00011,
  B00101,
  B01010,
  B10101,
};

byte squiGhost1R[8]	=	
{
  B11100,
  B01100,
  B11100,
  B10000,
  B11000,
  B10100,
  B01010,
  B10101,
};

byte squiGhost2L[8]	=	
{
  B00111,
  B00101,
  B00111,
  B00011,
  B00101,
  B00100,
  B01010,
  B01010,
};

byte squiGhost2R[8]	=	
{
  B11100,
  B01100,
  B11100,
  B11000,
  B10100,
  B00100,
  B01010,
  B01010,
};

byte squiGhost3L[8]	=	
{
  B00111,
  B00110,
  B00111,
  B00001,
  B00011,
  B00101,
  B01011,
  B01010,
};

byte squiGhost3R[8]	=	
{
  B11100,
  B10100,
  B11100,
  B10000,
  B11000,
  B10100,
  B11010,
  B01010,
};

//************************************************************************
int gameTitle()
{
	long prevTime	=	millis();
	lcd.clear();
	while (1) 
	{
		gTime	=	millis();

		lcd.setCursor(0,0);
		lcd.print("Tilt Spirit");
		printGhost(14,0,200);
		/*
		lcd.setCursor(14,0);
		lcd.write((byte)0);
		lcd.write((byte)1);
		delay(200);
		lcd.setCursor(14,0);
		lcd.write((byte)2);
		lcd.write((byte)3);
		delay(200);
		lcd.setCursor(14,0);
		lcd.write((byte)4);
		lcd.write((byte)5);
		*/
		delay(200);

		lcd.setCursor(0,1);
		lcd.print("Focus to Live");
		if (gTime - prevTime > 3000) 
		{
			prevTime	=	gTime;
			break;
		}
	}
	return GAME_INTRO;
}

//************************************************************************
int gameIntro()
{

	lcd.clear();
	while (1) 
	{
		tiltStatus	=	getTilt();

		lcd.setCursor(0,0);
		lcd.print("<--Help|Start-->");
		printGhost(7,1,200);
		printGhost(0,1,200);

		if (tiltStatus == TILT_L) 
		{
			return GAME_INSTR;
		} 
		else if (tiltStatus == TILT_R) 
		{
			return GAME_START;
		}
	}
	return GAME_START;

}

//************************************************************************
int gameInstr() 
{
	lcd.clear();
	tiltACnt	=	0;

	while (1) 
	{
		tiltStatus	=	getTilt();
		if (tiltStatus == TILT_L) 
		{
		    tiltACnt++;
		}
		
		if (tiltStatus == TILT_R) 
		{
			return GAME_START;
		}  
		lcd.setCursor(0,0);
		lcd.print(tiltACnt);
		lcd.setCursor(4,0);
		lcd.print("<-- TILT -->");
		lcd.setCursor(0,1);
		lcd.print("Start  -->");
	}
	return GAME_INTRO;
}

//************************************************************************
int gameStart() 
{
	lcd.clear();
	long prevTime	=	millis();
	while (1) 
	{
		gTime	=	millis();

		lcd.setCursor(0,0);
		lcd.print("Focus Combat");
		lcd.setCursor(0,1);

		if (gTime - prevTime > 2000) 
		{
			lcd.print("Fight 3,");
		}
		
		if (gTime - prevTime > 3500) 
		{
			lcd.print(" 2,");
		}
		
		if (gTime - prevTime > 5000) 
		{
			lcd.print(" 1...");
		}
		
		if (gTime - prevTime > 6500) 
		{
			break;
		}
	}
	return GAME_PLAY;
}

//************************************************************************
int gamePlay() 
{
	tiltACnt	=	0;
	tiltBCnt	=	0;
	lcd.clear();

	while(1) 
	{
		tiltStatus	=	getTilt();

		switch (tiltStatus) 
		{
			case TILT_L:
				tiltACnt++;
				break;

			case TILT_R: 
				tiltBCnt++;
				break;

			case TILT_MID:
				break;
		}

		//How many stars, bars, gap, middle ghost
		leftEnergy	=	map(tiltACnt, 0, 1023, 0, 16);
		rightEnergy	=	map(tiltBCnt, 0, 1023,0, 16);
		if (leftEnergy < kCombatBuffLen && rightEnergy < kCombatBuffLen) 
		{
			if (leftEnergy == 8 && rightEnergy == 8) 
			{
				return GAME_WIN;
			}
			if (leftEnergy > 8|| rightEnergy > 8) 
			{
				return GAME_DEATH;
			}
			strcpy(combatBuff,bars);  
			int gap	=	getGap(leftEnergy, rightEnergy);
			strncpy(combatBuff,spaces, gap + leftEnergy);
			strncpy(combatBuff,stars, leftEnergy);
		} 
		else 
		{
			return GAME_DEATH;
		}

		// lcd.clear();
		lcd.setCursor(0,0);
		lcd.print(leftEnergy);
		lcd.setCursor(2,0);
		lcd.print("<-- TILT -->");
		lcd.setCursor(15,0);
		lcd.print(rightEnergy);

		lcd.setCursor(7,1);
		lcd.write((byte)0);
		lcd.write((byte)1);
		lcd.setCursor(0,1);

		lcd.print(combatBuff);
		lcd.setCursor(7,1);
		lcd.write((byte)0);
		lcd.write((byte)1);

	}

	return GAME_DEATH;
}

//************************************************************************
int gameDeath() 
{
	lcd.clear();
	long prevTime	=	millis();

	while (1) 
	{
		gTime	=	millis();
		lcd.setCursor(0,0);
		lcd.print("The ghost melds");
		lcd.setCursor(0,1);
		lcd.print("Soul Loss");
		printGhost(14,1, 200);
		printGhost(12,1, 200);
		
		if (gTime - prevTime > 4000) 
		{
			break;
		}
	}
	return GAME_RESTART;
}

//************************************************************************
int gameWin() 
{
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("Ghost Dispersed");
	lcd.setCursor(0,1);
	lcd.print("You Win!!!");
	delay(4000);
	return GAME_RESTART;
}

//************************************************************************
int gameRestart()
{
	lcd.clear();
	while (1) 
	{
		tiltStatus	=	getTilt();
		if (tiltStatus == TILT_R) 
		{
			break;
		}  
		lcd.setCursor(4,0);
		lcd.print("Refocus");
		lcd.setCursor(0,1);
		lcd.print("To Start -->");
		printGhost(0,0, 200);
		printGhost(14, 0, 200);
	}
	return GAME_START;
}


//************************************************************************
int getTilt() 
{
	bool AA	=	digitalRead(TILT_PINA);
	bool BB	=	digitalRead(TILT_PINB);

	if (AA == LOW) 
	{
		return TILT_L;
	}
	if (BB == LOW) 
	{
		return TILT_R;
	}
	return TILT_MID; 
}


//************************************************************************
int getGap(int star, int bar) 
{
	int gap	=	16 - (star + bar);
	return gap;
}

//************************************************************************
void printGhost(int col, int row, int wait) 
{

	lcd.setCursor(col,row);
	lcd.write((byte)0);
	lcd.write((byte)1);
	delay(wait);
	lcd.setCursor(col,row);
	lcd.write((byte)2);
	lcd.write((byte)3);
	delay(wait);
	lcd.setCursor(col,row);
	lcd.write((byte)4);
	lcd.write((byte)5);
}














#ifndef Hardware_h
#define Hardware_h

#include <LiquidCrystal.h>


#define	WIDTH		16
#define	HEIGHT		2
#define	RED_BG		3
#define	GREEN_BG	5
#define	BLUE_BG		6

#define	TILT_PINA	2
#define	TILT_PINB	4
#define	TILT_MID	1
#define	TILT_L		0
#define	TILT_R		2

#define LCD_PIN1  7
#define LCD_PIN2  8
#define LCD_PIN3  9
#define LCD_PIN4  10
#define LCD_PIN5  11
#define LCD_PIN6  12


//Enable the LCD object with the controls pins
extern LiquidCrystal lcd;

#endif

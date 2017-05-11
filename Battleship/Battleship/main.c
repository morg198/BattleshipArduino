/*
 * Battleship.c
 *
 * Created: 5/3/2017 9:49:51 PM
 * Author : dylan
 */ 

 #define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

//#include "Music.h"
#include "CommonFunctions.h"
#include "Joystick.h"
#include "LedPins.h"


enum GAME_STATES {MAIN_MENU, GAME1, GAME2, GAME3, GAMEOVER};

short joystickState = RELEASED;

struct LedPin rgbPin;

void MainMenu();

int gameMode = MAIN_MENU;

int main(void)
{
	DDRB = (1 << DDB1) | (1 << DDB2) | (1 << DDB3); //Sets the rgb pins to output

	

	/*****************************************************************************
	*	Pseudo Thoughts for parallel arrays
	*
	*		enum possibility: NO_SHIP, SHIP_UNKNOWN, SHIP_HIT, MISS
	*		
	*			LedPin ledGrid[3][4] 
	*			short gridInfo[3][4]
	*
	*		Possible use:
	*			player tries hitting 1, 2
	*				if gridInfo[1][2] ship_unknown
	*					set gridInfor[1][2] ship_hit
	*				.................................
	*				.................................
	*
	*			Update grid colors
	*				loop through grid info set ledgrid pin to correct color
	*	
	*****************************************************************************/


	InitializeLed(&rgbPin, B, B, B, DDB1, DDB2, DDB3);				//Initializes the rgb "pin" to hold the ports and registers of each node it is made of

	DDRC &= ( (0 << DDC0) | (0 << DDC1) | (0 << DDC2) | (0 << DDC3) | (0 << DDC4));		//Sets up the analog inputs to be read digitally as inputs

    /* Replace with your application code */
    while (1) 
    {

		ReadJoystickState(&joystickState);

		switch(gameMode)
		{
			case MAIN_MENU:
			MainMenu();
			break;
			case GAME1:
			SetColor(&rgbPin, 0, 1, 0);								//Sets pin to be magenta
			break;
			case GAME2:
			break;
			case GAME3:
			break;
			case GAMEOVER:
			break;
			default:
			break;
		}

		
	
    }
}

void MainMenu()
{
	switch(joystickState)
	{
		case UP:
		SetColor(&rgbPin, 1, 0, 1);								//Sets pin to be green
		break;
		case LEFT:
		SetColor(&rgbPin, 0, 1, 1);								//Sets pin to be red
		break;
		case DOWN:
		SetColor(&rgbPin, 1, 1, 0);								//Sets pin to be blue
		break;
		case RIGHT:
		SetColor(&rgbPin, 0, 0, 1);								//Sets pin to be yellow
		break;
		case PRESSED:
		
		gameMode = GAME1;
		break;
		case RELEASED:
		SetColor(&rgbPin, 0, 0, 0);		//Sets pin to be white
		break;
		default:
		break;
	}
}

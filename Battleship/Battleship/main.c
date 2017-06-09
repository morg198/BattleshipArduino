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

#include "Music.h"
#include "CommonFunctions.h"
#include "Joystick.h"
#include "ShiftRegisters.h"
#include "LedPins.h"
#include "LightsToArrays.h"


short posX = 0;
short posY = 0;

short TempVal = WATER;


enum GAME_STATES {MAIN_MENU, GAME1, GAME2, GAME3, GAMEOVER};

short joystickState = RELEASED;

struct LedPin rgbPin;

struct LedPin lights[GRIDHEIGHT][GRIDLENGTH];

short gameGrid[GRIDHEIGHT][GRIDLENGTH];
short lightGrid[GRIDHEIGHT][GRIDLENGTH];



void MainMenu();

int gameMode = MAIN_MENU;

void UpdateColors(struct LedPin lights[GRIDHEIGHT][GRIDLENGTH], short lightGrid[GRIDHEIGHT][GRIDLENGTH]);

void CheckForHit(short gameGrid[GRIDHEIGHT][GRIDLENGTH], short lightGrid[GRIDHEIGHT][GRIDLENGTH]);

bool CheckForWin(short lightGrid[GRIDHEIGHT][GRIDLENGTH]);

int main(void)
{
	InitializeRegister();

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

	for(int i = 0; i < GRIDHEIGHT; i++)
	{
		for(int j = 0; j < GRIDLENGTH; j++)
		{
			InitializeLed(&lights[i][j]);				//Initializes the light grid
			SetColor(&lights[i][j], OFF, ON, ON);

			gameGrid[i][j] = WATER;
			lightGrid[i][j] = WATER;
		}
	}

	GenerateShips(3, gameGrid);
	lightGrid[0][0] = HOVER;


	UpdateColors(lights, lightGrid);

	bool triggered = false;
	
	//DDRC &= ( (0 << DDC0) | (0 << DDC1) | (0 << DDC2) | (0 << DDC3) | (0 << DDC4));		//Sets up the analog inputs to be read digitally as inputs


	while(1)
	{		

			
			ReadJoystickState(&joystickState);

			switch(joystickState)
			{
				case UP:
					if( triggered == false && posY < GRIDHEIGHT - 1)
					{
						triggered = true;
						posY++;

						lightGrid[posY - 1][posX] = TempVal;
						TempVal = lightGrid[posY][posX];
					}
				break;

				case DOWN:
					if( triggered == false && posY > 0)
					{
						triggered = true;
						posY--;

						lightGrid[posY + 1][posX] = TempVal;
						TempVal = lightGrid[posY][posX];
					}
				break;

				case LEFT:
					if( triggered == false && posX < GRIDLENGTH - 1)
					{
						triggered = true;
						posX++;

						lightGrid[posY][posX - 1] = TempVal;
						TempVal = lightGrid[posY][posX];
					}
				break;

				case RIGHT:
					if( triggered == false && posX > 0)
					{
						triggered = true;
						posX--;

						lightGrid[posY][posX + 1] = TempVal;
						TempVal = lightGrid[posY][posX];
					}
				break;

				case PRESSED:
				CheckForHit(gameGrid, lightGrid);

				break;

				case RELEASED:
					if(triggered == true)
					{
						triggered = false;
					}
				break;

				default:
				break;

			}

			lightGrid[posY][posX] = HOVER;

			UpdateColors(lightGrid);

			if(CheckForWin(lightGrid) == true)
			{

				for(int i = 0; i < GRIDHEIGHT; i++)
				{
					for(int j = 0; j < GRIDLENGTH; j++)
					{
						SetColor(lights, ON, OFF, ON);
					}
				}
				for(int i = 0; i < 100; i++)
				{
					TestWrite(GetNumArray(lights));
					LatchIn();
					_delay_ms(100);
				}
			}

			TestWrite(GetNumArray(lights));

			//TestWrite(test);
			LatchIn();
			_delay_ms(100);
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

void UpdateColors(struct LedPin lights[GRIDHEIGHT][GRIDLENGTH], short lightGrid[GRIDHEIGHT][GRIDLENGTH])
{
	for(int i = 0; i < GRIDHEIGHT; i++)
	{
		for(int j = 0; j < GRIDLENGTH; j++)
		{
			switch(gameGrid[i][j])
			{
				case WATER:
					SetColor(&lights[i][j], OFF, ON, ON);
				break;

				case SHIP:
					SetColor(&lights[i][j], OFF, ON, ON);
				break;

				case HIT:
					SetColor(&lights[i][j], OFF, ON, OFF);

				break;

				case MISS:
					SetColor(&lights[i][j], ON, OFF, OFF);
				break;

				case HOVER:

					SetColor(&lights[i][j], ON, ON, OFF);
				break;

				default:

				break;
			}
		}
	}
}

void CheckForHit(short gameGrid[GRIDHEIGHT][GRIDLENGTH], short lightGrid[GRIDHEIGHT][GRIDLENGTH])
{
	if(gameGrid[posY][posX] == SHIP)
	{
		lightGrid[posY][posX] = HIT;
	}
	else
	{
		lightGrid[posY][posX] = MISS;
	}
}


bool CheckForWin(short lightGrid[GRIDHEIGHT][GRIDLENGTH])
{
bool won = true;
	for(int i = 0; i < GRIDHEIGHT; i++)
	{
		for(int j = 0; j < GRIDLENGTH; j++)
		{
			if(lightGrid[i][j] == HOVER && TempVal == SHIP)
			{
				won = false;
				break;
			}

			else if(lightGrid[i][j] == SHIP)
			{
				won = false;
				break;
			}
		}
	}

	return won;
}
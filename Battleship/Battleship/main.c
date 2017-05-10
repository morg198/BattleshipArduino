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
//#include "Music.h"
#include "CommonFunctions.h"

void InitializeJoyStick();




int main(void)
{
	DDRB = (1 << DDB1) | (1 << DDB2) | (1 << DDB3); //Sets the rgb pins to output

	struct LedPin rgbPin;

	InitializeLed(&rgbPin, B, B, B, DDB1, DDB2, DDB3);				//Initializes the rgb "pin" to hold the ports and registers of each node it is made of

	DDRC &= ( (0 << DDC0) | (0 << DDC1) | (0 << DDC2) | (0 << DDC3) | (0 << DDC4));		//Sets up the analog inputs to be read digitally as inputs

    /* Replace with your application code */
    while (1) 
    {

		if(JoyStickUp())
		{
			SetColor(&rgbPin, 1, 0, 1);								//Sets pin to be green
		}
		else if(JoyStickLeft())
		{
			SetColor(&rgbPin, 0, 1, 1);								//Sets pin to be red
		}
		else if(JoyStickDown())
		{
			SetColor(&rgbPin, 1, 1, 0);								//Sets pin to be blue
		}
		else if(JoyStickRight())
		{
			SetColor(&rgbPin, 0, 0, 1);								//Sets pin to be yellow
		}
		else if(JoyStickPress())
		{
			SetColor(&rgbPin, 0, 1, 0);								//Sets pin to be magenta
		}
		else
		{
			SetColor(&rgbPin, 0, 0, 0);		//Sets pin to be white
		}
	
    }
}


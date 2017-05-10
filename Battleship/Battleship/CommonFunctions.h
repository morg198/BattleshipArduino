/*
 * CommonFunctions.h
 *
 * Created: 5/3/2017 9:54:17 PM
 *  Author: dylan
 */ 


#ifndef COMMONFUNCTIONS_H_
#define COMMONFUNCTIONS_H_
#include "Types.h"

enum ALLPORTS {B = 0, C, D};

typedef short bool;
#define true 1
#define false 0


/*
	Joystick Assumptions:
	
	Pin Numbers:

	Up = analog 0
	Left = analog 1
	Down = analog 2
	Right = analog 3
	Press = analog 4
	
*/
bool JoyStickUp()
{
	bool up = false;
	if(!(PINC & (1 << PINC0)))
	{
		up = true;
	}
	else
	{
		up = false;
	}
	return up;
}

bool JoyStickLeft()
{
	bool on = false;
	if(!(PINC & (1 << PINC1)))
	{
		on = true;
	}
	else
	{
		on = false;
	}
	return on;
}

bool JoyStickDown()
{
	bool on = false;
	if(!(PINC & (1 << PINC2)))
	{
		on = true;
	}
	else
	{
		on = false;
	}
	return on;
}

bool JoyStickRight()
{
	bool on = false;
	if(!(PINC & (1 << PINC3)))
	{
		on = true;
	}
	else
	{
		on = false;
	}
	return on;
}

bool JoyStickPress()
{
	bool on = false;
	if(!(PINC & (1 << PINC4)))
	{
		on = true;
	}
	else
	{
		on = false;
	}
	return on;
}

struct LedPin
{
	int ports[3];
	int regLocs[3];
};

/************************************************************************/
/*  Purpose: Initializes an rgb led pin to hold the values of its       */
/*				ports and register locations, takes a pointer to the	*/
/*				struct then all the needed values						*/
/************************************************************************/
void InitializeLed(struct LedPin * pin, int port1, int port2, int port3, int regLoc1, int regLoc2, int regLoc3)
{
	pin->ports[0] = port1;
	pin->ports[1] = port2;
	pin->ports[2] = port3;

	pin->regLocs[0] = regLoc1;
	pin->regLocs[1] = regLoc2;
	pin->regLocs[2] = regLoc3;
}

/************************************************************************/
/*  Purpose: Function to clear a rgb pins values so when they are set	*/
/*			by or'ing if there is a need for a 0 it will be set properly*/
/************************************************************************/
void ClearPin(struct LedPin* pin)
{
	for(int i = 0; i < 3; i++)
	{
		switch(pin->ports[i])
		{
			case B:
			PORTB &= (0 << pin->regLocs[i]);				//Ands each register of the rgb pin in port b with 0 (thus ensuring that bit will be 0)
			break;
			case C:
			PORTC &= (0 << pin->regLocs[i]);				//Ands each register of the rgb pin in port c with 0 (thus ensuring that bit will be 0)
			break;
			case D:
			PORTD &= (0 << pin->regLocs[i]);				//Ands each register of the rgb pin in port d with 0 (thus ensuring that bit will be 0)
			break;
			default:
			break;
		}
	}
}

/************************************************************************/
/*  Purpose: Function to set the color of a rgb pin. Takes a pointer to */
/*			to the pin struct, and the digital rgb values				*/
/************************************************************************/
void SetColor(struct LedPin*  lightPin, int r, int g, int b)
{
	_delay_ms(2);													//Delay 2 ms to show the color
	ClearPin(lightPin);												//First we make all of the pin values that make up the rgb pin 0 so that when we or it if it is 1 it will set it to 1 if it is 0 it will stay 0
	ShiftPort((lightPin)->ports[0], (lightPin)->regLocs[0], r);		//Shift the r value passed into this function into the register bit of the red pin
	ShiftPort((lightPin)->ports[1], (lightPin)->regLocs[1], g);		//Shift the g value passed into this function into the register bit of the green pin
	ShiftPort((lightPin)->ports[2], (lightPin)->regLocs[2], b);		//Shift the b value passed into this function into the register bit of the blue pin
}


/*******************************************************
* Function used to bitshift a value into a register given
*		the port as an int(see enum types above), the
*			regLoc(register location), and the value to
*			shift in
*
*	Ex Call: ShiftPort(C, DDC4, 1) will shift 1 into
*			port c's 5th register bit (DDC0 is first)
*
*		Reset					PC6
*
*		Digital Pin 0			PD0
*
*		Digital Pin 1			PD1
*
*		Digital Pin 2			PD2
*
*		Digital Pin 3			PD3
*
*		Digital Pin 4			PD4
*
*		Digital Pin 5			PD5
*
*		Digital Pin 6			PD6
*
*		Digital Pin 7			PD7
*
*		Digital Pin 8			PB0
*
*		Digital Pin 9			PB1
*
*		Digital Pin 10			PB2
*
*		Digital Pin 11			PB3
*
*		Digital Pin 12			PB4
*
*		Digital Pin 13			PB5
*
*		Analog Input 0			PC0
*
*		Analog Input 1			PC1
*
*		Analog Input 2			PC2
*
*		Analog Input 3			PC3
*
*		Analog Input 4			PC4
*
*		Analog Input 5			PC5
*
*******************************************************/
void ShiftPort(int port, int regLoc, short val)
{
	switch(port)
	{
		case B:				
				PORTB |= (val << regLoc);				
			break;
		case C:
				PORTC |= (val << regLoc);			
			break;
		case D:
				PORTD |= (val << regLoc);			
			break;
		default:
			break;
	}
}


void IncrementTimer(struct Timer *t)
{
	t->counter += 1;
}

void IncrementTimerX(int am, struct Timer *t)
{
	t->counter += am;
}

void ResetTimer(struct Timer *t)
{
	t->counter = 0;
}

/*******************************************************
* Function to delay in microseconds ( 50 at a time )
* Use for longer delays divisible by 50
*******************************************************/
void Delay(long t)
{
	while(t > 0)
	{
		_delay_us(50);
		t -= 50;
	}
}

void DelayMicro(long t)
{
	while(t > 0)
	{
		_delay_us(1);
		t--;
	}
}

#endif /* COMMONFUNCTIONS_H_ */
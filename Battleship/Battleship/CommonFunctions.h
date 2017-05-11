/*
 * CommonFunctions.h
 *
 * Created: 5/3/2017 9:54:17 PM
 *  Author: dylan
 */ 


#ifndef COMMONFUNCTIONS_H_
#define COMMONFUNCTIONS_H_
#include "Types.h"
#include <time.h>

enum ALLPORTS {B = 0, C, D};




typedef short bool;
#define true 1
#define false 0

void SeedRand()
{
	srand(time(NULL));
}

int RNG(int min, int max)
{
	return rand() % (max - min + 1) + min;
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
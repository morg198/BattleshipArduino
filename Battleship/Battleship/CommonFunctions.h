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

/*******************************************************
* Function used to bitshift a value into a register given
*		the port as an int(see enum types above), the
*			regLoc(register location), and the value to
*			shift in
*
*	Ex Call: ShiftPort(C, DDC4, 1) will shift 1 into
*			port c's 5th register bit (DDC0 is first)
*
*	See Word Doc Klamath ex for img showing which register
*		connects to which pin
*
*	To Do:
*			Add comment block showing registers and their
*			corresponding pins
*******************************************************/
void ShiftPort(int port, int regLoc, short val)
{
	switch(port)
	{
		case B:
		PORTB = (val << regLoc);
		
		break;
		case C:
		PORTC = (val << regLoc);
		break;
		case D:
		PORTD = (val << regLoc);
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
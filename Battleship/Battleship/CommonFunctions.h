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

void DelayMicro(long t)
{
	while(t > 0)
	{
		_delay_us(1);
		t--;
	}
}

#endif /* COMMONFUNCTIONS_H_ */
/*
 * LedPins.h
 *
 * Created: 5/10/2017 7:03:12 PM
 *  Author: dylan
 */ 


#ifndef LEDPINS_H_
#define LEDPINS_H_

#define RED 0
#define GREEN 1
#define BLUE 2

#define ON 0
#define OFF 1

struct LedPin
{
	int ports[3];
	int regLocs[3];
	int values[3];
};

/************************************************************************/
/*  Purpose: Initializes an rgb led pin to hold the values of its       */
/*				ports and register locations, takes a pointer to the	*/
/*				struct then all the needed values						*/
/************************************************************************/
void InitializeLed(struct LedPin * pin)
{
	pin->values[0] = OFF;
	pin->values[1] = OFF;
	pin->values[2] = OFF;
}

/************************************************************************/
/*  Purpose: Function to clear a rgb pins values so when they are set	*/
/*			by or'ing if there is a need for a 0 it will be set properly*/
/************************************************************************/
void ClearPin(struct LedPin* pin)
{
	for(int i = 0; i < 3; i++)
	{
		pin->values[i] = OFF;
	}
}

/************************************************************************/
/*  Purpose: Function to set the color of a rgb pin. Takes a pointer to */
/*			to the pin struct, and the digital rgb values				*/
/************************************************************************/
void SetColor(struct LedPin*  lightPin, int r, int g, int b)
{
	_delay_ms(2);													//Delay 2 ms to show the color
	lightPin->values[RED] = r;
	lightPin->values[GREEN] = g;
	lightPin->values[BLUE] = b;
}



#endif /* LEDPINS_H_ */
/*
 * LedPins.h
 *
 * Created: 5/10/2017 7:03:12 PM
 *  Author: dylan
 */ 


#ifndef LEDPINS_H_
#define LEDPINS_H_


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



#endif /* LEDPINS_H_ */
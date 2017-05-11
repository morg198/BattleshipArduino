/*
 * Joystick.h
 *
 * Created: 5/10/2017 7:02:27 PM
 *  Author: dylan
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_

enum {UP, LEFT, DOWN, RIGHT, PRESSED, RELEASED};

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

void ReadJoystickState(int * joystickState)
{
	if(JoyStickUp())
	{
		*joystickState = UP;
	}
	else if(JoyStickLeft())
	{
		*joystickState = LEFT;
	}
	else if(JoyStickDown())
	{
		*joystickState = DOWN;
	}
	else if(JoyStickRight())
	{
		*joystickState = RIGHT;
	}
	else if(JoyStickPress())
	{
		*joystickState = PRESSED;
	}
	else
	{
		*joystickState = RELEASED;
	}
}



#endif /* JOYSTICK_H_ */
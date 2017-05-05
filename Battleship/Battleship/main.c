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
#include "Music.h"


int main(void)
{
	DDRB = (1 << DDB1);

	struct Song yubNub;
	CreateYubNub(&yubNub);
	PlaySong(&yubNub);
	
    /* Replace with your application code */
    while (1) 
    {
		
    }
}


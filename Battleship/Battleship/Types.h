/*
 * Types.h
 *
 * Created: 5/3/2017 10:36:28 PM
 *  Author: dylan
 */ 


#ifndef TYPES_H_
#define TYPES_H_


/******************************************************************
*	Structure used to hold the needed information for a song
*		these are:
*			the number of beats
*			the notes
*			the length of the notes(beats)
*******************************************************************/
struct Song
{
	int length;

	int * notes;
	int * beats;
};


/******************************************************************
*	Structure used as a timer or counter
*******************************************************************/
struct Timer
{
	unsigned long counter;
};


#endif /* TYPES_H_ */
/*
 * Types.h
 *
 * Created: 5/3/2017 10:36:28 PM
 *  Author: dylan
 */ 


#ifndef TYPES_H_
#define TYPES_H_


struct Song
{
	int length;

	int * notes;
	int * beats;
};

struct Timer
{
	unsigned long counter;
};


#endif /* TYPES_H_ */
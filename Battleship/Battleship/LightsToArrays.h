/*
 * LightsToArrays.h
 *
 * Created: 6/3/2017 8:06:10 AM
 *  Author: dylan
 */ 


#ifndef LIGHTSTOARRAYS_H_
#define LIGHTSTOARRAYS_H_

 #include "LedPins.h"
 #include "arraytolong.h"

 //short numArr[GRIDLENGTH][GRIDHEIGHT];
 short numArr[GRIDLENGTH * GRIDHEIGHT * 3];
 unsigned short * GetNumArray(struct LedPin pins[2][2])
 {
	

	//int k = 0;
//
//
	//for(int i = 0; i < GRIDLENGTH; i++)
	//{
		//for(int j = 0; j < GRIDHEIGHT; j += 3)
		//{
			//numArr[i][j] = pins[i][k].values[0];
			//numArr[i][j + 1] = pins[i][k].values[1];
			//numArr[i][j + 2] = pins[i][k].values[2];
			//k++;
		//}
	//}

	int a = 0;
	

	for(int i = 0; i < GRIDLENGTH; i++)
	{
		for(int j = 0; j < GRIDHEIGHT; j++)
		{
			for(int k = 0; k < 3; k++)
			{
				numArr[a] = pins[i][j].values[k];
				a++;
			}
		}
	}
	return numArr;
 }




#endif /* LIGHTSTOARRAYS_H_ */
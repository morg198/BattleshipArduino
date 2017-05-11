/*
 * Music.h
 *
 * Created: 5/3/2017 10:09:09 PM
 *  Author: dylan
 */ 


#ifndef MUSIC_H_
#define MUSIC_H_
#include "CommonFunctions.h"
#include "Pitches.h"

void PlayTone (int frequencyInHertz, long timeInMilliseconds, enum ALLPORTS port, int regLoc, int tempoOne, int tempoTwo)
{
	int x;
	long delayAmount = (long)(1000000/frequencyInHertz);
	long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));

	for (x=0;x<loopTime;x++)
	{
		struct Timer t1;

		
		ShiftPort(port, regLoc, 1);
		while(t1.counter < delayAmount)
		{
			_delay_us(tempoOne);
			//Delay(delayAmount);
			IncrementTimerX(tempoTwo, &t1);
		}
		
		ResetTimer(&t1);

		
		ShiftPort(port, regLoc, 0);
			//Delay(delayAmount);
		while(t1.counter < delayAmount)
		{
			_delay_us(tempoOne);
			IncrementTimerX(tempoTwo, &t1);
		}
	}
	Delay(50000); // a gap between notes
	Delay(50000);
}

void CreateSong(struct Song * s)
{
	
	int WWRY[] = {	NOTE_D4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,
		NOTE_E4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_E4,
		NOTE_E4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_E4,
		NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_C3, NOTE_C3, NOTE_C2, NOTE_C2, NOTE_C4, NOTE_D4,

	};

	int wwryBeats[] = {	16, 16, 16, 16, 8, 16, 16, 8, 8, 16, 16, 16, 16,
		8, 16, 16, 16, 16, 8, 8, 8, 16, 16, 8,
		8, 16, 16, 8, 8, 8, 8, 4,
		16, 16, 8, 8, 16, 8, 16, 16, 8, 8, 16, 16
	};

	for(int i = 0; i < s->length; i++)
	{
		*(s->notes + i) = WWRY[i];
		*(s->beats + i) = wwryBeats[i];
	}
}

	
void CreateYubNub(struct Song * s)
{

	for(int i = 0; i < s.length; i++)
	{
		free(s.notes[i]);
		free(s.beats[i]);
	}

	s->length = 41;

	s->notes = (int *) calloc(s.length, sizeof(int));

	s->beats = (int *) calloc(s.length, sizeof(int));

	int YN[] = {	NOTE_C4 + NOTE_G4, NOTE_C4 + NOTE_G4, 0,
					0, NOTE_E4, NOTE_G4, 0, 
					NOTE_E4 + NOTE_A4, NOTE_E4 + NOTE_A4, 0,
					0, 0, 0, NOTE_F4,
					NOTE_E4 + NOTE_G4, NOTE_E4 + NOTE_G4, NOTE_E4 + NOTE_G4, NOTE_A4, NOTE_B4, NOTE_A6 + NOTE_E4,
					0, 0, NOTE_G4, NOTE_A4, NOTE_B4,
					NOTE_A4 + NOTE_A6, NOTE_AS4 + NOTE_AS6, NOTE_AS4 + NOTE_AS6 + NOTE_AS4 + NOTE_AS6, NOTE_B4 + NOTE_B6,
					NOTE_B4 + NOTE_B6, 0,
					NOTE_C4 + NOTE_G4, NOTE_C4 + NOTE_G4, 0,
					0, NOTE_E4, NOTE_G4, 0,
					NOTE_E4 + NOTE_A4, NOTE_E4 + NOTE_G4, 0
	};

	int ynBeats[] = {	4, 4, 2,
						2, 8, 8, 4,
						4, 4, 2,
						2, 4, 8, 8,
						4, 4, 8, 8, 8, 8,
						8, 4, 8, 4, 4,

						4, 8, 4, 4,
						4, 4, 2,
						2, 8, 8, 4
						2, 4,
						4, 4, 2,
						2, 8, 8, 4,
						4, 4, 2
	};

	
	for(int i = 0; i < s->length; i++)
	{
		*(s->notes + i) = YN[i];
		*(s->beats + i) = ynBeats[i];
	}

}


void PlaySong(struct Song *s)
{
	for(int i = 0; i < s->length; i++)
	{
		int noteDuration = 1000 / s->beats[i];
		if(s->notes[i] == 0)
		{
			DelayMicro(noteDuration);
		}
		else
		{
			PlayTone(s->notes[i], noteDuration, B, DDB1, 5, 3);
		}
	}

	for(int i = 0; i < s->length; i++)
	{
		free(s->notes[i]);
		free(s->beats[i]);
	}
	free(s->notes);
	free(s->beats);
}

#endif /* MUSIC_H_ */
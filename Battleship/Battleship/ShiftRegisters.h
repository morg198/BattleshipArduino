/*
 * ShiftRegisters.h
 *
 * Created: 5/18/2017 2:55:38 PM
 *  Author: dylan
 */ 


#ifndef SHIFTREGISTERS_H_
#define SHIFTREGISTERS_H_

#include <avr/io.h>
#include <util/delay.h>

//How the register is connected to the arduino
#define CONTROL_DDR		DDRB
#define CONTROL_PORT	PORTB
#define DataPin			0
#define EnablePin		1
#define LatchClkPin		2
#define ShiftClkPin		3
#define ResetPin		4

//Control of shift register
#define delay(a)				_delay_ms(a)
#define DataHigh()				(CONTROL_PORT |= (1 << DataPin))
#define DataLow()				(CONTROL_PORT &= (~(1 << DataPin))

#define HIGH 1
#define LOW 0

const int NUMBER_REGISTERS = 6;


uint8_t ArrayToByte(int arr[8])
{
	uint8_t byte;

	byte |= (arr[7] << 0) | (arr[6] << 1) | (arr[5] << 2) | (arr[4] << 3) | (arr[3] << 4) | (arr[2] << 5) | (arr[1] << 6) | (arr[0] << 7);

	return byte;
}

void InitializeRegister()
{
	CONTROL_DDR |= ((1 << DataPin) | (1 << ShiftClkPin) | (1 << LatchClkPin));
}



void PulseClock()
{
	CONTROL_PORT |= (1 << ShiftClkPin); //HIGH
	CONTROL_PORT &= (~(1 << ShiftClkPin)); //LOW


}

void LatchIn()
{
	CONTROL_PORT |= (1 << LatchClkPin); //HIGH
	_delay_loop_1(1);
	CONTROL_PORT |= (1 << LatchClkPin); //LOW
	_delay_loop_1(1);
}


void WriteSerial(uint8_t dataByte)
{
	//Send each bit serially

	//MSB order
	for(uint8_t i = 0; i < 8; i++)
	{
		//Output the data on the line from the MSB
		if(dataByte & 0b10000000)
		{
			//MSB is 1 so set high
			DataHigh();
		}
		else
		{
			DataLow();
		}

		PulseClock();	

		dataByte = dataByte << 1;		//Brings the next bit to the MSB
	}

	LatchIn(); //Outs in parallel
}

void Example()
{
	//Done before loop
	InitializeRegister();

	int output[8] = {HIGH, HIGH, LOW, LOW, LOW, HIGH, LOW, HIGH};
	//Done in loop

	WriteSerial(ArrayToByte(output));


}
#endif /* SHIFTREGISTERS_H_ */
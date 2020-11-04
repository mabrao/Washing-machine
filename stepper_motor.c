#define F_CPU 16000000UL //define for delay
// include files
#include <avr/io.h>
#include <util/delay.h>
#include "stepper_motor.h"
//#include "io_ports.h"


//arrays for motor
uint8_t Wave[4] = {0x01, 0x02, 0x04, 0x08};
uint8_t Full[4] = {0x09, 0x03, 0x06, 0x0C};
uint8_t Half[8] = {0x09, 0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08};
	
void Stepper_Drive(char mode,uint8_t revolutions)
{
	uint16_t steps = 2; //what should be the data type of steps?
	//you need to calculate the steps needed for each revolution
	switch (mode)
	{
		case 'W':
		steps = revolutions * 2048UL / 4; //each rev takes 32*64 steps, array has
		//4 elements
		//you need to calculate the steps needed for each revolution
		for(uint16_t i = 0; i< steps; i++) //loop thru array # of times
		{
			for(uint16_t j = 0; j< 4; j++) //loop thru the whole array
			{
				PORTL = Wave[j];
				_delay_ms(5);
			}
		}
		break;
		case 'F':
		steps = revolutions * 2048UL / 4;
		//you need to calculate the steps needed for each revolution
		for(uint16_t i = 0; i< steps; i++)
		{
			for(uint16_t j = 0; j< 4; j++)
			{
				PORTL = Full[j];
				_delay_ms(5);
			}
		}
		break;
		case 'H':
		steps = revolutions * 4096UL / 8;
		//you need to calculate the steps needed for each revolution
		for(uint16_t i = 0; i< steps; i++)
		{
			for(uint16_t j = 0; j< 8; j++)
			{
				PORTL = Half[j];
				_delay_ms(5);
			}
		}
		break;
	}
}

void Motor_Control (char mode, uint8_t mTime)
{
	//uint8_t Half2[8] = {0x08, 0x0C, 0x04, 0x06, 0x02, 0x03, 0x01, 0x09};
	switch (mode)
	{
		case 'A': //if SW0 is pressed, start Wave Step mode
		{
			Stepper_Drive_Time('H',mTime);
			break;
		}
		case 'S': //if SW1 is pressed, Full Step mode
		{
			Stepper_Drive_Time('F',mTime);
			break;
		}
		case 'OFF': //if SW2 is pressed, Half Step mode
		{
			PORTL = 0x00;
			break;
		}
	}
	PORTL = 0x00; //clear output when done
}


void Stepper_Drive_Time(char mode,uint8_t t)
{
	uint8_t Half2[8] = {0x08, 0x0C, 0x04, 0x06, 0x02, 0x03, 0x01, 0x09};
	uint8_t steps = 25; //what should be the data type of steps?
	//you need to calculate the steps needed for each revolution
	switch (mode)
	{
		case 'W':
		//steps = revolutions * 2048UL / 4; //each rev takes 32*64 steps, array has
		//4 elements
		//you need to calculate the steps needed for each revolution
		for(uint16_t i = 0; i< steps; i++) //loop thru array # of times
		{
			for(uint16_t j = 0; j< 4; j++) //loop thru the whole array
			{
				PORTL = Wave[j];
				_delay_ms(5);
			}
		}
		break;
		case 'F':
		//steps = revolutions * 2048UL / 4;
		//you need to calculate the steps needed for each revolution
		for(uint16_t i = 0; i< 50*t; i++)
		{
			for(uint16_t j = 0; j< 4; j++)
			{
				PORTL = Full[j];
				_delay_ms(3);
			}
		}
		break;
		case 'H':
		//steps = revolutions * 4096UL / 8;
		//you need to calculate the steps needed for each revolution
		for (uint8_t k= 0; k< (t/2);k++)
		{
			for(uint16_t i = 0; i< 25; i++) // 25=1s/8step/5ms
			{
				for(uint16_t j = 0; j< 8; j++)
				{
					PORTL = Half[j];
					_delay_ms(5);
				}
			}
			for(uint16_t i = 0; i< 25; i++)
			{
				for(uint16_t j = 0; j< 8; j++)
				{
					PORTL = Half2[j];
					_delay_ms(5);
				}
			}
		}
		break;
	}
}
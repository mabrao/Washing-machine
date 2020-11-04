/*
* Name_of_your_file.c
*
* Created: Date and time of your file
* Author : Matheus Abrao
*
*
* Project name:Three_Modes_Stepper
* Description:
* Control stepper motor thru three different modes:
* Wave step mode
* Full step mode
* Half step mode
*
* Three arrays with data corresponding to the bit
* pattern necessary to move the stepper motor. Code
* has a for loop in either 4 or 8 iterations depending
* on the drive mode for the stepper
*
* Use system delay function _delay_ms(3) Delay 3mS in between
* each step (below 1ms won't work)
*
* Hardware: (output)
* IN1 ---- PF.0
* IN2 ---- PF.1
* IN3 ---- PF.2
* IN4 ---- PF.3
* Input
* SW0 ---- PA.0 WaveStep mode
* SW1 ---- PA.1 FullStep mode
* SW2 ---- PA.2 HalfStep mode
*
* The code is written as a multi module program
*
****************************************************/
#define F_CPU 16000000UL //define for delay
// include files
#include <avr/io.h>
#include <util/delay.h>
#include "stepper_motor.h"
#include "io_ports.h"


int main(void)
{
	
	io_init(); // initialize IOs, defined in io_ports module
	uint8_t n = 1; //number of revolutions for turning the stepper motor
	//2048 steps per revolution
	while(1)
	{
		switch (PushButton)
		{
			case Wave_Step: //if SW0 is pressed, start Wave Step mode
			{
				Stepper_Drive('W',n);
				break;
			}
			case Full_Step: //if SW1 is pressed, Full Step mode
			{
				Stepper_Drive('F',n);
				break;
			}
			case Half_Step: //if SW2 is pressed, Half Step mode
			{
				Stepper_Drive('H',n);
				break;
			}
		}
		PORTL = 0x00; //clear output when done
	}
}
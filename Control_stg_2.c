/*
 * Washing Machine Project
 * Control_stg_1.c
 *
 * Author: Matheus Abrao
 *
 * 2/11/19
 *
 * This code will simulate the operation
 * of a washing machine, by using a stepper
 * motor as an output and switches as inputs.
 *
 * Inputs:
 * Hot - PA.0
 * Warm - PA.1
 * Cold - PA.2
 * Door Open - PA.3
 * Start push-button - PA.4
 *
 * Outputs:
 * IN1 - PL.0
 * IN2 - PL.1
 * IN3 - PL.2
 * IN4 - PL.3
 * Drain Valve - PK.0
 * Hot Water Valve - PK.4
 * Cold Water Valve - PK.2
 * Wash Finished LED - PK.3
 *
 */ 

//preprocessor directives:
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "stepper_motor.h"




int main(void)
{
    DDRL = 0xFF; //PORTL as an input
	PORTL = 0x00; //Pull ups on
	DDRK = 0xFF; //PORTK as an output
	PORTK = 0x00; //Start with outputs off
	
    while (1) 
    {
		_delay_ms(5000);
		while((PINA & 0x10) == 0x00) //wait for start pb
		{
		}
		while(PINA & 0x08) //don't start if door is open
		{	
		}
		if(PINA & 0x01) //hot mode
		{
			PORTK = 0x10;
			_delay_ms(4000);
		}
		if(PINA &  0x02) //warm mode
		{
			PORTK = 0x14;
			_delay_ms(4000);
		}
		if(PINA & 0x04) //cold mode
		{
			PORTK = 0x04;
			_delay_ms(4000);
		}
		PORTK = 0x00; //reset output
		//_delay_ms(4000);
		Motor_Control('A', 8); //motor in agitate for 8 seconds
		PORTL = 0x00;//motor off
		PORTK = 0x01; //drain valve on
		_delay_ms(4000);
		PORTK = 0x00; //drain valve off
		_delay_ms(4000);
		if(PINA & 0x01) //hot mode
		{
			PORTK = 0x10;
			_delay_ms(4000);
		}
		if(PINA &  0x02) //warm mode
		{
			PORTK = 0x14;
			_delay_ms(4000);
		}
		if(PINA & 0x04) //cold mode
		{
			PORTK = 0x04;
			_delay_ms(4000);
		}
		PORTK = 0x00; //valves off
		Motor_Control('A', 6); //motor in agitate for 6 seconds (rinse)
		_delay_ms(4000);
		PORTK = 0x01; //drain valve on
		_delay_ms(1000);
		Motor_Control('S',8);
		PORTK = 0x00; //drain valve off
		PORTK = 0x04; //done
		while(!(PINA & 0x08)) //don't start if door is open
		{
		}
		
	}
}


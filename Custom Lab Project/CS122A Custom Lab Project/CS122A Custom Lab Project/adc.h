
#define F_CPU 8000000UL
#include <util/delay.h>
#define power 4

unsigned char presSens = 0;
unsigned char muxselect = 0;
unsigned int magCalc = 0;
unsigned char magTL = 0 , magTR =0, magBL=0, magBR=0;
unsigned char magX = 0;
unsigned char magY = 0;

void ADC_ON()
{
	ADMUX = muxselect;			// changes the adc input, adc select 
	ADCSRA = (1 << ADEN) | (1 << ADSC); // turns on converter, starts conversion
}

void ADC_SELECT(unsigned char select) // selects the adc input pin
{
	if(select < 8) { muxselect = select; ADC_OFF(); ADMUX = muxselect; ADC_ON();}
}

void ADC_OFF()
{
	ADCSRA = ~(1 << ADEN) | ~(1 << ADSC);
}

unsigned char ADC_SEND()
{
	return (char)(ADC/68);
}

unsigned char magCheck()
{
	if((!magTL && !magTR) || (!magBL && !magBR) || (!magTL && !magBL) || (!magTR && !magBR))
		return 0;
	else return 1;
}

void cal()
{
	if(!magCheck)
	{
	}
	else{
	magX = magTL; // temporary
	}
}


#ifndef PRESSENS_H
#define PRESSENS_H

enum PRESSENS{presStart, presSample, presOff} pressense_state;

int PRESSENSE_task(int state)
{
	switch (state)
	{
		case presStart:
			state = presSample;
			ADC_ON();
			break;
		
		case presOff:
			state = presOff;
			break;
		
		case presSample:
			state = presSample;
			break;
			
		default:
			state = presStart;
			break;
	}
	switch (state)
	{
		case presStart:
			break;
		
		case presOff:
			ADC_OFF();
			break;
		
		case presSample:
			ADC_SELECT(0);
			_delay_ms(1);
			presSens = 15 - ADC_SEND();
			break;
		
		default:
			break;
	}
	return state;
}

#endif /* PRESSENS_H */

#ifndef MAGSENS_H
#define MAGSENS_H

enum magSense {magStart, magRead, magOff} magSense_state;

int magSense_task(int state)
{
	switch(state)
	{
		case magStart:
			state = magRead;
			break;
		
		case magRead:
			state = magRead;
			ADC_SELECT(1);
			_delay_ms(1);
			magTL = 15 - ADC_SEND();
			ADC_SELECT(2);
			_delay_ms(1);
			magBL = 15 - ADC_SEND();
			_delay_ms(1);
			ADC_SELECT(4);
			magTR = 15 - ADC_SEND();
			_delay_ms(1);
			ADC_SELECT(3);
			_delay_ms(1);
			magBR = 15 - ADC_SEND();
			break;
		
		case magOff:
			state = magOff;
			break;
		
		default:
			state = magStart;
			break;
	}
	switch(state)
	{
		case magStart:
			break;
		
		case magRead:
			magCalc = magY | (magX << 8);
			break;
		
		case magOff:
			state = magOff;
			break;
		
		default:
			state = magStart;
			break;
	}
	return state;
}

#endif /* MAGSENS_H */
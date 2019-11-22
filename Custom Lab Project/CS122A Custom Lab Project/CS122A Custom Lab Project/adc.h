
#define F_CPU 8000000UL
#include <util/delay.h>
#define power 4

unsigned char presSens = 0;
unsigned char muxselect = 0;
unsigned int magCalc = 0;
unsigned char magTL = 0 , magTR =0, magBL=0, magBR=0;
unsigned char magX = 0;
unsigned char magY = 0;

char up = 0, down = 0, speed = 0;

void ADC_ON()
{
	ADMUX = muxselect;			// changes the adc input, adc select 
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << 6) | (3); // turns on converter, starts conversion
}

void ADC_SELECT(unsigned char select) // selects the adc input pin
{
	if(select < 8) { muxselect = select; //ADC_OFF();
		 ADMUX = muxselect; }//ADC_ON();}
}

void ADC_OFF()
{
	while(!(ADCSRA & (1 << 4))); // http://extremeelectronics.co.in/avr-tutorials/using-adc-of-avr-microcontroller/
	ADCSRA = ~(1 << ADEN) | ~(1 << ADSC);
}

unsigned char ADC_SEND()
{
	ADCSRA |= (1 << ADSC);
	while(!(ADCSRA & (1 << ADIF)));
	ADCSRA &= ~(1 << ADSC);
	return (char)(ADC >> 2);
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
			presSens = 15 - (ADC_SEND() >> 4);
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
			magTL = (ADC_SEND() >> 4);
			ADC_SELECT(2);
			magBL = (ADC_SEND() >> 4);
			/*_delay_ms(1);
			ADC_SELECT(4);
			//magTR = ADC_SEND();
			_delay_ms(1);
			ADC_SELECT(3);
			_delay_ms(1);*/
			//magBR = ADC_SEND();
			if(up && !down)
			{
				if(magTL < 7 && magBL < 7) speed = 1;
				else if(magTL < 7) speed = 2;
				else speed = 0;
			}
			else if(down && !up)
			{
				if(magTL < 7 && magBL < 7) speed = 1;
				else if(magBL < 7) speed = 2;
				else speed = 0;
			}
			else if(!up && !down) {speed = 0;}
			else
			{
				if(magTL < 7 && magBL > 7)
				{
					speed = 1; up = 1;
				}
				else if(magTL > 7 && magBL < 7)
				{
					speed = 1; down = 1;
				}
				else
				{
					speed = 0;
				}
			}
			up = magBL < 7 ? 1 : 0;
			down = magTL < 7 ? 1 : 0;
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
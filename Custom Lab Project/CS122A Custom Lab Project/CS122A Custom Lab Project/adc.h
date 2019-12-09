
//#define F_CPU 8000000UL
//#include <util/delay.h>
#define power 4

unsigned char presSens = 0;
unsigned char muxselect = 0;
unsigned char compass1 = 0, compass2 = 0, direction = 0;

#define l (PINA & 0x08)
#define r (PINA & 0x10)

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

// { right, up-right, up, up-left, left, bottom-left, bottom, bottom-right }

int magSense_task(int state)
{
	static unsigned char TL;
	static unsigned char TR;
	static unsigned char BL;
	static unsigned char BR;
	switch(state)
	{
		case magStart:
			TL = TR = BL = BR = 0;
			state = magRead;
			break;
		
		case magRead:
			state = magRead;
			
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
			TL = (~PINB & 0x02) ? 0x0a : 0;
			TR = (~PINB & 0x04) ? 0x09 : 0;
			BL = (~PINB & 0x08) ? 0x06 : 0;
			BR = (~PINB & 0x10) ? 0x05 : 0;
			compass1 = compass2;
			compass2 = (TL ) | (TR) | (BL) | (BR);
			if(compass2 != 0 && compass2 != compass1 && compass1 != 0)
			{
				if(compass1 & 0x08 && compass2 & 0x08) {
					compass2 &= ~(1 << 0x08);
				}
				if(compass1 & 0x04 && compass2 & 0x04) {
					compass2 &= ~(1 << 0x04);
				}
				if(compass1 & 0x02 && compass2 & 0x02) {
					compass2 &= ~(1 << 0x02);
				}
				if(compass1 & 0x01 && compass2 & 0x01) {
					compass2 &= ~(1 << 0x01);
				}
				direction = compass2;
			}
			else
				direction = 0;
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
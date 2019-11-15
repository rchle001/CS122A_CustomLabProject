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
			break;
		
		case magOff:
			state = magOff;
			break;
		
		default:
			state = magStart;
			break;
	}
}

#endif
#ifndef  BUTTONS_H
#define BUTTONS_H

#define button1 (~PINB & (1 << 5))
#define button2 (~PINB & (1 << 6))

enum B1 {B1_start, B1_sample, B1_wait} B1_states;
enum B2 {B2_start, B2_sample, B2_wait} B2_states;
	
unsigned char buttons = 0;
	
int B1_task(int state)
{
	switch(state)
	{
		case B1_start:
			state = B1_sample;
			break;
			
		case B1_sample:
			if(button1)
				state = B1_wait;
			else state = B1_sample;
			break;
			
		case B1_wait:
			if(!button1)
				state = B1_sample;
			else
				state = B1_wait;
			break;
		
		default:
			state = B1_start;
			break;
	}
	switch(state)
	{
		case B1_start:
			break;
		
		case B1_sample:
			buttons &= ~(1);
			break;
		
		case B1_wait:
			buttons |= 1;
			break;
		
		default:
		
			break;
	}
	return state;
}

int B2_task(int state)
{
	switch(state)
	{
		case B2_start:
			state = B2_sample;
			break;
		
		case B2_sample:
			if(button2)
				state = B2_wait;
			else
				state = B2_sample;
			break;
		
		case B2_wait:
			if(!button2)
				state = B2_sample;
			else
				state = B2_wait;
			break;
		
		default:
			state = B2_start;
			break;
	}
	switch(state)
	{
		case B2_start:
			break;
		
		case B2_sample:
			buttons &= ~(1 << 1);
			break;
		
		case B2_wait:
			buttons |= (1 << 1);
			break;
		
		default:
		
			break;
	}
	return state;
}
	

#endif
/*
 * CS122A Custom Lab Project.c
 *
 * Created: 11/7/2019 3:48:27 PM
 * Author : Raymond Chlebeck
 */ 

#include <avr/io.h>

#include "adc.h"
#include "scheduler.h"
#include "buttons.h"
#include "usart_ATmega1284.h"


enum TASKS{tasks_start, tasks_send, tasks_sleep} task_state;
	
int tasks_task(int state)
{
	static unsigned char tk; // counts to 5 seconds
	switch(state)
	{
		case tasks_start:			// initializes all ports
			DDRA = 0x00; PORTA = 0xff;
			DDRB = 0x00; PORTB = 0xff;
			DDRC = 0x00; PORTC = 0xff;
			DDRD = 0xff; PORTD = 0x00;
			tk = 50;
			initUSART(0);
			state = tasks_send;
			break;
		case tasks_send:
			if(tk == 0)
				state = tasks_sleep;
			else
				state = tasks_send;
			break;
		case tasks_sleep:
			break;
		default:
			state = tasks_start;
			break;
	}
	switch(state)
	{
		case tasks_start:			// initializes all ports
			/*DDRA = 0x00; PORTA = 0xff;
			DDRB = 0xff; PORTB = 0x00;
			DDRC = 0x00; PORTC = 0xff;
			DDRD = 0xff; PORTD = 0x00;*/
			state = tasks_send;
			break;
		case tasks_send:
			//PORTB = presSens | buttons | direction1 | (speed << 2); // temporary
			//PORTB = magTL;
			/*if(ADC == 0 && presSens == 0 && buttons == 0)
				tk--;*/
			if(USART_IsSendReady(0))
			{
				unsigned char send = (buttons << 2) | (presSens >> 2) | ((direction & 0x0f) << 4);
				USART_Send(send,0);
			}
			break;
		case tasks_sleep:
			//sleep();
			break;
		default:
			state = tasks_start;
			break;
	}
	
	return state;
}


int main(void)
{
    /* Replace with your application code */
	unsigned char contTime = 400;
	
	task  controller;
	task  Pressure;
	task Poll1;
	task Poll2;
	task Mag;
	
	controller.state = tasks_start;
	controller.elapsedTime = contTime;
	controller.period = contTime;
	controller.TickFct = &tasks_task;
	
	Pressure.state = presStart;
	Pressure.TickFct = &PRESSENSE_task;
	Pressure.elapsedTime = contTime/2;
	Pressure.period = contTime/2;
	tasksPeriodGCD = contTime;
	
	Poll1.state = B1_start;
	Poll1.elapsedTime = contTime/2;
	Poll1.period = contTime/2;
	Poll1.TickFct = &B1_task;
	
	Poll2.state = B2_start;
	Poll2.elapsedTime = contTime/2;
	Poll2.period = contTime/2;
	Poll2.TickFct = &B2_task;
	
	Mag.state = magStart;
	Mag.elapsedTime = contTime/2;
	Mag.period = contTime/2;
	Mag.TickFct = &magSense_task;
	
	/*DDRA = 0x00; PORTA = 0xff;
	DDRB = 0xff; PORTB = 0x00;
	DDRC = 0xff; PORTC = 0x00;
	DDRD = 0xff; PORTD = 0x00;
	*/
	TimerSet(contTime/2);
	TimerOn();
	
	
	task temp[] = {controller, Pressure, Poll1, Poll2, Mag};
	tasks = &temp;
	tasksNum = 5;
	//task * temp[] = {Pressure};
		
	//ADC_ON();
    while (1) 
    {
		//ADC_ON();
		//PORTB = ADC_SEND();
		//ADC_SELECT(selector);
		//selector++;
		//PORTB = presSens;
    }
}


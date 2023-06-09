/*
 * systic.c
 *
 *  Created on: Apr 1, 2023
 *      Author: Ezrah Buki
 *
 */
#include "stm32f4xx.h"

#define   SYSTIC_LOAD_VAL         16000
#define   CTRL_ENABLE             (1U<<0)
#define   CTRL_CLKSRC             (1U<<2)
#define   CTRL_COUNTFLAG          (1U<<16)
#define   ONE_SEC_LOAD             16000000

#define   CTRL_TICKINT            (1U<<1)

void systicDelayms(int delay)
{

	/*Reload with number of clocks per millisecond*/
	SysTick->LOAD = SYSTIC_LOAD_VAL;
	/*Clear systick current value register*/
	SysTick->VAL = 0;
	/*Enable systic and select internal clk src*/
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	for(int i=0; i<delay; i++)
	{
		/*wait until the COUNTFLAG id set*/
		while((SysTick->CTRL & CTRL_COUNTFLAG) == 0){}
	}

	SysTick->CTRL = 0 ;

}

void systick_1hz_interrupt(void)
{
	SysTick->LOAD = ONE_SEC_LOAD-1;
	SysTick->VAL = 0;

	/*Enable systic and select internal clk src*/
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;
	/*Enable systick interrupt*/
	SysTick->CTRL |= CTRL_TICKINT;


}










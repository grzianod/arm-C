#include "../translate.h"
#include "lpc17xx.h"
#include "../led/led.h"
	
void EINT0_IRQHandler (void)	  
{
  LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  
{
	NVIC_DisableIRQ(EINT2_IRQn);
	NVIC_DisableIRQ(EINT0_IRQn);
	LPC_GPIO2->FIOCLR    = 0x000000FF;  //all LEDs off
	start = 1;
	compute_table();
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
	NVIC_EnableIRQ(EINT2_IRQn);
	NVIC_EnableIRQ(EINT0_IRQn);
}

void EINT2_IRQHandler (void)	  
{
	volatile int res;
	if(!start) {
		LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */   
		return;
	}
	NVIC_DisableIRQ(EINT1_IRQn);
	NVIC_DisableIRQ(EINT0_IRQn);
	
	res = translate(_message, INPUT_LENGTH, _output, OUTPUT_LENGTH, '2','3','4');
	
  LPC_SC->EXTINT &= (1 << 2);
	NVIC_EnableIRQ(EINT1_IRQn);
	NVIC_EnableIRQ(EINT0_IRQn);	
	return;
}



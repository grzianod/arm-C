/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../led/led.h"
#include "../translate.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void RIT_IRQHandler (void)
{			
	static int down1=0;	
	static int down2=0;	
	volatile int res;
	down1++;
	if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
		reset_RIT();
		switch(down1){
			case 1:
				
						LPC_GPIO2->FIOCLR    = 0x000000FF;  //all LEDs off
						start = 1;
						compute_table();
			
				break;
			default:
				break;
		}
	}
	else {	/* button released */
		down1=0;			
		disable_RIT();
		reset_RIT();
		NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
	}
	
	down2++;
	if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){
		reset_RIT();
		switch(down2){
			case 1:
				
							res = translate(_message, INPUT_LENGTH, _output, OUTPUT_LENGTH, '2', '3', '4');
			
				break;
			default:
				break;
		}
	}
	else {	/* button released */
		down2=0;			
		disable_RIT();
		reset_RIT();
		NVIC_EnableIRQ(EINT2_IRQn);							 /* disable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
	}
		
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/

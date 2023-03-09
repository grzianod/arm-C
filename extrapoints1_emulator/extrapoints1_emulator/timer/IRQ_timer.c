/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 

extern void updateStatus(void);
extern void changeSelection(void);
extern void doSelection(void);
extern uint8_t eating;
extern void legend(void);


/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER0_IRQHandler (void)
{
	updateStatus();
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	//life timer saturated -> closing the current game
	legend();
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER2_IRQHandler (void)
{
	static uint8_t selected=0, left=0, right=0;
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0) {
			selected++;
			switch(selected) {
				case 1: doSelection();
								break;
				default:break;
			}
	}
	else selected=0;
	
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0) {
			left++;
			switch(left) {
				case 1: changeSelection();
								break;
				default:break;
			}
	}
	else left=0;
	
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0) {
			right++;
			switch(right) {
				case 1: changeSelection();
								break;
				default:break;
			}
	}
	else right=0;
	
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/

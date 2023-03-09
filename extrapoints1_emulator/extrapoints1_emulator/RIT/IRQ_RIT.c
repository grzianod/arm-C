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

extern void doSelection(void);
extern void changeSelection(void);

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
		static int select = 0;
		static int left = 0;
		static int right = 0;
	
		/*Joystick select pressed*/
		if((LPC_GPIO1 -> FIOPIN & (1<<25)) == 0) {
			select++;
			switch(select) {
				case 1:	doSelection();
								break;
				default: break;
			}
		}
		else select = 0;
		
		/*Joystick left */
		if((LPC_GPIO1 -> FIOPIN & (1<<27)) == 0) {
			left++;
			switch(left) {
				case 1:	changeSelection();
								break;
				default: break;
			}
		}
		else left = 0;
		
		/*Joystick right */
		if((LPC_GPIO1 -> FIOPIN & (1<<28)) == 0) {
			right++;
			switch(right) {
				case 1:	changeSelection();
								break;
				default: break;
			}
		}
		else right = 0;
}

/******************************************************************************
**                            End Of File
******************************************************************************/

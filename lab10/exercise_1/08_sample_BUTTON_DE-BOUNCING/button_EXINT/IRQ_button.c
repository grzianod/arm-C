#include "button.h"
#include "lpc17xx.h"


//	#include "../led/led.h" 					/* do not needed anymore, make your project clean */
#include "../RIT/RIT.h"		  			/* you now need RIT library 			 */

void EINT0_IRQHandler (void)	  	/* INT0														 */
{		
	
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1					*/
{
	NVIC_DisableIRQ(EINT2_IRQn);
	NVIC_DisableIRQ(EINT0_IRQn);
	
	enable_RIT();										/* enable RIT to count 50ms				 */
	NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
	NVIC_EnableIRQ(EINT2_IRQn);
	NVIC_EnableIRQ(EINT0_IRQn);
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	volatile int res;
	NVIC_DisableIRQ(EINT1_IRQn);
	NVIC_DisableIRQ(EINT0_IRQn);
	
	enable_RIT();										/* enable RIT to count 50ms				 */
	NVIC_DisableIRQ(EINT2_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 20);     /* GPIO pin selection */
	
	LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
	NVIC_EnableIRQ(EINT1_IRQn);
	NVIC_EnableIRQ(EINT0_IRQn);
  
}



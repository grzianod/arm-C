/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "tamagotchi.h" 

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


int main(void)
{
	/*Initialization step */
  SystemInit();  												/* System Initialization (i.e., PLL)  */
  LCD_Initialization();
	init_timer(0, 0x17D7840, 0x0, 0x0, 0x0); 						/* updating alive animations/information: 1s * 25MHz = 0x17D7840 */
	init_timer(1, 0xFFFFFFFF, 0x0, 0x0, 0x0);						/* life timer */
	init_timer(2, 0x1312D0, 0x0, 0x0, 0x0);							/* polling joystick timer: 50 ms * 25MHz = 0x1312D0 */
	joystick_init();
	
	initGame();
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
  while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

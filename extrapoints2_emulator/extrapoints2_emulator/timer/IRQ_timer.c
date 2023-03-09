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
#include "../TouchPanel/TouchPanel.h"

extern void updateStatus(void);
extern void changeSelection(void);
extern void doSelection(void);
extern uint8_t eating;
extern void legend(void);
extern void touchAnimation(void);
extern void changeVolume(void);
extern uint32_t age;
extern uint8_t sound;
extern uint8_t state;
uint8_t clickSound = 0;

const int eatingNotes[3] = {2120, 1684, 1417 };
const int cuddleNotes[12] = {1684, 1417, 1263, 1684, 1417, 1194, 1263, 1684, 1417, 1263, 1417, 1684};
const int runNotes[5] = {1062, 1125, 1263, 1417, 1592};

uint16_t SinTable[45] =                                       /* ÕýÏÒ±í                       */
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};

const int freqs[8]={2120,1890,1684,1592,1417,1263,1125,1062};
/*
262Hz	k=2120		c4
294Hz	k=1890		d4
330Hz	k=1684		e4
349Hz	k=1592		f4
392Hz	k=1417		g4
440Hz	k=1263		a4
494Hz	k=1125		b4
523Hz	k=1062		c5

*/

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
	age++;
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
	static int i=0;
	disable_timer(3);
	reset_timer(3);
	if(sound == SILENT) {
		LPC_TIM1 -> IR = 1;
		return;
	}
	if(state == EATING) {
		init_timer(3, eatingNotes[(i++)%3], 0x0, 0x0, 0x0);
		enable_timer(3);
	}
	if(state == CUDDLING) {
		init_timer(3, cuddleNotes[(i++)%12], 0x0, 0x0, 0x0);
		enable_timer(3);
	}
	if(state == END) {
		init_timer(3, runNotes[(i++)%5], 0x0, 0x0, 0x0);
		enable_timer(3);
	}
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER2_IRQHandler (void)
{
	static uint8_t selected=0, left=0, right=0;
	
	if(getDisplayPoint(&display, Read_Ads7846(), &matrix )){
			if(display.x > 70 && display.x < 170 && display.y > 130 && display.y < 230){
				touchAnimation();
			}
			if(display.x > 15 && display.x < 35 && display.y > 15 && display.y < 35) {
				changeVolume();
			}
		}
	
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


void TIMER3_IRQHandler (void)
{	
		static int ticks=0;
		/* DAC management */	
		LPC_DAC->DACR = (SinTable[ticks]<<6)/2;
		ticks++;
		if(ticks==45) ticks=0;
		LPC_TIM3->IR = 1;			/* clear interrupt flag */
		return;
	}
	
/******************************************************************************
**                            End Of File
******************************************************************************/

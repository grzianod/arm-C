#include "animation.h"
#include <string.h>
#include "kirby1.c"
#include "kirby2.c"
#include "eating.c"
#include "snack.c"
#include "meal.c"
#include "end.c"
#include "volume.c"
#include "legend.c"
#include "mute.c"
#include "heart.c"
#include "sing1.c"
#include "sing2.c"

typedef struct {
	unsigned long int hours;
	unsigned char minutes;
	unsigned char seconds; 
} time;

selection selected;
status state;
volume sound;
uint8_t last;
extern uint8_t satiety;
extern uint8_t happiness;
extern uint32_t age;

extern void enable_timer(uint8_t timer_num);

void drawFigure(uint8_t num) {
	(num == 0) ? GUI_DrawBitmap(70, 130, 100,100, KIRBY1) : GUI_DrawBitmap(70, 130, 100,100, KIRBY2);
}

void deleteFigure(unsigned char x, unsigned char y) {
	int i,j;
	for(i=0; i<100;i++)
		for(j=0; j<100; j++)
			LCD_SetPoint(x+i, y+j, White);
}

void drawButtons() {
	LCD_DrawRectangle(5, 260, 110, 55, Blue);
	selected = MEAL;
	LCD_DrawRectangle( 7, 262, 106, 51, White);
	LCD_DrawRectangle(125, 260, 106, 51, White);
	GUI_Text(42, 277, "MEAL", Blue, White);
	GUI_Text(158, 277, "SNACK", Black, White);
}

void mainScreen() {
	LCD_Clear(White);
	last = 0;
	drawFigure(last);
	drawButtons();
}

void changeAnimation() {
	if(state == EATING || state == CUDDLING) return;
	last = (last == 0) ? 1 : 0;
	drawFigure(last);
}

char* toString(uint8_t num) {
		static char str[4];
		sprintf(str, "%3d %c", num, 37);
		return str;
}

time getAge(uint32_t age) {
		time t;
		t.hours = (unsigned long int)(age/3600);
		t.minutes = (unsigned char)(age - t.hours*3600)/60;
		t.seconds = (unsigned char)(age - t.hours*3600 -t.minutes*60);
		return t;
}

char* toTimeString(time t) {
	static char str_time[8]; 
		sprintf(str_time, "%02lu:%02u:%02u", t.hours, t.minutes, t.seconds);
		return str_time;
}

void updateAge() {
	time t = getAge(age);
	GUI_Text(105,16, (uint8_t *)toTimeString(t), Black, White);
	GUI_Text(65,16, "Age: ", Black, White);
}

void updateInformation(uint8_t satiety, uint8_t happiness, uint8_t age) {
	updateAge();
	(sound == SILENT) ? GUI_DrawBitmap(15, 15, 20,20, MUTE) : GUI_DrawBitmap(15, 15, 20,20, VOLUME);
	GUI_Text(30, 48, "Happiness: ", Black, White);
	GUI_Text(50, 64, (uint8_t *)toString(happiness), Black, White);
	GUI_Text(145, 48, "Satiety: ", Black, White);
	GUI_Text(157, 64, (uint8_t *)toString(satiety), Black, White);
	
}

void initAnimation() {
	mainScreen();
}

void runAway(void) {
	LCD_Clear(White);
	
	GUI_DrawBitmap(70, 130, 100, 100, ENDIMAGE);
	
	GUI_Text(87, 64, "YOU LOSE!", Black, White);
	updateAge();
	LCD_DrawRectangle(5, 260, 230, 55, Red);
	LCD_DrawRectangle( 7, 262, 226, 51, White);
	GUI_Text(93, 277, "RESTART", Red, White);
}

void changeSelection(void) {
	if(state != ALIVE) return;
	if(selected == MEAL) {
		LCD_DrawRectangle(5, 260, 110, 55, White);
		selected = SNACK;
		LCD_DrawRectangle(123, 258, 110, 55, Green);
		LCD_DrawRectangle( 7, 262, 106, 51, White);
		LCD_DrawRectangle(125, 260, 106, 51, White);
		GUI_Text(42, 277, "MEAL", Black, White);
		GUI_Text(158, 277, "SNACK", Green, White);
	}
	else {
		LCD_DrawRectangle(123, 258, 110, 55, White);
		selected = MEAL;
		LCD_DrawRectangle(5, 260, 110, 55, Blue);
		LCD_DrawRectangle( 7, 262, 106, 51, White);
		LCD_DrawRectangle(125, 260, 106, 51, White);
		GUI_Text(42, 277, "MEAL", Blue, White);
		GUI_Text(158, 277, "SNACK", Black, White);
	}
}

void drawFood(selection selected) {
	(selected == MEAL) ? GUI_DrawBitmap(32, 180, 30, 30, MEALIMAGE) : GUI_DrawBitmap(32, 180, 30, 30, SNACKIMAGE);
}

void deleteFood(selection selected) {
	int i,j;
	for(i=0; i<30; i++)
		for(j=0; j<30; j++) 
			LCD_SetPoint(32+i, 160+j, White);
}

void drawEating(unsigned int x, unsigned int y) {
	GUI_DrawBitmap(x,y, 100, 100, EATINGIMAGE);
}

void deleteEating(unsigned int x, unsigned int y) {
	int i,j;
	for(i=0; i<100; i++)
		for(j=0; j<100; j++) 
			LCD_SetPoint(x+i, y+j, White);
}

void eatingAnimation() {
	int i,j;
	LCD_Clear(White);
	updateInformation(satiety, happiness, get_timer_count(1));
	
	drawFood(selected);
	for(j=0,i=276; i>=12; j++, i-=8) {
		deleteEating(i+8, 130);
		if(state == END) return;
		drawEating(i, 130);
	}
	if(state == END) return;
	LCD_Clear(White);
	drawFigure(last);
	drawButtons();
	updateInformation(satiety, happiness, get_timer_count(1));
}

void cuddling(void) {
	int i;
	LCD_Clear(White);
	updateInformation(satiety, happiness, get_timer_count(1));
	
	GUI_DrawBitmap(155, 110, 20, 20, HEART);
	
	
	for(i=0; i<150; i++) {
		if(state == END) return;
		if(i%7 == 0) {
			LCD_DrawRectangle(40,100,20,20,White);
			LCD_DrawRectangle(25,150,20,20,White);
			GUI_DrawBitmap(70, 130, 100, 100, SING1);
			GUI_DrawBitmap(155, 110, 20, 20, HEART);
		}
		if(i%13 == 0) {
			LCD_DrawRectangle(155,110,20,20,White);
			GUI_DrawBitmap(70, 130, 100, 100, SING2);
			GUI_DrawBitmap(40, 100, 20, 20, HEART);
			GUI_DrawBitmap(25, 150, 20, 20, HEART);
		}
	}
	if(state == END) return;
	
	LCD_Clear(White);
	drawFigure(last);
	drawButtons();
	updateInformation(satiety, happiness, get_timer_count(1));
}

void changeVolume(void) {
	if(sound == SILENT) {
		sound = LOUD;
		GUI_DrawBitmap(15,15,20,20, VOLUME);
	}	
	else {
		sound = SILENT;
		GUI_DrawBitmap(15,15,20,20, MUTE);
	}
}



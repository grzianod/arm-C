#include "tamagotchi.h"
#define LOSING_SATIETY_PER_SECOND 1
#define LOSING_HAPPINESS_PER_SECOND 1

uint8_t satiety;
uint8_t happiness;
uint8_t age;
uint8_t eating;

extern void updateInformation(uint8_t satiety, uint8_t happiness, uint8_t age);
extern void runAway(void);
extern void displayLegend(void);
extern status state;
extern selection selected;

void initGame() {
	initAnimation();
	satiety = 100;
	happiness = 100;
	age = 0;
	state = ALIVE;
	reset_timer(0);
	reset_timer(1);
	enable_timer(0);
	enable_timer(1);
	enable_timer(2);
	updateInformation(satiety, happiness, get_timer_count(1));
}

void updateStatus() {
	satiety-= LOSING_SATIETY_PER_SECOND;
	happiness-= LOSING_HAPPINESS_PER_SECOND;
	
	if(satiety > 100 || happiness > 100) {
		dead();
		return;
	}
	updateInformation(satiety, happiness, get_timer_count(1));
	changeAnimation();
}

void dead() {
	state = END;
	disable_timer(1);
	disable_timer(0);
	runAway();
}

void doSelection(void) {
	if(state == ALIVE) {
			state = EATING;
			if(selected == MEAL) satiety+=LOSING_SATIETY_PER_SECOND;
		  else happiness+=LOSING_HAPPINESS_PER_SECOND;
			if(satiety > 100) satiety = 100;
			if(happiness > 100) happiness = 100;
			eatingAnimation();
			if(state == END) dead();
			else state = ALIVE;
			return;
	}
	initGame();
	return;
}

void legend(void) {
	displayLegend();
}

#include "GLCD/GLCD.h" 
#include "joystick/joystick.h"
#include "timer/timer.h"

typedef enum {MEAL, SNACK} selection;
typedef enum {ALIVE, END, EATING} status;

void initGame(void);
void changeAnimation(void);
void updateInformation(uint8_t satiety, uint8_t happiness, uint8_t age);
void welcome(void);
void mainScreen(void);
void runAway(void);
void changeSelection(void);
void eatingAnimation(void);
void displayLegend(void);

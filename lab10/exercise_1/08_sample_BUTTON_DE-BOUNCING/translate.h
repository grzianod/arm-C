#include <math.h>

extern int translate(	char*, int, char*, int, char, char, char);

const int INPUT_LENGTH =45;
const int OUTPUT_LENGTH =13;

//_message = "CIAO MONDO 38"
char _message[INPUT_LENGTH] = {'1','0','1','0','2','0','0','2','0','1','2','1','1','1','3','1','1','2','1','1','1','2','1','0','2','1','0','0','2','1','1','1','3','0','0','0','1','1','2','1','1','1','0','0','4' };
char _output[OUTPUT_LENGTH];
int start = 0;
	
void compute_table(void);


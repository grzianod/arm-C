#include <math.h>
extern int check_square(int*, int*, int);
extern float my_division(float*, float*);
extern int _Matrix_Coordinates[11][22];
extern char _ROWS;
extern char _COLUMNS;

typedef enum {FALSE, TRUE} boolean;

int main(void){
		char i,j;
		float	r=3.0;
		volatile float pi_greco;
		volatile boolean result;
		float area=0.0;
		for(i=0;i<_ROWS; i++) {
			for(j=0; j<_COLUMNS; j+=2) {
				result = check_square(&(_Matrix_Coordinates[i][j]),&(_Matrix_Coordinates[i][j+1]),r);
				if(result == TRUE)
					area+=result;
			}
		}
		r=pow(r,2);
		pi_greco = my_division(&area, &r);
		while(1);
}


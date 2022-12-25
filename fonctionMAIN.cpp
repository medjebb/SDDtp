#include <iostream>
#include "focntion2.h"
#include "tpPileMathexp.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(void)
{
	char opr;
	float val=Caracters_To_float(&opr);
	printf("\nle chiffre : %+f",val);	
	printf("\nl\'oprateur  : %c",opr);	
	
}

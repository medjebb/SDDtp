#include <iostream>
#include "focntion2.h"


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(void)
{
	float val;
	union U_char_float op1,op2,op3;
	op1.opperande=5;
	op2.opperateur='/';
	op3.opperande=2;
	 
	
	val=eval(op1,op2,op3);
	printf("\nla valeur est : %f",val);
	
	//float val=Caracters_To_float(&opr);
	//printf("\nle chiffre : %+f",val);	
	//printf("\nl\'oprateur  : %d",opr);
//	Empiler_expression();	
	
}

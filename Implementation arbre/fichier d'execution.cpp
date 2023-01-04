#include<stdio.h>
#include "fonction1.h"

int main(void)
{
	Noeud* arbre=NULL;
	printf("Entrer une expression arithmetique : ");
	arbre=convertir_exp_math_arbre();	
	printf("la valeur est egale a : %f",Evaluation_Arb_arith(arbre));
}

#include<stdio.h>
#include "fonction1.h"

int main(void)
{
	Noeud* arbre=NULL;
	arbre=convertir_exp_math_arbre();
	
	afficher_Arb_horizontal(arbre,-1);
}

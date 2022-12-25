#include "tpPileMathexp.h"
#include "malloc.h"
union U_char_float
{
	float opperande;
	char opperateur;
};

typedef struct Nd
{
	U_char_float champ_opp;
	struct Nd * svt; 
}Noeud;


Noeud* Creer_element_pile(U_char_float element)
{
	Noeud * NE=(Noeud*)malloc(sizeof(Noeud));
	if(!NE) exit(0);
	NE->champ_opp =element;
	NE->svt=NULL;
	
	return (Noeud*)NE;
}

Noeud *Empiler_element_pile(Noeud * pile,U_char_float element)
{
	Noeud *NE=Creer_element_pile(element);
	
	//Si la pile est vide 
	if(!pile) return (Noeud*)NE;
	
	NE->svt=pile;
	return (Noeud*)NE;	
} 


void Empiler_expression()
{
	Noeud * pile=NULL;
	float reel;
	char opperateur;
	U_char_float instance1;
	do{
		reel=Caracters_To_float(&opperateur);
		instance1.opperande=reel;
		Empiler_element_pile(pile,instance1);
		instance1.opperateur=opperateur;
		if(opperateur!='\n')
			Empiler_element_pile(pile,instance1);
		
		
	}while(opperateur!='\n');	
	
	
}

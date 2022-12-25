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
Noeud *Dempiler_element_pile(Noeud *pile)
{
	Noeud *ptr;
	ptr=pile;
	pile=pile->svt;
	free(ptr);
	return (Noeud*)pile;	
} 

Noeud *Empiler_expression()
{
	Noeud * pile=NULL;
	float reel;
	char opperateur;
	U_char_float instance1;
	do{
		reel=Caracters_To_float(&opperateur);
//		printf("le reel : %f\n",reel);
//		printf("l'opperateur ' : %c\n",opperateur);
		instance1.opperande=reel;
		pile=Empiler_element_pile(pile,instance1);
		instance1.opperateur=opperateur;
		if(opperateur!='\n')
			pile=Empiler_element_pile(pile,instance1);
		
		
	}while(opperateur!='\n');	
	
	return((Noeud*)pile);
}
 

float eval(U_char_float oprd1 , U_char_float opr , U_char_float oprd2)
{
	switch(opr.opperateur)
	{
		case '+': return(oprd1.opperande + oprd2.opperande);
		case '-': return(oprd1.opperande - oprd2.opperande);
		case '*': return(oprd1.opperande * oprd2.opperande);
		case '/': return(oprd1.opperande / oprd2.opperande);
	}	
}

/* opr1 -> dernier operateur
   opr2 -> operateur lu */
int priorite(char op1,char op2)
{

	if((op1 =='*') || (op1 == '/'))
	{
		if((op2 =='*') || (op2 == '/'))return((int)0);
		return((int)1);
	}
	return((int)0);

}


float calculer_exp_math_pile()
{
	Noeud *Pile_init,*Pile_opr,*Pile_eval;
	U_char_float operande;
	int val;
	
	//l'appel de la fonction Empiler_expression
	printf("entrer une expression : ");
	Pile_init=Empiler_expression();
	
	//le cas ou on a qu'un seul operande
	if(Pile_init->svt==NULL)return(Pile_init->champ_opp.opperande);
	
	for(int i=0;i<3;i++)
	{
		if(i==1)
		{
			Pile_opr=Empiler_element_pile(Pile_opr,Pile_init->champ_opp);
			Pile_init=Dempiler_element_pile(Pile_init);
			continue;
		}
		Pile_eval=Empiler_element_pile(Pile_eval,Pile_init->champ_opp);
		Pile_init=Dempiler_element_pile(Pile_init);
	}
	
	while(Pile_init)
	{
		if(priorite(Pile_opr->champ_opp.opperateur,Pile_init->champ_opp.opperateur) == 0)
		{
			//l'empilement de l'operateur
			Pile_opr=Empiler_element_pile(Pile_opr,Pile_init->champ_opp);
			Pile_init=Dempiler_element_pile(Pile_init);
			//l'empilement de l'operande
			Pile_eval=Empiler_element_pile(Pile_eval,Pile_init->champ_opp);
			Pile_init=Dempiler_element_pile(Pile_init);
			continue;
		}
		operande=Pile_eval->champ_opp;
		//depiler le 1er operande
		Pile_eval=Dempiler_element_pile(Pile_eval);
		//l'appel de la fonction eval
		val=eval(operande,Pile_opr->champ_opp,Pile_eval->champ_opp);
		//depiler le 2eme operande
		Pile_eval=Dempiler_element_pile(Pile_eval);
		//depiler le operateur
		Pile_opr=Dempiler_element_pile(Pile_opr);
		
		operande.opperande=val;
		//empiler le resultat dans la pile d'evaluation
		Pile_eval=Empiler_element_pile(Pile_eval,operande);
	}
	
	while(Pile_eval->svt)
	{
		operande=Pile_eval->champ_opp;
		//depiler le 1er operande
		Pile_eval=Dempiler_element_pile(Pile_eval);
		//l'appel de la fonction eval
		val=eval(operande,Pile_opr->champ_opp,Pile_eval->champ_opp);
		//depiler le 2eme operande
		Pile_eval=Dempiler_element_pile(Pile_eval);
		//depiler le operateur
		Pile_opr=Dempiler_element_pile(Pile_opr);
		
		operande.opperande=val;
		//empiler le resultat dans la pile d'evaluation
		Pile_eval=Empiler_element_pile(Pile_eval,operande);
		
	}
	return((float)Pile_eval->champ_opp.opperande);
}






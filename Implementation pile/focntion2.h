#include "tpPileMathexp.h"
#include "malloc.h"
#include <stdio.h>
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


int est_operateur(char car)
{
	return((car == '+') || (car == '-') || (car == '*') || (car == '/'));
}

int Est_numerique(char cara)
{
	//voir si comprit entre le code 0 et 9
	if(((int)'0'<=(int)cara) && ((int)cara<= (int)'9')) 
		return ((int)cara - (int)'0');
	if((int)cara==(int)'-') return -1;
	if((int)cara==(int)'+') return -2;

	return (int)-3;	
}


float Caracters_To_float(char *opr)
{
	float valeur1=0,valeur2=0,rang=.1;
	int unite,signe=1;
	char cara;
	
	
	//traitement de signe
	cara=getchar();
	unite=Est_numerique(cara);
	switch (unite)
		{
			//si le caractere est un -
			case -1: signe=-1;break;
			//si le caractere est un +
			case -2:signe=1;break;
			//si le caractere est quelque chose d'autre que le + et -
			case -3:
				printf("ERREUR 1 : expression mathematique est mal ecrite"); 
				exit(0);
			default:  valeur1=valeur1*10+unite;	
		}
	
	//boucler sur la premiere partie du reel qui est avant le '.'
	while( ( (cara=getchar()) != '.') && (cara != '\n')) 
	{
		unite=Est_numerique(cara);
		//le cas ou le caractere n'est un caractere numerique
		if(unite < 0)break;
		
		valeur1=valeur1*10+unite;
	}	
	
	
	//lecture des chiffres apres la virgule
	if(cara=='.')
	{
		while((cara=getchar())!=(int)'\n')
		{
			unite=Est_numerique(cara);
			//le cas ou le caractere n'est un caractere numerique
			if(unite < 0)break;
			valeur2+=unite*rang;
			rang/=10;
		}
	}
	
	
	if(unite < 0)
	{
		if(!est_operateur(cara))
		{
			printf("ERREUR 2 : expression mathematique est mal ecrite"); 
			exit(0);
		}
		*opr=cara;
	}
	
	if(cara == '\n')*opr=cara;

	// retourner la somme des deux parties du float
	return (float)(signe*(valeur1+valeur2));
}

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
Noeud *Depiler_element_pile(Noeud *pile)
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
	Noeud *Pile_init=NULL,*Pile_opr=NULL,*Pile_eval=NULL;
	U_char_float operande;
	float val;
	
	//l'appel de la fonction Empiler_expression
	printf("entrer une expression : ");
	Pile_init=Empiler_expression();

	//le cas ou on a qu'un seul operande
	if(Pile_init->svt==NULL)
		return (float)(Pile_init->champ_opp.opperande);
	
	//empiler le 1er operande dans la pile d'evaulation
	Pile_eval=Empiler_element_pile(Pile_eval,Pile_init->champ_opp);
	Pile_init=Depiler_element_pile(Pile_init);


	while(Pile_init)
	{

		//Si la pile d'operateur est vide , on continu a lire
		if(!Pile_opr)
		{
			//l'empilement de l'operateur
			Pile_opr=Empiler_element_pile(Pile_opr,Pile_init->champ_opp);
			Pile_init=Depiler_element_pile(Pile_init);
			//l'empilement de l'operande
			Pile_eval=Empiler_element_pile(Pile_eval,Pile_init->champ_opp);
			Pile_init=Depiler_element_pile(Pile_init);	
			continue;
		}
		//Si les deux opperateurs ont la meme priorite , on continu a lire
		if(priorite(Pile_opr->champ_opp.opperateur,
				Pile_init->champ_opp.opperateur) == 0)
		{
			//l'empilement de l'operateur
			Pile_opr=Empiler_element_pile(Pile_opr,Pile_init->champ_opp);
			Pile_init=Depiler_element_pile(Pile_init);
			//l'empilement de l'operande
			Pile_eval=Empiler_element_pile(Pile_eval,Pile_init->champ_opp);
			Pile_init=Depiler_element_pile(Pile_init);
			
		}
		//Si non on evalu le contenu de la pile d'evaluation
		else
		{
			operande=Pile_eval->champ_opp;
			//depiler l'operande a la tete de pile
			Pile_eval=Depiler_element_pile(Pile_eval);
			//l'appel de la fonction eval
			val=eval(operande,Pile_opr->champ_opp,Pile_eval->champ_opp);
			//depiler le 2eme operande
			Pile_eval=Depiler_element_pile(Pile_eval);
			//depiler l'operateur
			Pile_opr=Depiler_element_pile(Pile_opr);
			
			operande.opperande=val;
			//empiler le resultat dans la pile d'evaluation
			Pile_eval=Empiler_element_pile(Pile_eval,operande);
			
		}
	}
	
	// le cas ou on a que des operateurs de meme priorite
	while(Pile_eval->svt)
	{
		operande=Pile_eval->champ_opp;
		//depiler le 1er operande
		Pile_eval=Depiler_element_pile(Pile_eval);
		//l'appel de la fonction eval
		val=eval(operande,Pile_opr->champ_opp,Pile_eval->champ_opp);
		//depiler le 2eme operande
		Pile_eval=Depiler_element_pile(Pile_eval);
		//depiler l'operateur
		Pile_opr=Depiler_element_pile(Pile_opr);
		
		operande.opperande=val;
		//empiler le resultat dans la pile d'evaluation
		Pile_eval=Empiler_element_pile(Pile_eval,operande);
	}
	
	return((float)Pile_eval->champ_opp.opperande);
}
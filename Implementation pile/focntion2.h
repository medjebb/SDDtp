#include "malloc.h"
#include <stdio.h>
union U_char_float
{
	float opperande;//champ operande
	char opperateur;//champ operateur
};

typedef struct Nd
{
	U_char_float champ_opp;//champ contenant l'information
	struct Nd * svt; //Pointeur sur le prochain noeud
}Noeud;//Nom de la structure

/* 
Nom Fonction : est_operateur
Entree : un caractere 
Sortie : entier
Description : la fonction test si le caractere est 
	un opperateur mathematique
*/
int est_operateur(char car)
{
	return((car == '+') || (car == '-') || (car == '*') || (car == '/'));
}
/*________________________FIN_est_operateur_____________________________*/

/* 
Nom Fonction : Est_numerique
Entree : un caractere 
Sortie : entier
Description : la focntion test si le caractere est 
	un chiffre mathematique
*/
int Est_numerique(char cara)
{
	//voir si comprit entre le code 0 et 9
	if(((int)'0'<=(int)cara) && ((int)cara<= (int)'9')) 
		return ((int)cara - (int)'0');
	if((int)cara==(int)'-') return -1;
	if((int)cara==(int)'+') return -2;

	return (int)-3;	
}
/*________________________FIN_Est_numerique_____________________________*/


/* 
Nom Fonction : Caracters_To_float
Entree : un caractere un passage par addresse  
Sortie : reel
Description : la fonction transforme le contenu de buffer en un reel
	elle retourne aussi le dernier elemnt lu est qui n'est pas un chiffre
	ceci par le passage par adresse de la variable 'opr'
*/

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

/*________________________FIN_Caracters_To_float________________________*/


/* 
Nom Fonction : Creer_element_pile
Entree : un element de type U_char_float (union) qui est soit un opperateur
	soit un reel
Sortie : pointeur de type Noeud
Description : la fonction creer une instance de type Noeud et la remplie 
	avec l'union passe dans les parametres
*/

Noeud* Creer_element_pile(U_char_float element)
{
	Noeud * NE=(Noeud*)malloc(sizeof(Noeud));
	if(!NE) exit(0);
	NE->champ_opp =element;
	NE->svt=NULL;
	
	return (Noeud*)NE;
}
/*________________________FIN_Creer_element_pile________________________*/


/* 
Nom Fonction : Empiler_element_pile
Entree :
		-pointeur de type Noeud
		-un element de type U_char_float (union) qui est soit un opperateur
	soit un reel		 
Sortie : pointeur de type Noeud
Description : la fonction empile un element(soit opperateur sois reel) dans
la pile
*/
Noeud *Empiler_element_pile(Noeud * pile,U_char_float element)
{
	Noeud *NE=Creer_element_pile(element);
	
	//Si la pile est vide 
	if(!pile) return (Noeud*)NE;
	
	NE->svt=pile;
	return (Noeud*)NE;	
}

/*________________________FIN_Empiler_element_pile______________________*/


/* 
Nom Fonction : Depiler_element_pile
Entree :
		-pointeur de type Noeud		 
Sortie : pointeur de type Noeud
Description : la fonction depile la tete de la pile
*/
Noeud *Depiler_element_pile(Noeud *pile)
{
	Noeud *ptr;
	ptr=pile;
	pile=pile->svt;
	free(ptr);
	return (Noeud*)pile;	
} 
/*________________________FIN_Depiler_element_pile______________________*/


/* 
Nom Fonction : Empiler_expression
Entree : VOID	 
Sortie : pointeur de type Noeud
Description : la fonction va prendre le contenu du buffer et
le transformer en une pile d'elements
*/
Noeud *Empiler_expression()
{
	Noeud * pile=NULL;
	float reel;
	char opperateur;
	U_char_float instance1;

	do{
		//Lecture de l'operande et de l'opperateur
		reel=Caracters_To_float(&opperateur);
		instance1.opperande=reel;
		//Empiler l'operande dans la pile
		pile=Empiler_element_pile(pile,instance1);
		instance1.opperateur=opperateur;
		//Empiler l'opperateur a condition qu'il est pas un routeur chariot
		if(opperateur!='\n')
			pile=Empiler_element_pile(pile,instance1);
		
	//Refaire tant que l'opperateur lu n'est pas un '\n'
	}while(opperateur!='\n');
	
	return((Noeud*)pile);
}
/*________________________FIN_Empiler_expression________________________*/


/* 
Nom Fonction :eval
Entree : trois elements de type U_char_float 
Sortie : reel
Description : la fonction prends deux opperandes et un opperateur et rends
un reel qui est l'evaluation de cette opperation
*/
float eval(U_char_float oprd1 , U_char_float opr , U_char_float oprd2)
{
	switch(opr.opperateur)
	{
		case '+': return(oprd1.opperande + oprd2.opperande);
		case '-': return(oprd1.opperande - oprd2.opperande);
		case '*': return(oprd1.opperande * oprd2.opperande);
		case '/': if(oprd2.opperande==0)
					{
						printf("\n\nOn ne peut pas divider par 0\n\n");
						exit(0);
					}
					return(oprd1.opperande / oprd2.opperande);
	}	
}
/*_______________________________FIN_eval_______________________________*/


/* 
Nom Fonction :priorite
Entree : deux elements de type caracteres 
Sortie : entier
Description : donne la priorite entre les opperandes
*/
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
/*____________________________FIN_priorite______________________________*/



/* 
Nom Fonction :   calculer_exp_math_pile
Entree : VOID
Sortie : reel
Description : la focntion evalue une expression mathematique saisi sur 
le clavier et la stocke dans des piles pour apres l'evaluer
*/
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

/*______________________FIN_calculer_exp_math_pile______________________*/
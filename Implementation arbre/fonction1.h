union U_char_float
{
	float opperande;
	char opperateur;
};

typedef struct Nd
{
	U_char_float champ_opp;
	struct Nd* fgche;//pointeur sur le fils gauche
	struct Nd* fdt;//pointeur sur le fils droit
}Noeud;

/********************************Creer_Noeud************************/
/*
	Ent�e: U_char_float b val : la valeur a mettre dans le nouvel element
	Sorties: le nouvel element allou�
	la fonction prends la valeur et fait une allocation memoire, 
	et initialise cette nouvel element avec val
*/
Noeud * Creer_Noeud(U_char_float val)
{
	Noeud *arb;
	
	//allocation memoire du nouvel element
	arb=(Noeud*)malloc(sizeof(Noeud));
	
	//Test si l'allocation est bien faite
	if(!arb)
	{
		printf("\nErreur d'allocation");
		exit(0);
	}
	/*Initialisation Noeud*/
	arb->champ_opp=val;
	arb->fgche=NULL;
	arb->fdt=NULL;
	
	return (Noeud*) arb;
}

/*******************************************************************/


/**********************afficher_Arb_horizontal***************************/

/*
	Entr�es:
			Noeud * arb: pointeur sur la racine de l'arbre.
			int niveau : variable permettant de renseigner sur le 
			niveau de l'element courant.
	Sorties:
			int : entier permet de renseigner sur l'etat de la focntion
			
La focntion permet d'afficher l'arbre horizontalement ceci en parcourant 
la pratie droite de l'arbre et en l'affichant puis afficher la partie 
gauche
*/
int afficher_Arb_horizontal(Noeud * arb,int niveau)
{
	int rst;
	//Test si l'element courant est NULL
	if(!arb)
		return (int)0;
	//afficher le sous arbre droit 
	rst=afficher_Arb_horizontal(arb->fdt,++niveau);
	//ajouter auttant de tabulation que le niveau de l'element courant
	for(int i=0;i<niveau;i++)printf("\t");
	//afficher l'elemnt courant et retourner a la ligne
	if((!arb->fgche)&&(!arb->fdt))
		printf("%f\n",arb->champ_opp.opperande);
	else
		printf("%c\n",arb->champ_opp.opperateur);
	//afficher le sous arbre gauche
	rst=afficher_Arb_horizontal(arb->fgche,niveau);
	
	return (int)1;	
}
/*******************************************************************/




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


Noeud* rendre_ancetre(Noeud* arbre,Noeud *element_courant[1] 
								,char opperateur)
{
	Noeud *ptr,*ptr_Svt,*NE;
	union U_char_float T;
	T.opperateur=opperateur;
	NE=Creer_Noeud(T);
	
	//si la racine est de meme ou plus prioritaire que l'opperateur lu
	if(priorite(arbre->champ_opp->opperateur,opperateur) == 0)
	{
		NE->fgche=arbre;
		NE->fdt=NULL;
		element_courant[1]=NE;
		return((Noeud*)NE);
	}
	ptr=arbre;
	ptr_Svt=arbre->fdt;
	
	while(priorite(ptr_Svt->champ_opp->opperateur,opperateur) == 1)
	{
		ptr=ptr_Svt;
		ptr_Svt=ptr_Svt->fdt;
	}
	ptr->fdt=NE;
	NE->fgche=ptr_Svt;
	element_courant[1]=NE;
	return((Noeud*)arbre);
	
}

/* op1 -> l'operateur qui se trouve dans le noeud courant
   op2 -> operateur lu */
int priorite(char op1,char op2)
{
	if((op1 =='+') || (op1 == '-'))
	{
		if((op2 =='-') || (op2 == '+'))return((int)0);
		return((int)1);
	}
	return((int)0);

}

Noeud* convertir_exp_math_arbre(void)
{
	char opperateur;
	float opperande;
	U_char_float elem;
	Noeud * arbre=NULL,* NE,*element_courant;
	
	opperande=Caracters_To_float(&opperateur);
	elem.opperande=opperande;
	NE=Creer_Noeud(elem);
	
	//Si l'expression est compos� d'un seul chifre
	if(opperande=='\n')
		return (Noeud*)NE;
		
	//Si non on met l'opperateur dans la racine et l'opperande comme fils
	arbre=NE;	
	elem.opperateur=opperateur;
	NE=Creer_Noeud(elem);
	NE->fgche=arbre;
	arbre=NE;	
	
	//Traiter les elements qui restent
	while(opperateur!='\n')
	{
		opperande=Caracters_To_float(&opperateur);
		
		
	}
}







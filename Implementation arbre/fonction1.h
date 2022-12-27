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
	Entée: U_char_float val : la valeur a mettre dans le nouvel element
	Sorties: le nouvel element alloué
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

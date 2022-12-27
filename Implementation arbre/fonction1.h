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


Noeud * Creer_Noeud(U_char_float val)
{
	Noeud *arb;
	
	//allocation memoire du nouvel element
	arb=(Noeud*)malloc(sizeof(Noeud));
	
	//Test si l'allocation est bien fait
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

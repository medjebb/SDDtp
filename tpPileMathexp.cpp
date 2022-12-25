#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct nd
{
	float info;
	struct nd *suivant;
}cellule;


cellule *creer_cellule(float val)
{
	cellule *NE;
	NE=(cellule*)malloc(sizeof(cellule));
	if(!NE)
	{
		printf("erreur d\'allocation");
		exit(0);
	}
	NE->info=val;
	NE->suivant=NULL;
	return((cellule*)NE);
}

cellule *empiler(cellule *pile,float val)
{	
	cellule *NE;
	NE=creer_cellule(val);
	if(!pile)return((cellule*)NE);
	NE->suivant=pile->suivant;
	pile->suivant=NE;
	return((cellule*)pile);
}
float Caracters_To_float(char *opr)
{
	float valeur1=0,valeur2=0,rang=.1;
	int unite;
	char cara;
	
	
	//boucler sur la premiere partie du reel 
	//qui est avant le '.'
	

	while( ((cara=getchar()) != ((int)'.')) || (cara != ((int)'\n')) ) 
	{
		unite=Est_numerique(cara);
		if (unite == -1)break;
		valeur1=valeur1*10+unite;				
	}	
	
	//lecture des chiffres apres la virgule
	if(cara=='.')
	{
		while((cara=getchar())!=(int)'\n')
		{
			unite=Est_numerique(cara);
			if (unite == -1)break;
			valeur2+=unite*rang;
					rang/=10;	
					
		}
	}
	
	if(est_operateur(cara))*opr=cara;	

	// retourner la somme des deux parties du float
	return (float)(valeur1+valeur2);
}



int Est_numerique(char cara)
{
	if(((int)'0'<=(int)cara) && ((int)cara<= (int)'9')) 
		return ((int)cara - (int)'0');	
	return((int)-1)	;
}
int est_operateur(char car)
{
	return((car == '+') || (car == '-') || (car == '*') || (car == '\\'));
}



int ExperssionMath_pile(){
	cellule *maPile,*NE;
	float valeur;
	char c,*opr;
	cellule *ptr;
	ptr=mapile;
	
	do
	{
		valeur=Caracters_To_float(opr);
		maPile=empile(valeur);
		
		
		
	}while(opr);
	

	
}







int main(int argc, char** argv) {
	return 0;
}







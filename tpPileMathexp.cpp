#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


float Caracters_To_float(char *opr)
{
	
	float valeur1=0,valeur2=0,rang=.1;
	int unite;
	char cara;
	
	
	cara=getchar();
	unite=Est_numerique(cara);
	switch (cara)
		{
			case '+': 
				signe=1;
				break;
			case '-':
				signe=-1;
				break;
			case -11:
				printf("Erreur de lecture"); 
				exit(0);
				break;
			default:  valeur1=valeur1*10+unite;	
		}
		
	
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

//

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










int main(int argc, char** argv) {
	return 0;
}







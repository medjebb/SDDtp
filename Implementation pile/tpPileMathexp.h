
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












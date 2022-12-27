


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

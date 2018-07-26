#include<stdio.h>
#include<stdlib.h>
#include "fonction.h"

void TrouverSortie(int tab[][W])
{
	int memi[50];
	int memj[50];
	int k=0,i=0,j=0,haut,bas,droite,gauche,mem;
	while ((i!=W-1)||(j!=W-1))
	{
		haut = TestDirection2(tab[i-1][j],i,1);
		bas = TestDirection2(tab[i+1][j],i,2);
		gauche = TestDirection2(tab[i][j-1],j,1);
		droite = TestDirection2(tab[i][j+1],j,2);
		
		if ((haut + bas + droite + gauche)<=2)
		{
			memi[k]=i;
			memj[k]=j;
			k=k+1;		
		}

		if (bas==0) 
		{
			tab[i][j]=5;
			i = i+1;
		}
		else if (droite==0)
		{
			tab[i][j]=3;
			j=j+1;	
		}
		else if (haut==0)
		{
			tab[i][j]=4;
			i=i-1;	
		}
		else if (gauche==0)
		{
			tab[i][j]=2;
			j=j-1;	
		}
		
		else 
		{	
			tab[i][j]=6;
			k=k-1;
			i=memi[k]; 
			j=memj[k]; 	
		}	
	}
	i=0;j=0;
	while( (i!=W-1) || (j!=W-1))
	{
		mem=tab[i][j];
		tab[i][j]=7;
		switch(mem)
		{
			case 2:j=j-1;
			break;
			case 3:j=j+1;
			break;
			case 4:i=i-1;
			break;
		 	case 5:i=i+1;
			break;
		}		
	}
	tab[i][j]=7;			
}


int main()
{

	int tab[H][W];
	GenerateLabyrinthe(H,W,tab);
	clearLab(tab);
	TrouverSortie(tab);
	clearLab(tab);
	DisplayLabyrinthe(tab);
	printf("\n\n");
	return 0;
}

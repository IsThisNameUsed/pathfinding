#include<stdio.h>
#include<stdlib.h>
#include "fonction.h"


void TrouverSortie(int tab[][W])
{
	int i,j,maxi=W-3,maxj=W-3,mem;
	tab[W-1][W-1]=-1;
	if(tab[W-2][W-1]==0) tab[W-2][W-1]=5;
	if(tab[W-1][W-2]==0) tab[W-1][W-2]=3;
	
	/*Double boucle parcourant la zone du tableau concernée par les calculs*/
	while(tab[0][0]==0)
	{
		for(i=W-1;i>=maxi;i--)
		{
			for(j=W-1;j>=maxj;j--)
			{
				if(tab[i][j]==0)
				{
					if(tab[i+1][j]>=2 && i+1<W) 	  tab[i][j]=5; 	/*test voisin bas*/		
					else if(tab[i][j+1]>=2 && j+1<W) tab[i][j]=3; 	/*test voisin droite*/		
					else if(tab[i][j-1]>=2 && j-1>=0) tab[i][j]=2; 	/*test voisin gauche*/		
					else if(tab[i-1][j]>=2 && i-1>=0) tab[i][j]=4;  /*test voisin haut*/
					
					/*Augmentation (ou non) de la zone concernée par les calculs, controlée par maxi et maxj*/
					if(tab[i][j]>1)
					{
						if(maxi>(i-1) && (i>0)) maxi=i-1;
						if(maxj>(j-1) && (j>0)) maxj=j-1;
					}
				}								
			}
		}			
	}

	i=0;j=0;
	/*Parcours et balisage du chemin trouvé*/
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
}




int main()
{
	int tab[W][W];
	srand(time(NULL));
	GenerateLabyrinthe(W,W,tab);
	clearLab(tab);
	TrouverSortie(tab);
	clearLab(tab);
	DisplayLabyrinthe(tab);
	printf("\n\n");
	return 0;
}


#include <stdio.h>
#include<stdlib.h>
#include "fonction.h"


void DisplayLabyrinthe(int tab[][W])
{
	int i=0,j=0;

	printf("  ");
	for(i=1;i<W+2;i++)
	{
		printf("* ");
	}
	printf("\n");
	
	for(i=0;i<H;i++)
	{
		printf("* ");
		for(j=0;j<W;j++)
		{	
			if(tab[i][j]==0) printf("  ");
			if(tab[i][j]==1) printf("* ");
			if(tab[i][j]==2) printf("G ");
			if(tab[i][j]==3) printf("D ");
			if(tab[i][j]==4) printf("H ");
			if(tab[i][j]==5) printf("B ");
			if(tab[i][j]==6) printf("X ");
			if(tab[i][j]==7) printf("0 ");
			if(tab[i][j]==-1) printf("S ");
			if(j==W-1) printf("*");
		}
		printf("\n");		
	}
	
	
	for(i=0;i<W+1;i++)
	{
		printf("* ");
	}

}

int TestDirection(int t,int indice,int y)
{
	
	int r;
	if (y==1)
	{
		if((indice==0)||(t==1)||(t==4))r=1;						
		else r=0;
	}
	
	if (y==2)
	{
		if((indice==H-1)||(t==1)||(t==4))r=1;						
		else r=0;
	}
	return r;
		
}

int TestDirection2(int t,int indice,int y)
{
	
	int r;
	if (y==1)
	{
		if((indice==0)||(t>=1))r=1;						
		else r=0;
	}
	
	if (y==2)
	{
		if((indice==W-1)||(t>=1))r=1;						
		else r=0;
	}
	
	return r;
		
}


int Chemin(int tab [][W],int a, int b)
{
	if(tab[a][b]==3)
	{
		tab[a][b] = 4;
	}
	else tab[a][b] = 3;
	return tab[a][b];
}

void ChoixDirection(int tab[][W],int *i,int *j,int y)
{
	
	int direction;
	direction=rand()%(3-1)+1;			
	switch(direction)
	{
		case 1:
		*i = *i+y;
		break;
		case 2:
		*j = *j+y;
		break;
	}
	tab[*i][*j]=Chemin(tab,*i,*j);	
	
	
}

void Digaway(int tab[][W])
{

	int i=H-1,j=W-1,droite=0,gauche=0,haut=0,bas=0;
	int *pointeurI = &i, *pointeurJ = &j;
	srand(time(NULL));
	tab[H-1][W-1]=3;
	tab[0][0]=0;
		
	while((i!=0)||(j!=0))
	{
		
		
		haut = TestDirection(tab[i-1][j],i,1);
		bas = TestDirection(tab[i+1][j],i,2);
		gauche = TestDirection(tab[i][j-1],j,1);
		droite = TestDirection(tab[i][j+1],j,2);
		
		if((gauche==0)&&(haut==0))
		{
			ChoixDirection(tab,pointeurI,pointeurJ,-1);
		}
		
		else if(haut==0) 
		{ 
			i--;
			tab[i][j]=Chemin(tab,i,j);	
		}
		
		else if(gauche==0) 
		{
			j--;
			tab[i][j]=Chemin(tab,i,j);	 
		}
		
		else if((bas==0)&&(droite==0))
		{
			
			ChoixDirection(tab,pointeurI,pointeurJ,1);
			
		}
		
		else if(droite==0) 
		{
			j++;
			tab[i][j]=Chemin(tab,i,j);	
		}
		
		else if(bas==0) 
		{
			i++;
			tab[i][j]=Chemin(tab,i,j);	
		}
	
		else if((gauche==1)&&(droite==1)&&(haut==1)&&(bas==1))	
		{	
		
			if ((i!=0)&&(j!=0))
			{					
				ChoixDirection(tab,pointeurI,pointeurJ,-1);
			}
		
			else if(j==0)
			{				
				i --;
				tab[i][j]=Chemin(tab,i,j);
			}
			
			else
			{				
				j--;
				tab[i][j]=Chemin(tab,i,j);
			}
		}	
				
	}
		
}

void GenerateLabyrinthe(int w,int h,int tab[][w])
{
	int i,j;
	srand(time(NULL));

	for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
		tab[i][j]=rand()%(2-0)+0;
		}
	}
	Digaway(tab);
}

void clearLab(int tab[][W])
{
	int i,j;
	for(i=0;i<H;i++)
	{
		for(j=0;j<W;j++)
		{
			
			if(tab[i][j]>1&&tab[i][j]<7) tab[i][j]=0;
		}
	}
}

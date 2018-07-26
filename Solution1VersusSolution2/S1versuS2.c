#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<time.h>
#include "fonction.h"

float TrouverSortie2(int tab[][W])
{
	int i,j,maxi=17,maxj=17,mem;
	float temps;
	clock_t t1,t2;
	/*Top1 horloge*/
	t1=clock();
	tab[W-1][W-1]=-1;
	if(tab[W-2][W-1]==0) tab[W-2][W-1]=5;
	if(tab[W-1][W-2]==0) tab[W-1][W-2]=3;
	
	while(tab[0][0]==0)
	{				
		for(i=W-1;i>=maxi;i--)
		{
			for(j=W-1;j>=maxj;j--)
			{
				if(tab[i][j]==0)
				{
					if(tab[i+1][j]>=2 && i+1<20) 	  tab[i][j]=5;	/*test voisin bas*/		
					else if(tab[i][j+1]>=2 && j+1<20) tab[i][j]=3;/*test voisin droite*/		
					else if(tab[i][j-1]>=2 && j-1>=0) tab[i][j]=2;	/*test voisin gauche*/		
					else if(tab[i-1][j]>=2 && i-1>=0) tab[i][j]=4; /*test voisin haut*/
					/* Extension (ou non) de la zone du tableau concernée par les calculs */
					{
						if(maxi>(i-1) && (i>0)) maxi=i-1;
						if(maxj>(j-1) && (j>0)) maxj=j-1;
						
					}
				}
									
			}
		}					
	}
	/*Top2 horloge, temps= top2-top1 avec conversion en microseconde*/
	t2=clock();
	temps = ((float)(t2-t1)/CLOCKS_PER_SEC)*1000000;
	i=0;j=0;
	while( i!=19 || j!=19)
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
	return temps;	
}

float TrouverSortie1(int tab[][W])
{
	int memi[50];
	int memj[50];
	int k=0,i=0,j=0,haut,bas,droite,gauche,mem;
	float temps;
	clock_t t1,t2;
	t1=clock();
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
		tab[i][j]=7;
		
	}
	t2=clock();
	temps=((float)(t2-t1)/CLOCKS_PER_SEC)*1000000;
	i=0;j=0;
	while( i!=W-1 || j!=W-1)
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
	return temps;	
}


int main()
{
	int tab[H][W],tab2[H][W],i,j,p;
	float t1,t1max,t1min=1000,moyt1,t2,t2max,t2min=1000,moyt2;
	srand(time(NULL));
	while(p<5)
	{	
		GenerateLabyrinthe(H,W,tab);
		clearLab(tab);
		for(i=0;i<W;i++)
		{
			for(j=0;j<W;j++)
			{
				tab2[i][j]=tab[i][j];
			}
		}
		t1=TrouverSortie1(tab);
		clearLab(tab);
		moyt1=moyt1+t1;
		if(t1<t1min) t1min=t1;
		if(t1>t1max) t1max=t1;
		t2=TrouverSortie2(tab2);
		clearLab(tab2);
		moyt2=moyt2+t2;
		if(t2<t2min) t2min=t2;
		if(t2>t2max) t2max=t2;
		p=p+1;
		sleep(1.2);	
	}
	moyt1=moyt1/p;
	moyt2=moyt2/p;
	printf("moyt1 = %.3f microsecondes t1min = %.3f microseconde t1max = %.3f \nmoyt2 = %.3fmicrosecondes t2min = %.3f microseconde t2max = %.3f \n",moyt1,t1min,t1max,moyt2,t2min,t2max);
	return 0;
}


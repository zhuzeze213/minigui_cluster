#include "map.h"
#include <stdio.h>
#include <stdlib.h> 
static int buildnum=20;
static int treenum=120;
static int animalnum=50;
struct build_struct build[BUILDNUM];
int map[MAPX+1][MAPY+1];
void init_map()
{
	int i,j;
	for(i=0;i<=MAPX;i++)
	{
		for(j=0;j<=MAPY;j++)
			map[i][j]=NO;
	}
	for(i=MAPX/4;i<=3*MAPX/4;i++)
	{
		for(j=MAPY/4;j<=3*MAPY/4;j++)
			map[i][j]=HUMANLAND;
	}
	for(i=MAPX/4;i<=2*MAPX/5;i++)
	{
		for(j=MAPY/4;j<=2*MAPY/5;j++)
			map[i][j]=FARM;
	}
	for(i=3*MAPX/5;i<=3*MAPX/4;i++)
	{
		for(j=3*MAPY/5;j<=3*MAPY/4;j++)
			map[i][j]=GARDEN;
	}
	while(buildnum)
	{
		int t1,t2;
		t1=rand()%(MAPX/2+1)+MAPX/4;t2=rand()%(MAPY/2+1)+MAPY/4;
		if(map[t1][t2]==HUMANLAND)
		{
			map[t1][t2]=BUILD;	
			buildnum--;
			build[buildnum].x=t1;
			build[buildnum].y=t2;
		}
	}
	while(treenum)
	{
		int t1,t2;
		t1=rand()%(MAPX+1);t2=rand()%(MAPY+1);
		if(t1&&t2&&map[t1][t2]==NO)
		{
			map[t1][t2]=TREE;
			treenum--;
		}
	}
	while(animalnum)
	{
		int t1,t2;
		t1=rand()%(MAPX+1);t2=rand()%(MAPY+1);
		if(t1&&t2&&map[t1][t2]==NO)
		{
			map[t1][t2]=ANIMAL;
			animalnum--;
		}
	}
}	
	
void printmap()
{
	int i=0,j=0;
	for(i=0;i<=MAPX;i++)
	{
		for(j=0;j<=MAPY;j++)
			printf("%i ",map[i][j]);
		printf("\n");
	}
}

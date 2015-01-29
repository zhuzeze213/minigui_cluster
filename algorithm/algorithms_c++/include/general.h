#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <time.h>
#include <math.h>

# define MAX(a, b)	(((a) > (b))? (a) : (b))

# define MIN(a, b)	(((a) < (b))? (a) : (b))

#define __swap(a,b)  ({(a)+=(b); (b)=(a)-(b); (a)=(a)-(b);})

#define ERROR -1
#define DONE 1
#define RAND 0.1234567

#define OUT_OF_RANGE -2
void print_matrix_double(double *adj,int length)
{
	int i;
	if(!adj) printf("adj is null\n");
	for(i=0;i<length;i++)
		printf("%f ",adj[i]);
	printf("\n");
}

int copy_matrix_double(double *old,double *new,int start,int end,int start2)
{
	if(old&&new){
		int i,j=start2;
		for(i=start;i<end;i++){
			new[j]=old[i];
			j++;
		}
		return DONE;
	}
	return ERROR;
}

void bubblesort(double *a,int length)
{
	int i,j;
	double temp;
	for(i=0;i<=length-1;i++)
	{
		for(j=0;j<length-1-i;j++)
		{
			if(a[j]>a[j+1])
			{
				temp=a[j];a[j]=a[j+1];a[j+1]=temp;
			}
		}
	}
}

int find_num(double *adj,int length,double num)
{
	int i;
	for(i=0;i<length;i++){
		if(adj[i]==num)
			return i;
	}
	return -1;
}

#endif

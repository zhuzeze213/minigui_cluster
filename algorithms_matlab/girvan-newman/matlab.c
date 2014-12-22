#include "mystd.h"

#define RAND 0.1234567
int copy_2_matrix(int **old,int **new,int row,int column)
{
	if(old&&new){
		int i,j;
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				new[i][j]=old[i][j];
		return DONE;
	}
	return ERROR;
}

int *row_num(int **adj,int num,int row,int column)
{
	if(num>=row)
		return NULL;
	int *ret=init_matrix(column);
	if(ret){
		int i;
		for(i=0;i<column;i++)
			ret[i]=adj[num][i];
		return ret;
	}
	return NULL;
}

double *row_num_double(double **adj,int num,int row,int column)
{
	if(num>=row)
		return NULL;
	double *ret=init_matrix_double(column);
	if(ret){
		int i;
		for(i=0;i<column;i++)
			ret[i]=adj[num][i];
		return ret;
	}
	return NULL;
}

int sum_1(int *D,int length)
{
	if(!D) return ERROR;
	int i,sum=0;
	for(i=0;i<length;i++)
		sum+=D[i];
	return sum;
}

double sum_1_double(double *D,int length)
{
	if(!D) return ERROR;
	int i;
	double sum=0.0;
	for(i=0;i<length;i++)
		sum+=D[i];
	return sum;	
}


int equal_int_1(int *a,double *b,int length)
{
	int i;
	for(i=0;i<length;i++){
		double tmp=a[i]*1.0;
		if(tmp!=b[i])
			return 0;
	}
	return 1;
}

int **zeros(int row,int column)
{
	int **adj;
	if(adj=init_2_matrix(row,column)){
		if(fill(adj,0,row,column)==DONE)
			return adj;
	}
	return NULL;
}

double **zeros_double(int row,int column)
{
	double **adj;
	if(adj=init_2_matrix_double(row,column)){
		if(fill_double(adj,0.0,row,column)==DONE)
			return adj;
	}
	return NULL;
}	
int fill(int **adj,int num,int row,int column)
{
	if(adj){
		int i,j;
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				adj[i][j]=num;
		return DONE;
	}
	return ERROR;
}

int fill_double(double **adj,double num,int row,int column) 
{
        if(adj){
                int i,j;
                for(i=0;i<row;i++){
                        for(j=0;j<column;j++){
							if(num==RAND)
								adj[i][j]=(double)(rand()/(INT_MAX/1.0));
							else
								adj[i][j]=num;
						}
				}
                return DONE;
        }
        return ERROR;
}

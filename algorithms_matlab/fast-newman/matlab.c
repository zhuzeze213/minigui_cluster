#include "mystd.h"

#define RAND 0.1234567



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

double **zeros_double(int row,int column)
{
	double **adj;
	if(adj=init_2_matrix_double(row,column)){
		if(fill_double(adj,0.0,row,column)==DONE)
			return adj;
	}
	return NULL;
}


/*Function sum(int **adj,int num,int row,int column) if num==1 return the sum of column num==2 return row*/
int *sum(int **adj,int num,int row,int column)
{
	if(num==1){
		int *ret=init_matrix(column);
		if(ret){
			int tmp_sum=0,i,j;
			for(i=0;i<column;i++)
				for(j=0;j<row;j++)
					ret[i]+=adj[j][i];
			return ret;
		}
		return NULL;
	}
	else if(num==2){
		int *ret=init_matrix(row);
		if(ret){
			int tmp_sum=0,i,j;
			for(i=0;i<row;i++)
				for(j=0;j<column;j++)
					ret[i]+=adj[i][j];
			return ret;
		}
		return NULL;
	}
	else
		return NULL;
}
double *sum_double(double **adj,int num,int row,int column)
{
	if(num==1){
		double *ret=init_matrix_double(column);
		if(ret){
			double tmp_sum=0;
			int i,j;
			for(i=0;i<column;i++)
				for(j=0;j<row;j++)
					ret[i]+=adj[j][i];
			return ret;
		}
		return NULL;
	}
	else if(num==2){
		double *ret=init_matrix_double(row);
		if(ret){
			double tmp_sum=0;
			int i,j;
			for(i=0;i<row;i++)
				for(j=0;j<column;j++)
					ret[i]+=adj[i][j];
			return ret;
		}
		return NULL;
	}
	else
		return NULL;
}


/* n is *v size*/

double **copy_double(double *old,int copy,int length)
{
	double **adj;
	int i=0,j=0;
	adj=init_2_matrix_double(copy,length);
	if(adj){
		for(i=0;i<copy;i++){
			for(j=0;j<length;j++)
				adj[i][j]=old[j];
		}
		return adj;
	}
	return NULL;
}


double trace(double **adj,int row)
{
	double sum=0.0;
	int i;
	for(i=0;i<row;i++)
		sum+=adj[i][i];
		
	return sum;
}
	
int *sort(int *D,int *s_D,int length)
{
	int *IX=init_matrix(length);
	int *D_copy=init_matrix(length);
	copy_matrix(D,D_copy,0,length,0);
	if(s_D&&IX){
		int i,j;int min=INT_MAX,minindex=-1;
		int sortc=0;
		for(i=0;i<length;i++){
			for(j=0;j<length;j++){
				if(D[j]<min){
					min=D[j];
					minindex=j;
				}
			}
			s_D[sortc]=min;
			IX[sortc]=minindex;
			sortc++;
			D[minindex]=INT_MAX;
			min=INT_MAX;minindex=-1;
		}
		copy_matrix(D_copy,D,0,length,0);
		free_matrix(D_copy);
		return IX;
	}
	return NULL;
			
}

int *sort_double(double *D,double *s_D,int length)
{
	int *IX=init_matrix(length);
	double *D_copy=init_matrix_double(length);
	copy_matrix_double(D,D_copy,0,length,0);
	if(s_D&&IX){
		int i,j;double min=INT_MAX*1.0;
		int minindex=-1;
		int sortc=0;
		for(i=0;i<length;i++){
			for(j=0;j<length;j++){
				if(D[j]<min){
					min=D[j];
					minindex=j;
				}
			}
			s_D[sortc]=min;
			IX[sortc]=minindex;
			sortc++;
			D[minindex]=INT_MAX*1.0;
			min=INT_MAX*1.0;minindex=-1;
		}
		copy_matrix_double(D_copy,D,0,length,0);
		free_matrix_double(D_copy);
		return IX;
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

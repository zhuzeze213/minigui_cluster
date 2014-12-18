#include "mystd.h"

int find_int(int **adj,int *r,int *c,int *v,int edge,int row,int column)
{
	if(r&&c&&v){
		int i,j;int rc=0,cc=0,vc=0;
		for(i=0;i<row;i++){
			for(j=0;j<column;j++){
				if(adj[i][j]!=0){
					r[rc]=i;
					c[cc]=j;
					v[vc]=adj[i][j];
					rc++;cc++;vc++;
				}
			}
		}
		return DONE;
	}
	return ERROR;
}
int find_double(double **adj,int *r,int *c,double *v,int edge,int row,int column)
{
	if(r&&c&&v){
		int i,j;int rc=0,cc=0,vc=0;
		for(i=0;i<row;i++){
			for(j=0;j<column;j++){
				if(adj[i][j]!=0.0){
					r[rc]=i;
					c[cc]=j;
					v[vc]=adj[i][j];
					rc++;cc++;vc++;
				}
			}
		}
		return DONE;
	}
	return ERROR;
}
/* sort change to already sort array s_D and return the index array */
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

int edge_matrix_double(double **adj,int row,int column)
{
	if(!adj) return ERROR;
	int i,j;
	int edge=0;
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			if(adj[i][j]!=0.0)
				edge++;
		}
	}
	return edge;
}
/* find the minmum num and return the index */
int min_double(double *D,double *min,int length)
{
	if(!D) return ERROR;
	int i;
	int minindex=-1;
	*min=INT_MAX*1.0;
	for(i=0;i<length;i++){
		if(D[i]<*min){
			*min=D[i];
			minindex=i;
		}
	}
	return minindex;
	
}






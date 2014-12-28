#include "../include/mystd.h"

int **get_indicator_matrix(int **adj,int *com,int n)
{
	int nc;
	unique(com,n,&nc);
	int **H=zeros(n,nc);
	int i;
	for(i=0;i<n;i++)
		H[i][com[i]]=1;
		
	return H;
}

double kl(int **adj,int *com,int *cur_com,int row)
{
	int verbose=0;//false
	int ts=1;
	int nb_passes=INT_MAX;
	
	int **H=get_indicator_matrix(adj,com,row);
	int *d=sum(adj,2,row,row);
	/* M = diag(d) \ adj; A\B=inv(A)*B */
	int **M_tmp=create_diag(d,row,0);
	/* inv(M_tmp) */
	int **M_tmp_2=inv(M_tmp,row,row);
	
	int **M=matrix_multiply_int(M_tmp_2,adj,row,row,row,row);
	double *pi=init_matrix_double(row);
	int i;
	for(i=0;i<row;i++){
		pi[i]=d[i]*1.0/sum_1(d,row);
	}
	double **PI=create_diag_double(pi,row,0);
	
	
	
}
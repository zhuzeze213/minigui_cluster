#include "../include/mystd.h"

double compute_stability(int **M,int **H,double *pi,double **PI,int ts,int row)
{
	double Q=1.0;
	int s=0;
	/* one loop*/
	double **pri=matrix_multiply_int_2(PI,M,row,row,row,row);
	double **pi_sum=init_2_matrix_double(row,row);
	double **pi_t=init_2_matrix_double(row,1);
	for(s=0;s<row;s++)
		pi_t[s][0]=pi[s];
	for(i=0;i<row;i++)
		for(j=0;j<row;j++)
			pi_sum[i][j]+=pi_t[i][0]*pi[j];
	double **tmp=matrix_operate_double(pri,pi_sum,'-',row,row);
	int **H_t=transposition(H,row,row);
	double **m_tmp1=matrix_multiply_int_1(H_t,tmp,row,row,row,row);
	double **Rs=matrix_multiply_int_2(m_tmp1,H,row,row,row,row);
	double Q_tmp=trace(Rs,row);
	if(Q_tmp<Q)
		Q=Q_tmp;
}

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
	double Q=compute_stability(M,H,pi,PI,ts,row);
	double init_Q=Q;
	copy_matrix(com,cur_com,0,row,0);
	int change=1;//true
	while(change){
		change=0;
		int i,j;
		for(i=0;i<row;i++){
			double loop_best_Q=Q;
			for(j=i+1;j<row;j++){
				
	
	
	
}
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
				if(adj[i][j]!=0&&cur_com[i]!=cur_com[j]){
					int *com_tmp=init_matrix(row);
					copy_matrix(cur_com,com_tmp,0,row,0);
					com_tmp[i]=com_tmp[j];
					int k=0;
					int length;
					unique(com_tmp,row,&length);
					while(k<length){
						if(!find_num(com_tmp,row,k)){
							int l;
							for(l=0;l<row;l++){
								if(com_tmp[l]>k)
									com_tmp[l]--;
							}
						}
						else
							k++;
					}
					/* 1 loop */
					H=get_indicator_matrix(adj,com_tmp,row);
					double tmp_Q=compute_stability(M,H,pi,PI,ts,row);
					int best_pair[2];
					if(tmp_Q>loop_best_Q){
						loop_best_Q=tmp_Q;
						best_pair[0]=i;
						best_pair[1]=j;
					}
					copy_matrix(cur_com,com_tmp,0,row,0);
					com_tmp[j]=com_tmp[i];
					k=0;
					unique(com_tmp,row,&length);
					while(k<length){
						if(!find_num(com_tmp,row,k)){
							int l;
							for(l=0;l<row;l++){
								if(com_tmp[l]>k)
									com_tmp[l]--;
							}
						}
						else
							k++;
					}
					/* 1 loop */
					H=get_indicator_matrix(adj,com_tmp,row);
					tmp_Q=compute_stability(M,H,pi,PI,ts,row);
					if(tmp_Q>loop_best_Q){
						loop_best_Q=tmp_Q;
						best_pair[0]=j;
						best_pair[1]=i;
					}
				}
			}
			
			if(loop_best_Q>Q){
				Q=loop_best_Q;
				cur_com[best_pair[0]]=cur_com[best_pair[1]];
				int k=0;
				int length=0;
				unique(cur_com,row,&length);
				while(k<length){
					if(!find_num(com_tmp,row,k)){
						int l;
						for(l=0;l<row;l++){
							if(cur_com[l]>k)
								cur_com[l]--;
						}
					}
					else
						k++;
				}
				if(nb_passes>0){
					nb_passes--;
					change=1;
				}
			}
		}
	}
	return Q;			
	
}

int main(int argc,char *argv[])
{
	struct network network;
	if(loadmatrix(argv[1],&network)){
		int *com=init_matrix(network.node);
		for(i=0;i<network.node;i++)
			com[i]=i;
		int *cur_com=init_matrix(network.node);
		double Q=kl(network.adj,com,cur_com,network.node);
		print_matrix(com,network.node);
		printf("Q:%f\n",Q);
		free_matrix(com);
		free_matrix(cur_com);
		free_2_matrix(network.adj,network.row);
		
	}
	return 0;
}






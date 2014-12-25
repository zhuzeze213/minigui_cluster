#include "mystd.h"

double **get_community_matrix(int **adj,int *com,int row)
{
	int nc=row;
	double **e=zeros_double(nc,nc);
	if(!e) return NULL;
	int m=0;
	int i,j;
	for(i=0;i<row;i++){
		for(j=i;j<row;j++){
			if(adj[i][j]!=0){
				int ic=com[i];
				int jc=com[j];
				if(ic==jc)
					e[ic][ic]+=adj[i][j];
				else{
					e[ic][jc]=e[ic][jc]+0.5*adj[i][j];
					e[jc][ic]=e[ic][jc];
				}
				m+=adj[i][j];
			}
		}
	}
	for(i=0;i<row;i++)
		for(j=0;j<row;j++)
			e[i][j]=e[i][j]/m;
			
	return e;
}

double fast_newman(int **adj,int *com,int row)
{
	int row2=row;
	int *cur_com=init_matrix(row);
	int i,j;
	for(i=0;i<row;i++)
		cur_com[i]=i;
	copy_matrix(cur_com,com,0,row,0);
	
	double **e=get_community_matrix(adj,com,row);
	double *ls=sum_double(e,2,row,row);
	double *cs=sum_double(e,1,row,row);
	double **e2=init_2_matrix_double(row,row);
	for(i=0;i<row;i++)
		for(j=0;j<row;j++)
			e2[i][j]=e[i][j]*e[i][j];
	
	double *sum_tmp=sum_double(e2,1,row,row);
	double sum_sum=sum_1_double(sum_tmp,row);
	double cur_Q=trace(e,row)-sum_sum;
	double Q=cur_Q;
	int *best_pair=init_matrix(2);
	while(row>0){
		double loop_best_dQ=INT_MIN*1.0;
		int can_merge=0;//false
		for(i=0;i<row;i++){
			for(j=i+1;j<row;j++){
				if(e[i][j]>0.0){
					double dQ=2*(e[i][j]-ls[i]*cs[j]);
					if(dQ>loop_best_dQ){
						loop_best_dQ=dQ;
						best_pair[0]=i;
						best_pair[1]=j;
						can_merge=1;
					}
				}
			}
		}
		if(can_merge==0){
			printf("quit the main circulation!\n");
			break;
		}
		int *best=init_matrix(2);
		sort(best_pair,best,2);
		for(i=0;i<row2;i++){
			if(cur_com[i]==best[1])
				cur_com[i]=best[0];
			else if(cur_com[i]>best[1])
				cur_com[i]--;
		}
		
		for(i=0;i<row;i++)
			e[best[0]][i]+=e[best[1]][i];
		for(i=0;i<row;i++)
			e[i][best[0]]+=e[i][best[1]];
		
		double **e_1=init_2_matrix_double(row-1,row-1);
		int x,y,x2=0,y2=0;
		for(x=0;x<row;x++){
			if(x!=best[1]){
				for(y=0;y<row;y++){
					if(y!=best[1]){
						e_1[x2][y2]=e[x][y];
						y2++;
					}
				}
				x2++;
				y2=0;
			}
		}
		
		row--;//attention!
		e=init_2_matrix_double(row,row);
		copy_2_matrix_double(e_1,e,row,row);
		
		ls[best[0]]+=ls[best[1]];
		cs[best[0]]+=cs[best[1]];
		double *ls_1=init_matrix_double(row);
		double *cs_1=init_matrix_double(row);
		x2=0;
		for(x=0;x<row+1;x++){
			if(x!=best[1]){
				ls_1[x2]=ls[x];
				cs_1[x2]=cs[x];
				x2++;
			}
		}
		ls=init_matrix_double(row);
		cs=init_matrix_double(row);
		copy_matrix_double(ls_1,ls,0,row,0);
		copy_matrix_double(cs_1,cs,0,row,0);

		cur_Q+=loop_best_dQ;
		if(cur_Q>Q){
			//printf("%f\n",Q);
			Q=cur_Q;
			copy_matrix(cur_com,com,0,row2,0);
		}
		free_matrix(best);
		free_2_matrix_double(e_1,row);
		free_matrix_double(ls_1);
		free_matrix_double(cs_1);
	}
	
	free_matrix_double(sum_tmp);
	free_matrix(best_pair);
	free(cur_com);
	//free_2_matrix_double(e,row2);//they are becoming smaller and smaller!
	free_matrix_double(ls);
	free_matrix_double(cs);
	free_2_matrix_double(e2,row2);

	return Q;
	
}

int main(int argc,char *argv[])
{
	struct network network;
	if(loadmatrix(argv[1],&network)){
		int row=network.row;
		int *com=init_matrix(row);
		double Q=fast_newman(network.adj,com,row);
		print_matrix(com,row);
		printf("Q:%f\n",Q);
		free_matrix(com);
		free_2_matrix(network.adj,row);
	}
	return 0;
}

















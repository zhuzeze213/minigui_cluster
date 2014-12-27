#include "mystd.h"
double Calculate_Q(int **football,int **best_community,int Nnode,int col,int edges)
{
	double value_Q=0.0;
	int row=Nnode;
	int step_row_1=0;
	double edge_between[row][row];
	int i,j;
	for(i=0;i<row;i++)
		for(j=0;j<row;j++)
			edge_between[i][j]=0.0;
	while(step_row_1<row){
		int step_row_2=step_row_1;
		while(step_row_2<row){
			int len1=col;
			int step_col_1=0;
			while(step_col_1<len1){
				int step_col_2=0;
				int len2=col;
				while(step_col_2<len2){
					if(best_community[step_row_1][step_col_1]!=-1&&best_community[step_row_2][step_col_2]!=-1){
						if(football[best_community[step_row_1][step_col_1]][best_community[step_row_2][step_col_2]]==1)
							edge_between[step_row_1][step_row_2] = edge_between[step_row_1][step_row_2] + 1;
					}
					step_col_2++;
				}
				step_col_1++;
			}
			edge_between[step_row_2][step_row_1] = edge_between[step_row_1][step_row_2];
			if (step_row_2 == step_row_1)
				edge_between[step_row_1][step_row_2] = edge_between[step_row_1][step_row_2]/2;
			step_row_2++;
		}
		step_row_1++;
	}
	for(i=0;i<row;i++)
		for(j=0;j<row;j++)
			edge_between[i][j]=edge_between[i][j]/edges;
	int step_row=0;
	double e=0;
	double a[row];
	for(i=0;i<row;i++)
		a[i]=0.0;
	while(step_row<row){
		e+=edge_between[step_row][step_row];
		int step_col=0;
		while(step_col<row){
			a[step_col]+=edge_between[step_row][step_col];
			step_col++;
		}
		step_row++;
	}
	value_Q=e;
	step_row=0;
	while(step_row<row){
		value_Q=value_Q-a[step_row]*a[step_row];
		step_row++;
	}
	return value_Q;
}

double sa(int **adj,int count,int row,int edges)
{
	int **best_community=init_2_matrix(count,row);
	fill(best_community,-1,count,row);
	int i;
	int clu_count[count];
	for(i=0;i<count;i++)
		clu_count[i]=-1;
	
	for(i=0;i<row;i++){
		int ran_des=rand()%count;
		best_community[ran_des][clu_count[ran_des]+1]=i;
		clu_count[ran_des]++;
	}
	
	int **community=init_2_matrix(count,row);
	copy_2_matrix(best_community,community,count,row);
	//print_2_matrix(community,count,row);
	double Q_max=Calculate_Q(adj,community,count,row,edges);
	
	double r=0.9,T=1000000.0,T_min=1.0;
	while(T>T_min){
		int from=rand()%count;
		int dest=rand()%count;
		int fromindex=rand()%(clu_count[from]+1);
		if(from!=dest&&clu_count[dest]<row-1&&clu_count[from]>0){
			community[dest][clu_count[dest]+1]=community[from][fromindex];
			community[from][fromindex]=-1;
			int j;
			for(j=fromindex;j<=clu_count[from];j++)
				community[from][j]=community[from][j+1];
			double Q_tmp=Calculate_Q(adj,community,count,row,edges);
			//printf("%f ",Q_tmp);
			if(Q_tmp>Q_max){
				Q_max=Q_tmp;
				clu_count[from]--;
				clu_count[dest]++;
				copy_2_matrix(community,best_community,count,row);
			}
			else{
				if(exp((T*r-T)/T)>rand()*1.0/INT_MAX){
					printf("%f %f\n",T,exp((T*r-T)/T));
					Q_max=Q_tmp;
					clu_count[from]--;
					clu_count[dest]++;
					copy_2_matrix(community,best_community,count,row);
				}
				else
					copy_2_matrix(best_community,community,count,row);
			}
			T*=r;
		}
	}
	print_2_matrix(best_community,count,row);
	free_2_matrix(community,count);
	free_2_matrix(best_community,count);
	return Q_max;
}

int main(int argc,char *argv[])
{
	srand((unsigned int)time(NULL));
	struct network network;
	if(loadmatrix(argv[1],&network)){
		int count=atoi(argv[2]);
		double Q=sa(network.adj,count,network.row,network.edge);
		printf("Q:%f\n",Q);
		free_2_matrix(network.adj,network.row);
	}
	return 0;
}

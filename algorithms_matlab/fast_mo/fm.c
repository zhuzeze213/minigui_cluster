#include "../include/mystd.h"

double compute_Q(int **adj,int *com,int m2,int *d,int row)
{
	double Q=0.0;
	int i,j;
	for(i=0;i<row;i++){
		Q+=adj[i][i];
		for(j=i+1;j<row;j++){
			if(com[i]==com[j])
				Q=Q+2*(adj[i][j]-(d[i]*d[j])/m2);
		}
		Q=Q-(d[i]*d[i])/m2;
	}
	Q=Q/m2;
}

double fast_mo(int **adj,int *com,int row,int column,int edge)
{
	int m2=edge;
	int m=edge/2;
	int *d=sum(adj,2,row,column);
	
	int **Nbs=init_2_matrix(row,row);
	fill(Nbs,-1,row,row);
	int i,j,k;
	for(i=0;i<row;i++){
		int *tmp=find(adj[i],column);
		if(j=find_num(tmp,column,i)>=0){
			for(k=j;k<column-1;k++)
				tmp[k]=tmp[k+1];			
		}
		copy_matrix(tmp,Nbs[i],0,column,0);
	}
	
	int *wcom=init_matrix(row);
	copy_matrix(d,wcom,0,row,0);
	for(i=0;i<row;i++)
		com[i]=i;
	
	double Q=compute_Q(adj,com,m2,d,row);
	int check_nodes=1;
	int check_communities=1;
	while(check_nodes){
		int moved=1;
		while(moved){
			moved=0;
			int *l=init_matrix(row);
			for(i=0;i<row;i++)
				l[i]=i;
			int row2=row;
			while(l){
				int idx=rand()%row2;
				int n=l[idx];
				int *l_tmp=init_matrix(row2-1);
				int i2=0;
				for(i=0;i<row2;i++){
					if(i!=idx){
						l_tmp[i2]=l[i];
						i2++;
					}
				}
				l=init_matrix(row2-1);
				copy_matrix(l_tmp,l,0,row2-1,0);
				row2--;
				
				int length=0;
				for(length=0;length<row;length++)
					if(Nbs[n][length]==-1)
						break;
				
				int *unique_tmp=init_matrix(length);
				for(i=0;i<=length;i++){
					unique_tmp[i]=com[i];
				
				int *ncom=unique(unique_tmp,length,&length);
				int same_count=0;
				int index=find_num(ncom,length,com[n]);
				if(index>=0){
					int *ncom_tmp=init_matrix(length-1);
					i2=0;
					for(i=0;i<length;i++){
						if(i!=index){
							ncom_tmp[i2]=ncom[i];
							i2++;
						}
					}
					ncom=init_matrix(length-1);
					copy_matrix(ncom_tmp,ncom,0,length-1,0);
				}
				
				double best_dQ=0;
				int *nb=init_matrix(row);
				copy_matrix(Nbs[n],nb,0,row,0);
				
				int count=0;
				int *equal=init_matrix(row);
				for(i=0;i<row;i++){
					if(com[n]==com[i]){
						equal[count]=i;
						count++
					}
				}
				int *nb1=init_matrix(count);
				for(i=0;i<count;i++)
					nb1[i]=nb[equal[i]];
				int sum=0;
				for(i=0;i<count;i++)
					sum+=adj[n][nb1[i]];
				int sum_nb1=-sum;
				int w1=wcom[com[n]]-d[n];
				int new_c;
				for(i=0;i<length-1;i++){
					int c=ncom[i];
					int count2=0;
					int *equal2=init_matrix(row);
					for(i=0;i<row;i++){
						if(com[i]==c){
							equal2[count2]=i;
							count2++
						}
					}
					for(i=0;i<count2;i++)
						nb2[i]=nb[equal[i]];
					int sum2=0;
					for(i=0;i<count2;i++)
						sum2+=adj[n][nb2[i]];
					dQ=sum_nb1+sum2;
					dQ=(dQ+(d[n]*(w1-wcom[c]))/m2)/m;
					if(dQ>best_dQ){
						best_dQ=dQ;
						new_c=ncom[i];
					}
				}
				if(best_dQ>0){
					wcom[com[n]]-=d[n];
					wcom[new_c]+=d[n];
					com[n]=new_c;
					Q+=best_dQ;
					moved=1;
					check_communities=1;
				}
			}
		}
		check_nodes=0;
		if(!check_communities)
			break;
		moved=1;
		while(moved){
			moved=0;
			int r_length;
			int *cl=unique(com,row,&r_length);
			while(cl){
				
		
		
		
	
}
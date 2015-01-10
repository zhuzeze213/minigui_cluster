#include "../include/mystd.h"

double compute_Q(int **adj,int *com,int m2,int *d,int row)
{
	double Q=0.0;
	int i,j;
	for(i=0;i<row;i++){
		Q+=adj[i][i];
		for(j=i+1;j<row;j++){
			if(com[i]==com[j])
				Q=Q+2*(adj[i][j]*1.0-(d[i]*d[j])/m2);
		}
		Q=Q-(d[i]*d[i])*1.0/m2;
	}
	Q=Q/m2;
	return Q;
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
		int tmp_count;
		int *tmp=find_count(adj[i],column,&tmp_count);
		if(j=find_num(tmp,column,i)>=0){
			for(k=j;k<column-1;k++)
				tmp[k]=tmp[k+1];			
		}
		copy_matrix(tmp,Nbs[i],0,column,0);
		for(j=0;j<column-1;j++)
			if(Nbs[i][j]==0&&Nbs[i][j+1]==0)
				break;
		for(k=j;k<column;k++)
			Nbs[i][k]=-1;
	}
	//print_2_matrix(Nbs,row,row);
	
	int *wcom=init_matrix(row);
	copy_matrix(d,wcom,0,row,0);
	for(i=0;i<row;i++)
		com[i]=i;
	
	double Q=compute_Q(adj,com,m2,d,row);
	int check_nodes=1;
	int check_communities=1;
	while(check_nodes){
		double best_dQ=0.0;
		double dQ=0.0;
		int *ncom;
		int moved=1;
		while(moved){
			moved=0;
			int *l=init_matrix(row);
			for(i=0;i<row;i++)
				l[i]=i;
			int row2=row;
			while(row2>0){//!
				int idx=rand()%row2;
				int n=l[idx];
				erase_line_matrix(&l,idx,row2);
				row2--;
				
				int length=0;
				for(length=0;length<row-1;length++)
					if(Nbs[n][length]==-1)
						break;
				
				int *unique_tmp=init_matrix(length);
				for(i=0;i<length;i++)
					unique_tmp[i]=com[Nbs[n][i]];
				int alength=0;
				ncom=unique(unique_tmp,length,&alength);
				int index=find_num(ncom,alength,com[n]);
				if(index>=0){
					erase_line_matrix(&ncom,index,alength);
				}
				
				best_dQ=0.0;
				int *nb=init_matrix(row);
				copy_matrix(Nbs[n],nb,0,row,0);
				
				int count=0;
				int *equal=init_matrix(row);
				for(i=0;i<row;i++){
					if(com[n]==com[nb[i]]){
						equal[count]=i;
						count++;
					}
				}
				if(count){printf("%d\n",count);
				int *nb1=init_matrix(count);
				for(i=0;i<count;i++)
					nb1[i]=nb[equal[i]];
				int sum=0;
				for(i=0;i<count;i++)
					sum+=adj[n][nb1[i]];
				int sum_nb1=-sum;
				int w1=wcom[com[n]]-d[n];
				int new_c;
				for(i=0;i<alength-1;i++){
					int c=ncom[i];
					int count2=0;
					int *equal2=init_matrix(row);
					for(i=0;i<row;i++){
						if(com[nb[i]]==c){
							equal2[count2]=i;
							count2++;
						}
					}
					int *nb2=init_matrix(count2);
					for(i=0;i<count2;i++)
						nb2[i]=nb[equal[i]];
					int sum2=0;
					for(i=0;i<count2;i++)
						sum2+=adj[n][nb2[i]];
					dQ=sum_nb1*1.0+sum2;
					dQ=(dQ+(d[n]*(w1-wcom[c]))*1.0/m2)/m;
					//printf("%f %f\n",dQ,best_dQ);
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
				}}
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
			int row3=row;
			while(r_length>0){//!
				int idx=rand()%r_length;
				int cn=cl[idx];
				erase_line_matrix(&cl,idx,r_length);
				r_length--;
				
				int *equal3=init_matrix(row);
				int count3=0;
				for(i=0;i<row;i++){
					if(com[i]==cn){
						equal3[count3]=i;
						count3++;
					}
				}
				int *ncn=init_matrix(count3);
				copy_matrix(equal3,ncn,0,count3,0);
				int *Nbs_union=init_matrix(count3*row);
				int count4=0;
				for(i=0;i<count3;i++){
					for(j=0;j<row-1;j++){
						if(Nbs[ncn[i]][j]!=-1){
							Nbs_union[count4]=Nbs[ncn[i]][j];
							count4++;
						}
						else
							break;
					}
				}
				int r_length2;
				int *nbn=unique(Nbs_union,count4,&r_length2);
				int *comnbn=init_matrix(r_length2);
				for(i=0;i<r_length2;i++)
					comnbn[i]=com[nbn[i]];
				int ncom_length=0;
				ncom=unique(comnbn,r_length2,&ncom_length);
				erase_line_matrix(&ncom,find_num(ncom,ncom_length,cn),ncom_length);
						
				best_dQ=0;
				int *dncn=init_matrix(count3);
				for(i=0;i<count3;i++)
					dncn[i]=d[ncn[i]];
				int sum_dn1=sum_1(dncn,count3);
				
				int ncom_idx;
				int new_cn=0;
				for(ncom_idx=0;ncom_idx<ncom_length-1;ncom_idx++){
					int n2count=0;
					int *n2=init_matrix(row);
					for(i=0;i<row;i++){
						if(ncom[ncom_idx]==com[i]){
							n2[n2count]=i;
							n2count++;
						}
					}
					int sumtmp1=0;
					for(i=0;i<count3;i++)
						for(j=0;j<n2count;j++)
							sumtmp1+=adj[i][j];
					
					int sumtmp2=0;
					for(i=0;i<n2count;i++)
						sumtmp2+=d[n2[i]];
					dQ=(sumtmp1*1.0-sum_dn1*1.0*sumtmp2/m2)/m;
					if(dQ>best_dQ){
						best_dQ=dQ;
						new_cn=ncom[ncom_idx];
					}
				}
				if(best_dQ>0){
					wcom[new_cn]+=wcom[cn];
					wcom[cn]=0;
					for(i=0;i<count3;i++)
						com[ncn[i]]=new_cn;
					Q+=best_dQ;
					moved=1;
					check_nodes=1;
				}
			}
		}
		check_communities=0;
	}
	int u_length;	
	int *ucom=unique(com,row,&u_length);
	for(i=0;i<row;i++)
		com[i]=find_num(ucom,u_length,com[i]);
	
}

int main(int argc,char *argv[])
{
	struct network network;
	if(loadmatrix(argv[1],&network)){
		srand((unsigned int)time(NULL));
		int row=network.row;
		int column=network.column;
		int *com=init_matrix(row);
		double Q=fast_mo(network.adj,com,row,column,network.edge);
		print_matrix(com,row);
		printf("Q:%f\n",Q);
		free_matrix(com);
		free_2_matrix(network.adj,row);
	}
	return 0;
}


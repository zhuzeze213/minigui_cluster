#include "../include/mystd.h"
#define TMPFILE "../tmp/fcm.txt"

void ncut(int **adj,int row,int column)
{
	int **w=init_2_matrix(row,column);
	copy_2_matrix(adj,w,row,column);
	
	int i,j;
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			if(w[i][j]==1)
				w[j][i]=1;
		}
		w[i][i]=0;
	}
	
	int **d=zeros(row,column);
	for(i=0;i<row;i++){
		int sum=0;
		for(j=0;j<row;j++){
			if(w[i][j]==1)
				sum++;
		}
		d[i][i]=sum;
	}
	
	int **l=matrix_operate_double_int(d,w,'-',row,column);
	double *l_double=init_matrix_double(row*column);
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			l_double[i*row+j]=l[i][j];
	double *v_tmp=init_matrix_double(row*column);
	eejcb(l_double,row,v_tmp,0.001,1000);
	double **v=init_2_matrix_double(row,column);
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			v[i][j]=v_tmp[i*row+j];
	double **p=init_2_matrix_double(row,column);
	copy_2_matrix_double_scope(v,p,0,0,34,4,0,0);
	double **U=get_2_matrix_double_f(TMPFILE);
	FILE *fp=fopen(TMPFILE,"r");
	int cluster_n;
	fscanf(fp,"%d",&cluster_n);fclose(fp);
	int **result=zeros(cluster_n,row);
	for(i=0;i<cluster_n;i++)
		for(j=0;j<row;j++)
			result[i][j]--;
	for(i=0;i<cluster_n;i++){
		int *a=init_matrix(row);
		int count=0;
		for(j=0;j<row;j++){
			int index=-1;
			int max=0;
			int k;
			for(k=0;k<cluster_n;k++){
				if(U[k][j]>max){
					index=k;
					max=U[k][j];
				}
			}
			if(index==i)
				a[count++]=j;
		}
		for(j=0;j<count;j++)
			result[i][j]=a[j];
	}
	print_2_matrix(result,cluster_n,row);
}

int main(int argc,char *argv[])
{
	struct network network;
	if(loadmatrix(argv[1],&network)){
		int row=network.row;
		int column=network.column;
		
		ncut(network.adj,row,column);
		free_2_matrix(network.adj,row);
	}
	return 0;
}
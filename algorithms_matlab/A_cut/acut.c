#include "../include/mystd.h"

void acut(int **adj,int row,int column)
{
	int **w=init_2_matrix(row,column);
	copy_2_matrix(adj,w,row,column);
	
	int i,j;
	for(i=0;i<row;i++){
		for(j=0;j<row;j++){
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
	
		
}


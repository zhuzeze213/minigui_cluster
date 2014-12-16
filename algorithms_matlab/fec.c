#include "mystd.h"

/* [pos, EP1, EP2] = FC(new_P); */
void FC(int **new_P,int *pos,int *EP1,int *EP2)
{
	
}
/* function [pos, EP1, EP2, new_W, new_W_names]= PL(W,W_names,error) */
void PL(int **W,int *W_names,double error,int *pos,double *EP1,double *EP2,int ***new_W,int **new_W_names,int length,int edge,int row,int column)
{
	int n=length;
	int *i,*j,*v;
	find(W,&i,&j,&v,edge*2,row,column);
	int NNZ=edge*2;
	int *D=init_matrix(n);
	int r;
	for(r=0;r<NNZ;r++)
		D[i[r]]+=v[r];
		
	double **p=init_2_matrix_double(row,column);
	copy_2_matrix_double_int_1(W,&p,row,column);
	for(r=0;r<NNZ;r++){
		int x=i[r];
		int y=j[r];
		int w=v[r];
		if(D[x]!=0)
			p[x][y]=w/D[x]*1.0;
	}
	int *s_D=init_matrix(n);
	int *IX=sort(D,&s_D,n);
	int sink=IX[n-1];
	double pi_pink=D[n-1]/sum_1(D,n)*1.0;
	double *R0=init_matrix_double(n);
	R0[sink]=1.0;
	
	double *R1=init_matrix_double(n);
	copy_matrix_double(R0,&R1,n);
	double err=1.0;
	int steps=0;
	
	while(err>error&&steps<1000){
		double **S=zeros_double(n,1);
		int r;
		for(r=0;r<NNZ;r++)
			S[i[r]][0]+=R0[j[r]]*v[r];
		
		for(r=0;r<n;r++){
			if(D[r]!=0)
				R1[r]=S[r][0]/D[r]*1.0;
			else
				R1[r]=0.0;
		}
		
		double *tmp=init_matrix_double(n);
		for(r=0;r<n;r++)
			tmp[r]=fabs(R1[r]-R0[r]);
		err=sum_1_double(tmp,n);
		steps++;
		copy_matrix_double(R1,&R0,n);
	}
	double *SR=init_matrix_double(n);
	int *IX2=sort_double(R1,&SR,n);
	
	int *flection=init_matrix(n);
	for(r=0;r<n;r++){
		flection[IX2[r]]=r;
		(*new_W_names)[r]=W_names[IX2[r]];
	}
	
	if(*new_W==NULL)
		(*new_W)=init_2_matrix(n,n);
	int **new_P=init_2_matrix(n,n);
	int *i1,*j1;double *VP;
	find_double(p,&i1,&j1,&VP,edge_matrix_double(p,row,column),row,column);
	for(r=0;r<NNZ;r++){
		x=flection[i[r]];
		y=flection[j[r]];
		new_W[x][y]=v[r];
		new_P[x][y]=VP[r];
	}
	FC(pos,EP1,EP2);
}

/* [new_W,new_W_names,H,id] = NCMA(W,W_names,H,id,err); */
void NCMA(int **W,int *W_names,int ***H,int *id,double err,int ***new_W,int **new_W_names,int edge,int row,int column)
{
	
}

void fec(int **adj,int row,int column)
{
	int node=MAX(row,column);//length(W)
	double err=pow(0.1,7);
	int **H=init_2_matrix(node,node);
	int id=1;
	
	int c;
	int *W_names=init_matrix(node);
	for(c=0;c<node;c++)
		W_name[c]=c;
}

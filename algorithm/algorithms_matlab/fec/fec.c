#include "../include/mystd.h"

/*  function  col = find_first_col(H,v) */
int find_first_col(int **H,int v,int length)
{
	int col;
	for(col=0;col<length;col++){
		if(H[v][col]==0)
			break;
	}
	return col;
}
/* function H = makeH(H, id, names, first, last) */
void makeH(int **H,int id,double *names,int first,int last,int length)
{
	int c;
	for(c=first;c<last;c++){
		double v=names[c-first];
//		print_matrix_double(names,length);
//		printf("%d\n",(int)v);
		int col=find_first_col(H,(int)v,length);
		H[(int)v][col]=id;
	}
		
}
/* [pos, EP1, EP2] = FC(new_P); */
int FC(double **B,int *pos,double *EP1,double *EP2,int length,int row,int column)
{
	int n=length;
	int edge=edge_matrix_double(B,row,column);
	int *i=init_matrix(edge);
	int *j=init_matrix(edge);
	double *V=init_matrix_double(edge);
	find_double(B,i,j,V,edge,row,column);
	int NNZ=edge;
	if(n<=0){
		*pos=1;
		*EP1=1.0;
		*EP2=1.0;
		return DONE;
	}
	double *S1=init_matrix_double(n);
	double *T1=init_matrix_double(n);
	int r;
	for(r=0;r<NNZ;r++){
		int x=i[r];
		int y=j[r];
		double w=V[r];
		if(y<=x)
			S1[x]+=w;
		else
			S1[y]+=w;
	}
	for(r=1;r<n;r++){
		S1[r]=S1[r-1]+S1[r];
		T1[r]=S1[r]/r;
	}
	double *T1_copy=init_matrix_double(n-1);
	copy_matrix_double(T1,T1_copy,0,n-1,0);
	T1=init_matrix_double(n-1);
	copy_matrix_double(T1_copy,T1,0,n-1,0);
	free_matrix_double(T1_copy);
	double *S2=init_matrix_double(n);
	double *T2=init_matrix_double(n);
	for(r=NNZ-1;r>=0;r--){
		int x=i[r];
		int y=j[r];
		double w=V[r];
		if(y<=x)
			S2[y]+=w;
		else
			S2[x]+=w;
	}
	for(r=n-2;r>=0;r--){
		S2[r]=S2[r+1]+S2[r];
		T2[r]=S2[r]/(n-r+1);
	}
	double *T2_copy=init_matrix_double(n-1);
	copy_matrix_double(T2,T2_copy,1,n,0);
	T2=init_matrix_double(n-1);
	copy_matrix_double(T2_copy,T2,0,n-1,0);
	free_matrix_double(T2_copy);
	double *E1=init_matrix_double(n-1);
	double *E2=init_matrix_double(n-1);
	for(*pos=0;*pos<n-1;(*pos)++){
		E1[*pos]=1-T1[*pos];
		E2[*pos]=1-T2[*pos];
	}
	
	double *Pcut=init_matrix_double(n-1);
	for(*pos=0;*pos<n-1;(*pos)++)
		Pcut[*pos]=2-T1[*pos]-T2[*pos];
	
	double pcut;
	*pos=min_double(Pcut,&pcut,n-1);
	*EP1=1-T1[*pos];
	*EP2=1-T2[*pos];
	
	free_matrix(i);
	free_matrix(j);
	free_matrix_double(V);
	free_matrix_double(S1);
	free_matrix_double(T1);
	free_matrix_double(S2);
	free_matrix_double(T2);
	free_matrix_double(E1);
	free_matrix_double(E2);
	free_matrix_double(Pcut);
	return DONE;
}

/* function [pos, EP1, EP2, new_W, new_W_names]= PL(W,W_names,error) */
void PL(double **W,double *W_names,double error,int *pos,double *EP1,double *EP2,double **new_W,double *new_W_names,int length,int edge,int row,int column)
{
	int n=length;
	int *i=init_matrix(edge);
	int *j=init_matrix(edge);
	double *v=init_matrix_double(edge);
	find_double(W,i,j,v,edge,row,column);
	int NNZ=edge;
	double *D=init_matrix_double(n);
	int r;
	for(r=0;r<NNZ;r++)
		D[i[r]]+=v[r];
		
	double **p=init_2_matrix_double(row,column);
	copy_2_matrix_double(W,p,row,column);
	for(r=0;r<NNZ;r++){
		int x=i[r];
		int y=j[r];
		double w=v[r];
		if(D[x]!=0)
			p[x][y]=w*1.0/D[x];
	}
	double *s_D=init_matrix_double(n);
	int *IX=sort_double(D,s_D,n);
	int sink=IX[n-1];
	double pi_pink=D[sink]*1.0/sum_1_double(D,n);
	double *R0=init_matrix_double(n);
	R0[sink]=1.0;
	
	double *R1=init_matrix_double(n);
	copy_matrix_double(R0,R1,0,n,0);
	double err=1.0;
	int steps=0;
	
	while(err>error&&steps<1000){
		double *S=init_matrix_double(n);
		int r;
		for(r=0;r<NNZ;r++)
			S[i[r]]+=R0[j[r]]*v[r];
		
		for(r=0;r<n;r++){
			if(D[r]!=0)
				R1[r]=S[r]*1.0/D[r];
			else
				R1[r]=0.0;
		}
		
		double *tmp=init_matrix_double(n);
		for(r=0;r<n;r++)
			tmp[r]=fabs(R1[r]-R0[r]);
		err=sum_1_double(tmp,n);
		steps++;
		copy_matrix_double(R1,R0,0,n,0);
		free_matrix_double(S);
		free_matrix_double(tmp);
	}
	double *SR=init_matrix_double(n);
	int *IX2=sort_double(R1,SR,n);
	
	int *flection=init_matrix(n);
	for(r=0;r<n;r++){
		flection[IX2[r]]=r;
		new_W_names[r]=W_names[IX2[r]];
	}
	
	double **new_P=init_2_matrix_double(n,n);
	int *i1=init_matrix(edge_matrix_double(p,row,column));
	int *j1=init_matrix(edge_matrix_double(p,row,column));
	double *VP=init_matrix_double(edge_matrix_double(p,row,column));
	find_double(p,i1,j1,VP,edge_matrix_double(p,row,column),row,column);
	for(r=0;r<NNZ;r++){
	 	int x=flection[i[r]];
		int y=flection[j[r]];
		new_W[x][y]=v[r];
		new_P[x][y]=VP[r];
	}
	FC(new_P,pos,EP1,EP2,n,n,n);
	
	free_matrix(i);
	free_matrix(j);
	free_matrix_double(v);
	free_matrix_double(D);
	free_2_matrix_double(p,row);
	free_matrix_double(s_D);
	free_matrix(IX);
	free_matrix_double(R0);
	free_matrix_double(R1);
	free_matrix_double(SR);
	free_matrix(IX2);
	free_matrix(flection);
	free_matrix(i1);
	free_matrix(j1);
	free_matrix_double(VP);
}

/* [new_W,new_W_names,H,id] = NCMA(W,W_names,H,id,err); */
void NCMA(double **W,double *W_names,int **H,int *id,double err,double **new_W,double *new_W_names,int edge,int row,int column)
{
	int pos=0;double EP1=0.0;double EP2=0.0;
	int n=MAX(row,column);
	PL(W,W_names,err,&pos,&EP1,&EP2,new_W,new_W_names,n,edge,row,column);
	printf("%d %f %f\n",pos,EP1,EP2);
	if(EP1<0.5&&EP2<0.5){
		double **W_A=init_2_matrix_double(pos,pos);
		copy_2_matrix_double_scope(new_W,W_A,0,0,pos,pos,0,0);
		double *W_A_names=init_matrix_double(pos);
		copy_matrix_double(new_W_names,W_A_names,0,pos,0);
		
		makeH(H,*id,W_A_names,0,pos,n);
		(*id)++;
		if(pos>0){
			NCMA(W_A,W_A_names,H,id,err,W_A,W_A_names,edge_matrix_double(W_A,pos,pos),pos,pos);printf("1\n");
		}
		double **W_B=init_2_matrix_double(n-pos,n-pos);
		copy_2_matrix_double_scope(new_W,W_B,pos,pos,n,n,0,0);
		double *W_B_names=init_matrix_double(n-pos);
		copy_matrix_double(new_W_names,W_B_names,pos,n,0);
		makeH(H,*id,W_B_names,pos,n,n);
//		print_2_matrix(H,n,n);
		(*id)++;
		if(n-pos>0){
			NCMA(W_B,W_B_names,H,id,err,W_B,W_B_names,edge_matrix_double(W_B,n-pos,n-pos),n-pos,n-pos);printf("2\n");
		}
		copy_2_matrix_double_scope(W_A,new_W,0,0,pos,pos,0,0);
		copy_2_matrix_double_scope(W_B,new_W,0,0,n-pos,n-pos,pos,pos);
		
		copy_matrix_double(W_A_names,new_W_names,0,pos,0);
		copy_matrix_double(W_B_names,new_W_names,pos,n,pos);
		
		free_2_matrix_double(W_A,pos);
		free_2_matrix_double(W_B,n-pos);
		free_matrix_double(W_A_names);
		free_matrix_double(W_B_names);
	}		
}

void fec(double **adj,int row,int column,int edge)
{
	int n=MAX(row,column);//length(W)
	double err=pow(0.1,7);
	int **H=init_2_matrix(n,n);
	int id=0;
	edge*=2;
	int c;
	double *W_names=init_matrix_double(n);
	for(c=0;c<n;c++)
		W_names[c]=c*1.0;
	double **new_W=init_2_matrix_double(n,n);
	double *new_W_names=init_matrix_double(n);
	NCMA(adj,W_names,H,&id,err,new_W,new_W_names,edge,row,column);
	print_2_matrix(H,n,n);
	
	free_matrix_double(W_names);
	free_matrix_double(new_W_names);
	free_2_matrix_double(new_W,n);
	free_2_matrix(H,n);
//	print_2_matrix_double(new_W,n,n);
	
}

int main(int argc,char *argv[])
{
	struct network_double network;
	if(loadmatrix_double(argv[1],&network)){
		fec(network.adj,network.row,network.column,network.edge);
		free_2_matrix_double(network.adj,network.row);
	}
	return 0;
}


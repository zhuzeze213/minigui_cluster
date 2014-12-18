#include <stdio.h>
#include "mystd.h"

int main(void)
{
	struct network_double network;
	double **map=loadmatrix_double("karate.txt",&network);
	print_2_matrix_double(map,network.node,network.node);
	double *b=init_matrix_double(10);
	
	copy_matrix_double(map[0],&b,0,5);
	print_matrix_double(b,5);
	
	
	int edge=edge_matrix_double(map,network.node,network.node);
	printf("%d \n",edge);
	double **d=init_2_matrix_double(3,3);
	copy_2_matrix_double_scope(map,&d,0,0,3,3);
	print_2_matrix_double(d,3,3);
	
	int *r=init_matrix(edge);
	int *co=init_matrix(edge);
	double *v=init_matrix_double(edge);
	find_double(map,&r,&co,&v,edge,network.row,network.column);
	print_matrix(r,edge);
	print_matrix(co,edge);
	print_matrix_double(v,edge);
	
	double *A=init_matrix_double(3);
	A[0]=0.1;A[1]=0.05;A[2]=0.15;
	double *s_D=init_matrix_double(3);
	int *index;
	index=sort_double(A,&s_D,3);
	print_matrix_double(s_D,3);
	print_matrix(index,3);
	print_matrix_double(A,3);
	
	int node=network.node;
	
	double sum=sum_1_double(map[0],node);
	printf("%f \n",sum);
	
	double min;
	int minindex=min_double(map[0],&min,node);
	printf("%d %f\n",minindex,min);
	
	return 0;
}

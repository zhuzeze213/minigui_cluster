#include "matlab.h"

int main(void)
{
	struct network network;
	if(loadmatrix("karate.txt",&network)){
/*		srand((unsigned int)time(NULL));
		int node=network.node;
		int *sum1=sum(network.adj,1,node,node);
		int *sum2=sum(network.adj,2,node,node);
		int i=0;
		for(i=0;i<node;i++)
			printf("%d ",sum1[i]);
		printf("\n");
		for(i=0;i<node;i++)
                        printf("%d ",sum2[i]);
		printf("\n");
		int *sum3=row_num(network.adj,2,node,node);
		int *sum4=column_num(network.adj,3,node,node);
		                for(i=0;i<node;i++)
                        printf("%d ",sum3[i]);
                printf("\n");
                for(i=0;i<node;i++)
                        printf("%d ",sum4[i]);
                printf("\n");*/
		double **a=init_2_matrix_double(2,10);
		a[1][2]=0.2;
		free_2_matrix_double(&a,2);


	}
	return 0;
}

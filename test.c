#include "fcm.h"

int main(void)
{
	struct network network;
	if(loadmatrix("karate.txt",&network)){
		srand((unsigned int)time(NULL));
		int node=network.node;
		int **a=transposition(network.adj,2,4);
		int i,j;
		for(i=0;i<4;i++){
			for(j=0;j<2;j++)
				printf("%d ",a[i][j]);
		printf("\n");
		}
		int v[3]={1,2,3};
		int **b=create_diag(v,3,-2);
		                for(i=0;i<5;i++){
                        for(j=0;j<5;j++)
                                printf("%d ",b[i][j]);
		printf("\n");
			}
		fcm(network.adj,2,fcm_option,node,node);
	}
	return 0;
}

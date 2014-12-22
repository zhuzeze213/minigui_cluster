#include "mystd.h"

int *init_matrix(int num)
{
	int *adj=(int *)malloc(sizeof(int)*num);
	if(adj){
		int i;
		for(i=0;i<num;i++)
			adj[i]=0;
		return adj;
	}
	return NULL;
}

void free_matrix(int *matrix)
{
	free(matrix);
}

double *init_matrix_double(int num)
{
	double *adj=(double *)malloc(sizeof(double)*num);
	if(adj){
		int i;
		for(i=0;i<num;i++)
			adj[i]=0.0;
		return adj;
	}
	return NULL;
}

void free_matrix_double(double *matrix)
{
	free(matrix);
}

int **init_2_matrix(int row,int column)
{
	int **adj;
	int i=0,j=0;
	adj=(int **)malloc(row*sizeof(int *));
	
	if(adj){
		for(i=0;i<row;i++){
			adj[i]=(int *)malloc(column*sizeof(int));
			if(!adj[i]){
				printf("memory alloc error\n");
				return NULL;
			}
		}
	}
	else{
		printf("memory alloc error\n");
		return NULL;
	}
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			adj[i][j]=0;
	
	return adj;
}

void free_2_matrix(int **matrix,int row)
{
	int i;
	for(i=0;i<row;i++)
		free(matrix[i]);
	free(matrix);

}

double **init_2_matrix_double(int row,int column)
{
	double **adj;
	int i=0,j=0;
	adj=(double **)malloc(row*sizeof(double *));
	
	if(adj){
		for(i=0;i<row;i++){
			adj[i]=(double *)malloc(column*sizeof(double));
			if(!adj[i]){
				printf("memory alloc error\n");
				return NULL;
			}
		}
	}
	else{
		printf("memory alloc error\n");
		return NULL;
	}
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			adj[i][j]=0.0;
	
	return adj;
}

void free_2_matrix_double(double **matrix,int row)
{
	int i;
	for(i=0;i<row;i++)
		free(matrix[i]);
	free(matrix);
}

void print_matrix(int *adj,int length)
{
	int i;
	if(!adj) printf("adj is null\n");
    for(i=0;i<length;i++)
        printf("%d ",adj[i]);
    printf("\n\n");
}

void print_matrix_double(double *adj,int length)
{
	int i;
	if(!adj) printf("adj is null\n");
	for(i=0;i<length;i++)
		printf("%f ",adj[i]);
	printf("\n\n");
}

void print_2_matrix(int **adj,int row,int column)
{
	int i,j;
	if(!adj) printf("adj is null\n");
	for(i=0;i<row;i++){
		for(j=0;j<column;j++)
			printf("%d ",adj[i][j]);
		printf("\n");
	}
	printf("\n");
}

void print_2_matrix_double(double **adj,int row,int column)
{
	int i,j;
	if(!adj) printf("adj is null\n");
	for(i=0;i<row;i++){
		for(j=0;j<column;j++)
			printf("%f ",adj[i][j]);
		printf("\n");
	}
	printf("\n");
}
int init_network(struct network *network,int row,int column,int node,int edge,BOOL direct,BOOL power)
{
	if(network){
		network->row=row;
		network->column=column;
		network->node=node;
		network->edge=edge;
		network->direct=direct;
		network->power=power;
		return DONE;
	}
	else
		return ERROR; 
}



int copy_matrix(int *old,int *new,int start,int end,int start2)
{
	if(old&&new){
		int i,j=start2;
		for(i=start;i<end;i++){
			new[j]=old[i];
			j++;
		}
		return DONE;
	}
	return ERROR;
}

int copy_matrix_double(double *old,double *new,int start,int end,int start2)
{
	if(old&&new){
		int i,j=start2;
		for(i=start;i<end;i++){
			new[j]=old[i];
			j++;
		}
		return DONE;
	}
	return ERROR;
}

/* int ** loadmatrix(char *filename) return the two demension matrix from the file 
it only use row=column matrix*/
int **loadmatrix(char *filename,struct network *network)
{
	if(!filename)
		return NULL;
	FILE *fp;
	if(fp=fopen(filename,"r"))
		printf("read the %s\n",filename);
	else{
		printf("read error\n");
		return NULL;
	}
	char tmp[BUFFERSIZE];
	int node=0;
	while(fgets(tmp,BUFFERSIZE,fp))
		node++;
	printf("almost %d nodes\n",node);
	fclose(fp);	
	int **adj=init_2_matrix(node,node);
	network->adj=init_2_matrix(node,node);
	
	
	fp=fopen(filename,"r");
	int c;
	int i=0,j=0;
	int count=node*node;
	while(count){
		c=fgetc(fp);	
		if(c=='0'){
			adj[i][j]=0;
			j++;
			count--;
		}
		else if(c=='1'){
			adj[i][j]=1;
			j++;
			count--;
		}
		else if(c=='\n'){
			i++;
			j=0;
			
		}
	}
	fclose(fp);
	if(copy_2_matrix(adj,network->adj,node,node)==ERROR)
		return NULL;
	
	int x,y;int edges=0;
	for(x=0;x<node;x++){
		for(y=0;y<node;y++){
			if(adj[x][y]>0)
				edges++;	
		}
	}
	edges/=2;
	printf("almost %d edges\n",edges);
	if(init_network(network,node,node,node,edges,NO_DIRECT,NO_POWER)==ERROR)
		return NULL;
	for(x=0;x<node;x++)
		free(adj[x]);
	free(adj);
	return network->adj;
}


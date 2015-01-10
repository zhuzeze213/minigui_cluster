#include "../include/mystd.h"

int K,Vectordim,datasize,seed=1;
float **data,**kmatrix;
float *max_column,*min_column;

float** array(int m, int n) 
{
	float **p;
	int i;
	p=(float**)malloc(m*sizeof(float*));
	p[0]=(float*)malloc(m*n*sizeof(float));
	for(i=1; i<m; ++i) p[i]=p[i-1]+n;
	return p;
}

void freearray(float** p)
{
	free(*p); 
	free(p);
}


double euclid_distance(float a[],float b[],int dim)
{
	int i;
	double sum=0;
	for(i=0;i<dim;i++)
		sum+=pow(a[i]-b[i],2);
	return sqrt(sum);
}

void getmaxmin(float **a)
{
	int i,j;
	max_column=(float *)malloc(sizeof(float)*Vectordim);
	min_column=(float *)malloc(sizeof(float)*Vectordim);
	
	for(i=0;i<Vectordim;i++){
		max_column[i]=a[0][i];
		min_column[i]=a[0][i];
	}
	
	for(i=0;i<Vectordim;i++){
		for(j=1;j<datasize;j++){
			if(a[j][i]>max_column[i])max_column[i]=a[j][i];
			if(a[j][i]<min_column[i])min_column[i]=a[j][i];
		}
	}
}

void initializerandom()
{
	seed++;
	srand((unsigned) time(NULL)+seed);
}

float randomreal(float Low, float High)
{
	return ((float) rand() / RAND_MAX) * (High-Low) + Low;
}      

void K_locations_random()
{
	int i,j;
	kmatrix=array(K,Vectordim+1);
	printf("Randomly the K-locations are initialized as follows:\n");
	for(i=0;i<K;i++){
		initializerandom();
		kmatrix[i][Vectordim]=(float)(i+1);
		printf("location---%d:  ",i+1);
		for(j=0;j<Vectordim;j++){
			kmatrix[i][j]=randomreal(min_column[i],max_column[i]);
			printf("%f,   ",kmatrix[i][j]);
		}
		printf("\n");
	}
}

int existemptyclass()
{
	int *empty,i,j,ef;
	empty=(int *)malloc(sizeof(int)*K);
	for(i=0;i<K;i++) empty[i]=0;
	for(i=0;i<datasize;i++)
	{
		for(j=1;j<=K;j++)
		{
			if(j==(int)data[i][Vectordim]) empty[j-1]++;
		}
	}
	for(i=0,ef=0;i<K;i++) 
		if(0==empty[i]) ef=1;
	return ef;
}

int cluster()
{
	int i,j,flag,eflag=1;
	double closest,d;
	for(i=0;i<datasize;i++){
		closest=euclid_distance(data[i],kmatrix[0],Vectordim);
		flag=1;

		for(j=1;j<K;j++){
			d=euclid_distance(data[i],kmatrix[j],Vectordim);
			if(d<closest)  {closest=d;flag=j+1;}
		}
		if(data[i][Vectordim]!=(float)flag)  
			eflag=0;
		data[i][Vectordim]=(float)flag;
	}

	return eflag;
}

void update_k_location()
{
	int i,j,number,m;
	float *temp;
	temp=(float *)malloc(sizeof(float)*(Vectordim));
	for(m=0;m<Vectordim;m++) temp[m]=0;
	for(number=0,i=1;i<=K;i++){
		for(m=0;m<Vectordim;m++) 
			temp[m]=0;
		for(j=0;j<datasize;j++){
			if(data[j][Vectordim]==i){
				number++;
				for(m=0;m<Vectordim;m++){
					temp[m]+=data[j][m];
				}
		    }
		}
		for(m=0;m<Vectordim;m++)
		kmatrix[i-1][m]=temp[m]/number;
	}
	free(temp);
}

void output()
{
	int i,j,m;
	for(i=1;i<=K;i++){
		printf("The following data are clusterd as CLASS %d:\n",i);
		for(j=0;j<datasize;j++){
			if(data[j][Vectordim]==(float)i){
					printf("%d ",j);
			}		
		}
		printf("\n");
	}
}

void freememory()
{
	freearray(kmatrix);
	freearray(data);
	free(max_column);
	free(min_column);
}
void loaddata(char *filename)
{
	struct network network;
	loadmatrix(filename,&network);
	data=array(network.row,network.column+1);
	Vectordim=network.column;
	datasize=network.row;   
	int i,j;
	for(i=0;i<datasize;i++)
		for(j=0;j<Vectordim;j++)
			data[i][j]=(float)network.adj[i][j];
	for(i=0;i<datasize;i++)
		data[i][Vectordim]=0;
}
int main(int argc,char *argv[])
{
	int end_flag,empty_flag=0;
	long int time;
	K=atoi(argv[2]);
	loaddata(argv[1]);
	getmaxmin(data);
	while(1){
		K_locations_random();
		end_flag=cluster();
		if(existemptyclass()){
			printf("There is a empty class!\nSo restart!\n");
			continue;
		}
		time=0;
		while(!end_flag){
			if(time>1000)
				break;
		time++;
		update_k_location();
		end_flag=cluster();
		}
		empty_flag=existemptyclass();
		if(empty_flag) {printf("There is a empty class!\nSo restart!\n");continue;}
		else break;
	}
	printf("\nAfter %ld times calculation\n",time);
	output();
	freememory();
	return 0;
}

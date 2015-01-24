/* fuzzy cluster algorithm fcm main program       author:zhuyouze*/
#include "mystd.h"

double **distfcm(double **center,int **data,int cluster_n,int data_n)
{
	if(cluster_n>1){
		double **out=init_2_matrix_double(cluster_n,data_n);
		int k;int i,j;
		for(k=0;k<cluster_n;k++){
			double **center_mul=copy_double(center[k],data_n,data_n);
			double **data_center=matrix_operate_double_int_1(data,center_mul,'-',data_n,data_n);

			double **data_center_2=init_2_matrix_double(data_n,data_n);
			for(i=0;i<data_n;i++)
				for(j=0;j<data_n;j++)
					data_center_2[i][j]=pow(data_center[i][j],2);
			double **data_center_2_t=transposition_double(data_center_2,data_n,data_n);
			double *sum_data_center=sum_double(data_center_2_t,1,data_n,data_n);
			for(i=0;i<data_n;i++)
				out[k][i]=sqrt(sum_data_center[i]);
				
			free_2_matrix_double(&center_mul,data_n);
			free_2_matrix_double(&data_center,data_n);
			free_2_matrix_double(&data_center_2,data_n);
			free_2_matrix_double(&data_center_2_t,data_n);
			free_matrix_double(&sum_data_center);
		}
		return out;
	}
	return NULL;
}
void stepfcm(int **data,double ***U,int cluster_n,int expo,double ***center,double ***obj_fcn,int data_n,int count)
{
	int i,j,k;
	double **mf=init_2_matrix_double(cluster_n,data_n);
	for(i=0;i<cluster_n;i++)
		for(j=0;j<data_n;j++)
			mf[i][j]=pow((*U)[i][j],expo);
			
	double **mf_t=transposition_double(mf,cluster_n,data_n);//34*2
	double *mf_t_sum=sum_double(mf_t,1,data_n,cluster_n);//1*2

	double **tmp_copy=copy_double(mf_t_sum,data_n,cluster_n);//34*2
	double **tmp_copy_t=transposition_double(tmp_copy,data_n,cluster_n);//2*34
	
	double **mf_data=matrix_multiply_int_2(mf,data,cluster_n,data_n,data_n,data_n);//2*34
	double **center_tmp=matrix_operate_double(mf_data,tmp_copy_t,'/',cluster_n,data_n);
	copy_2_matrix_double(center_tmp,center,cluster_n,data_n);//
	
	double **dist=distfcm(*center,data,cluster_n,data_n);//

	double **dist_2=init_2_matrix_double(cluster_n,data_n);
	for(i=0;i<cluster_n;i++)
		for(j=0;j<data_n;j++)
			dist_2[i][j]=pow(dist[i][j],2);
	double **dist_mf=matrix_operate_double(dist_2,mf,'*',cluster_n,data_n);
	double *dist_sum=sum_double(dist_mf,1,cluster_n,data_n);
	for(i=0;i<data_n;i++)
		(*obj_fcn)[count][0]+=dist_sum[i];
	
	double **tmp=init_2_matrix_double(cluster_n,data_n);
	for(i=0;i<cluster_n;i++)
		for(j=0;j<data_n;j++)
			tmp[i][j]=pow(dist[i][j],-2/(expo-1));
	
	double **pri=ones_double(cluster_n,1);
	double *beh=sum_double(tmp,1,cluster_n,data_n);
	double **ones_sum=init_2_matrix_double(cluster_n,data_n);
	for(i=0;i<cluster_n;i++)
		for(j=0;j<data_n;j++)
			ones_sum[i][j]+=pri[i][0]*beh[j];
	double **U_new=matrix_operate_double(tmp,ones_sum,'/',cluster_n,data_n);
	copy_2_matrix_double(U_new,U,cluster_n,data_n);
	
	free_2_matrix_double(&mf,cluster_n);
	free_2_matrix_double(&mf_t,data_n);
	free_matrix_double(&mf_t_sum);
	free_2_matrix_double(&tmp_copy,data_n);
	free_2_matrix_double(&tmp_copy_t,cluster_n);
	free_2_matrix_double(&mf_data,cluster_n);
	free_2_matrix_double(&center_tmp,cluster_n);
	free_2_matrix_double(&dist,cluster_n);
	free_2_matrix_double(&dist_2,cluster_n);
	free_2_matrix_double(&dist_mf,cluster_n);
	free_matrix_double(&dist_sum);
	free_2_matrix_double(&tmp,cluster_n);
	free_2_matrix_double(&pri,cluster_n);
	free_matrix_double(&beh);
	free_2_matrix_double(&ones_sum,cluster_n);
	free_2_matrix_double(&U_new,cluster_n);
}

double **initfcm(int cluster_n,int data_n)
{
	double **U=rand_matlab(cluster_n,data_n);
	double *col_sum=sum_double(U,1,cluster_n,data_n);
	double **tmp=copy_double(col_sum,cluster_n,data_n);
	double **U2=matrix_operate_double(U,tmp,'/',cluster_n,data_n);
	
	free_2_matrix_double(&U,cluster_n);
	free_matrix_double(&col_sum);
	free_2_matrix_double(&tmp,cluster_n);
	return U2;
}
void fcm(int **data,int cluster_n,double options[],int row,int column)
{
	int data_n=row;
	int in_n=column;
	
	int expo=options[0];
	int max_iter=options[1];
	double min_impro=options[2];
	int display=options[3];
	
	double **obj_fcn=zeros_double(max_iter,1);
	double **U=initfcm(cluster_n,data_n);
	double **center=init_2_matrix_double(cluster_n,data_n);
	
	int i;
	for(i=0;i<max_iter;i++){
		stepfcm(data,&U,cluster_n,expo,&center,&obj_fcn,data_n,i);

		if(display)
			printf("%d iterations,obj_fcn=%f\n",i,obj_fcn[i][0]);
		if(i>0){
			if(fabs(obj_fcn[i][0]-obj_fcn[i-1][0])<min_impro)
				break;
		}
	}
	printf("\ncenter:\n");
	print_2_matrix_double(center,cluster_n,data_n);
	printf("\nU:\n");
	print_2_matrix_double(U,cluster_n,data_n);
	print_2_matrix_double_f(U,cluster_n,data_n,TMPFILE);
	int max_index=0;double max_num=0.0;int j;
	int *community=init_matrix(data_n);
	for(i=0;i<data_n;i++){
		for(j=0;j<cluster_n;j++){
			if(U[j][i]>max_num){
				max_index=j;
				max_num=U[j][i];
				community[i]=max_index;
			}
		}
		max_index=0;max_num=0.0;
	}
				
	
	printf("result:\n");
	for(i=0;i<data_n;i++){
		if(i%10==0)
			printf("\n");
		printf("%d ",community[i]+1);
	}
	printf("\n");
	
	free_2_matrix_double(&obj_fcn,max_iter);
	free_2_matrix_double(&U,cluster_n);
	free_2_matrix_double(&center,cluster_n);
	free_matrix(&community);
	
}

int main(int argc,char *argv[])
{
/*fcm() array number	
 default_options = [2;	% exponent for the partition matrix U
		100;	% max. number of iteration
		1e-5;	% min. amount of improvement
		1];	% info display during iteration 
*/
	double fcm_option[4]={2,100,0.00001,1};
	printf("matrix file:%s\n",argv[1]);
	struct network network;
	if(loadmatrix(argv[1],&network)){
		srand((unsigned int)time(NULL));
		int row=network.row;
		int column=network.column;
		fcm(network.adj,2,fcm_option,row,column);
	}
	return 0;
}

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

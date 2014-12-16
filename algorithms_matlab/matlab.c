#include "mystd.h"

#define RAND 0.1234567

/* Function option(int) return the number of array*/
double option(double fcm[],int num)
{
	if(fcm)
		return fcm[num-1];
	else return ERROR;
}

/*Function size(int ***adj,int num)  if num==1 return row,if num==2 return column*/
int size(int ***matrix,int num)
{
	if(matrix&&*matrix){
		if(num==1)
			return container_of(matrix,struct network,adj)->row;
		else if(num==2)
			return container_of(matrix,struct network,adj)->column;
		else
			return ERROR;
	}
	else
		return ERROR;
}

/* Function length(int ***adj) return the max between row and column */
int length(int ***matrix)
{
	if(matrix!=NULL){
		int row=container_of(matrix,struct network,adj)->row;
		int column=container_of(matrix,struct network,adj)->column;
		return MAX(row,column);
	}
	else
		return ERROR;
}

/*Function int *find(int *adj)return the index not equal with 0*/
int *find(int *matrix,int column)
{
	if(matrix){
		int *adj=init_matrix(column);
		if(adj){
			int index=0;int count=0;
			for(;index<column;index++){
				if(matrix[index]!=0){
					adj[count]=index;
					count++;
				}
			}
			return adj;
		}
	}
	return NULL;

}

int fill(int ***adj,int num,int row,int column)
{
	if(adj){
		int i,j;
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				(*adj)[i][j]=num;
		return DONE;
	}
	return ERROR;
}

int fill_double(double ***adj,double num,int row,int column) 
{
        if(adj){
                int i,j;
                for(i=0;i<row;i++){
                        for(j=0;j<column;j++){
							if(num==RAND)
								(*adj)[i][j]=(double)(rand()/(INT_MAX/1.0));
							else
								(*adj)[i][j]=num;
						}
				}
                return DONE;
        }
        return ERROR;
}

int **zeros(int row,int column)
{
	int **adj;
	if(adj=init_2_matrix(row,column)){
		if(fill(&adj,0,row,column)==DONE)
			return adj;
	}
	return NULL;
}

double **zeros_double(int row,int column)
{
	double **adj;
	if(adj=init_2_matrix_double(row,column)){
		if(fill_double(&adj,0.0,row,column)==DONE)
			return adj;
	}
	return NULL;
}

int **ones(int row,int column)
{
	int **adj;
	if(adj=init_2_matrix(row,column)){
		if(fill(&adj,1,row,column)==DONE)
			return adj;
	}
	return NULL;
}

double **ones_double(int row,int column)
{
	double **adj;
	if(adj=init_2_matrix_double(row,column)){
		if(fill_double(&adj,1.0,row,column)==DONE)
			return adj;
	}
	return NULL;
}

double **rand_matlab(int row,int column)
{
	double **adj;
	if(adj=init_2_matrix_double(row,column)){
		if(fill_double(&adj,RAND,row,column)==DONE)
			return adj;
	}
	return NULL;
}

/*Function sum(int **adj,int num,int row,int column) if num==1 return the sum of column num==2 return row*/
int *sum(int **adj,int num,int row,int column)
{
	if(num==1){
		int *ret=init_matrix(column);
		if(ret){
			int tmp_sum=0,i,j;
			for(i=0;i<column;i++)
				for(j=0;j<row;j++)
					ret[i]+=adj[j][i];
			return ret;
		}
		return NULL;
	}
	else if(num==2){
		int *ret=init_matrix(row);
		if(ret){
			int tmp_sum=0,i,j;
			for(i=0;i<row;i++)
				for(j=0;j<column;j++)
					ret[i]+=adj[i][j];
			return ret;
		}
		return NULL;
	}
	else
		return NULL;
}
double *sum_double(double **adj,int num,int row,int column)
{
	if(num==1){
		double *ret=init_matrix_double(column);
		if(ret){
			double tmp_sum=0;
			int i,j;
			for(i=0;i<column;i++)
				for(j=0;j<row;j++)
					ret[i]+=adj[j][i];
			return ret;
		}
		return NULL;
	}
	else if(num==2){
		double *ret=init_matrix_double(row);
		if(ret){
			double tmp_sum=0;
			int i,j;
			for(i=0;i<row;i++)
				for(j=0;j<column;j++)
					ret[i]+=adj[i][j];
			return ret;
		}
		return NULL;
	}
	else
		return NULL;
}
/*return the row you want */
int *row_num(int **adj,int num,int row,int column)
{
	if(num>=row)
		return NULL;
	int *ret=init_matrix(column);
	if(ret){
		int i;
		for(i=0;i<column;i++)
			ret[i]=adj[num][i];
		return ret;
	}
	return NULL;
}

/*return the column you want */
int *column_num(int **adj,int num,int row,int column)
{
	if(num>=column)
		return NULL;
	int *ret=init_matrix(row);
	if(ret){
		int i;
		for(i=0;i<row;i++)
			ret[i]=adj[i][num];
		return ret;
	}
	return NULL;
}

/*get matrix'	*/
int **transposition(int **matrix,int row,int column)
{
	int **adj;
	adj=init_2_matrix(column,row);
	if(adj){
		int i,j;
       		for(i=0;i<column;i++)
        		for(j=0;j<row;j++)
                		adj[i][j]=matrix[j][i];
		return adj;
	}
	return NULL;
			
}	

double **transposition_double(double **matrix,int row,int column)
{
	double **adj;
	adj=init_2_matrix_double(column,row);
	if(adj){
		int i,j;
       		for(i=0;i<column;i++)
        		for(j=0;j<row;j++)
                		adj[i][j]=matrix[j][i];
		return adj;
	}
	return NULL;	
}
/* n is *v size*/
int **create_diag(int *v,int n,int pos)
{
	if(pos>=0&&v){
		int column=pos+n;
		int row=pos+n;
		int **adj=init_2_matrix(row,column);
		int i=0,j=0;	
		i=0;j=pos;
		if(adj){
			for(i=0;i<n;i++){
				adj[i][j]=v[i];
				j++;
			}
			return adj;
		}
		else return NULL;
	}	
	else if(pos<0&&v){
		int column=-pos+n;
		int row=-pos+n;
		int **adj;
		int i=0,j=0;
		adj=init_2_matrix(row,column);
		i=-pos;j=0;
		if(adj){
			for(j=0;j<n;j++){
				adj[i][j]=v[j];
				i++;
			}
			return adj;
		}
		else return NULL;
	}
	else
		return NULL;
}

double **copy_double(double *old,int copy,int length)
{
	double **adj;
	int i=0,j=0;
	adj=init_2_matrix_double(copy,length);
	if(adj){
		for(i=0;i<copy;i++){
			for(j=0;j<length;j++)
				adj[i][j]=old[j];
		}
		return adj;
	}
	return NULL;
}
	
double **matrix_operate_double(double **pri,double **beh,char ope,int row,int column)
{
	int i,j;
	double **adj=init_2_matrix_double(row,column);
	switch(ope){
		case '+':{
			for(i=0;i<row;i++)
				for(j=0;j<column;j++)
						adj[i][j]=pri[i][j]+beh[i][j];
						
			break;
		}
		
		case '-':{
			for(i=0;i<row;i++)
				for(j=0;j<column;j++)
						adj[i][j]=pri[i][j]-beh[i][j];
						
			break;
		}
		
		case '*':{
			for(i=0;i<row;i++)
				for(j=0;j<column;j++)
						adj[i][j]=pri[i][j]*beh[i][j];
						
			break;
		}
		
		case '/':{
			for(i=0;i<row;i++)
				for(j=0;j<column;j++)
						adj[i][j]=pri[i][j]/beh[i][j];
						
			break;
		}
		
		default: return NULL;
	}	
		return adj;
}	

double **matrix_operate_double_int_1(int **pri,double **beh,char ope,int row,int column)
{
	int i,j;
	double **adj=init_2_matrix_double(row,column);
	switch(ope){
		case '+':{
			for(i=0;i<row;i++)
				for(j=0;j<column;j++)
						adj[i][j]=pri[i][j]+beh[i][j];
						
			break;
		}
		
		case '-':{
			for(i=0;i<row;i++)
				for(j=0;j<column;j++)
						adj[i][j]=pri[i][j]-beh[i][j];
						
			break;
		}
		
		case '*':{
			for(i=0;i<row;i++)
				for(j=0;j<column;j++)
						adj[i][j]=pri[i][j]*beh[i][j];
						
			break;
		}
		
		case '/':{
			for(i=0;i<row;i++)
				for(j=0;j<column;j++)
						adj[i][j]=pri[i][j]/beh[i][j];
						
			break;
		}
		
		default: return NULL;
	}	
		return adj;	
}

double **matrix_operate_double_int_2(double **pri,int **beh,char ope,int row,int column)
{
	int i,j;
	double **adj=init_2_matrix_double(row,column);
	switch(ope){
		case '+':{
			for(i=0;i<row;i++)
				for(j=0;j<column;j++)
						adj[i][j]=pri[i][j]+beh[i][j];
						
			break;
		}
		
		case '-':{
			for(i=0;i<row;i++)
				for(j=0;j<column;j++)
						adj[i][j]=pri[i][j]-beh[i][j];
						
			break;
		}
		
		case '*':{
			for(i=0;i<row;i++)
				for(j=0;j<column;j++)
						adj[i][j]=pri[i][j]*beh[i][j];
						
			break;
		}
		
		case '/':{
			for(i=0;i<row;i++)
				for(j=0;j<column;j++)
						adj[i][j]=pri[i][j]/beh[i][j];
						
			break;
		}
		
		default: return NULL;
	}	
		return adj;	
}
double **matrix_multiply(double **pri,double **beh,int row1,int column1,int row2,int column2)
{
	if(column1!=row2) return NULL;
	double **adj=init_2_matrix_double(row1,column2);
	if(adj){
		int i,j,k;
		for(i=0;i<row1;i++){
			for(j=0;j<column2;j++){
				for(k=0;k<row2;k++)
					adj[i][j]+=pri[i][k]*beh[k][j];
			}
		}
		return adj;
	}
	return NULL;
}	
	
double **matrix_multiply_int_2(double **pri,int **beh,int row1,int column1,int row2,int column2)
{
	if(column1!=row2) return NULL;
        double **adj=init_2_matrix_double(row1,column2);
        if(adj){
                int i,j,k;
                for(i=0;i<row1;i++){
                        for(j=0;j<column2;j++){
                                for(k=0;k<row2;k++)
                                        adj[i][j]+=pri[i][k]*beh[k][j];
                        }
                }
                return adj;
        }
        return NULL;
}
	

#include "../include/mystd.h"

#define RAND 0.1234567

/* Function option() return the number of array*/
double option(double fcm[],int num)
{
	if(fcm)
		return fcm[num-1];
	else return ERROR;
}

/*Function size(int ***adj,int num)  if num==1 return row,if num==2 return column.no use!
ATTENTION!it only use in **matrix has already embeded in the strucure network!*/
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

/* Function length(int ***adj) return the max between row and column no use!
ATTENTION!it only use in **matrix has already embeded in the strucure network!*/
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

/*return the index not equal with 0*/
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

/* fill the matrix with the parameter num*/
int fill(int **adj,int num,int row,int column)
{
	if(adj){
		int i,j;
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				adj[i][j]=num;
		return DONE;
	}
	return ERROR;
}

/* fill the matrix with the parameter num
if num==RAND,fill the matrix with the random number!*/
int fill_double(double **adj,double num,int row,int column) 
{
        if(adj){
                int i,j;
                for(i=0;i<row;i++){
                        for(j=0;j<column;j++){
							if(num==RAND)
								adj[i][j]=(double)(rand()/(INT_MAX/1.0));
							else
								adj[i][j]=num;
						}
				}
                return DONE;
        }
        return ERROR;
}

/* init the matrix and fill 0!*/
int **zeros(int row,int column)
{
	int **adj;
	if(adj=init_2_matrix(row,column)){
		if(fill(adj,0,row,column)==DONE)
			return adj;
	}
	return NULL;
}

double **zeros_double(int row,int column)
{
	double **adj;
	if(adj=init_2_matrix_double(row,column)){
		if(fill_double(adj,0.0,row,column)==DONE)
			return adj;
	}
	return NULL;
}

/* init the matrix and fill 1!*/
int **ones(int row,int column)
{
	int **adj;
	if(adj=init_2_matrix(row,column)){
		if(fill(adj,1,row,column)==DONE)
			return adj;
	}
	return NULL;
}

double **ones_double(int row,int column)
{
	double **adj;
	if(adj=init_2_matrix_double(row,column)){
		if(fill_double(adj,1.0,row,column)==DONE)
			return adj;
	}
	return NULL;
}

/* init the matrix and fill random numbers [0,1)!*/
double **rand_matlab(int row,int column)
{
	double **adj;
	if(adj=init_2_matrix_double(row,column)){
		if(fill_double(adj,RAND,row,column)==DONE)
			return adj;
	}
	return NULL;
}

/*if num==1 return the sum of column 
num==2 return row*/
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

double *row_num_double(double **adj,int num,int row,int column)
{
	if(num>=row)
		return NULL;
	double *ret=init_matrix_double(column);
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

/*get matrix'(transposition-matrix)	*/
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
/* n is *v size,pos is offset
for examle v=[1,2,3] create_diag(v,3,1) return the matrix
0 1 0 0
0 0 2 0
0 0 0 3
0 0 0 0 */
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

double **create_diag_double(double *v,int n,int pos)
{
	if(pos>=0&&v){
		int column=pos+n;
		int row=pos+n;
		double **adj=init_2_matrix_double(row,column);
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
		double **adj;
		int i=0,j=0;
		adj=init_2_matrix_double(row,column);
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

/* for example old[1,2,3] copy=2 return the matrix
1 2 3
1 2 3
*/
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

int **matrix_operate_double_int(int **pri,int **beh,char ope,int row,int column)
{
	int i,j;
	int **adj=init_2_matrix(row,column);
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
/* in matlab two matrix operate a.*b need the following function,only support +-/* */	
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

/*two matrix multiply a*b */
int **matrix_multiply_int(int **pri,int **beh,int row1,int column1,int row2,int column2)
{
	if(column1!=row2) return NULL;
	int **adj=init_2_matrix(row1,column2);
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

double **matrix_multiply_int_1(int **pri,double **beh,int row1,int column1,int row2,int column2)
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

/* return number is not 0 row index in *r,column index in *c,number in *v */
int find_int(int **adj,int *r,int *c,int *v,int edge,int row,int column)
{
	if(r&&c&&v){
		int i,j;int rc=0,cc=0,vc=0;
		for(i=0;i<row;i++){
			for(j=0;j<column;j++){
				if(adj[i][j]!=0){
					r[rc]=i;
					c[cc]=j;
					v[vc]=adj[i][j];
					rc++;cc++;vc++;
				}
			}
		}
		return DONE;
	}
	return ERROR;
}
int find_double(double **adj,int *r,int *c,double *v,int edge,int row,int column)
{
	if(r&&c&&v){
		int i,j;int rc=0,cc=0,vc=0;
		for(i=0;i<row;i++){
			for(j=0;j<column;j++){
				if(adj[i][j]!=0.0){
					r[rc]=i;
					c[cc]=j;
					v[vc]=adj[i][j];
					rc++;cc++;vc++;
				}
			}
		}
		return DONE;
	}
	return ERROR;
}
/* sort change to already sort array s_D and return the index array */
int *sort(int *D,int *s_D,int length)
{
	int *IX=init_matrix(length);
	int *D_copy=init_matrix(length);
	copy_matrix(D,D_copy,0,length,0);
	if(s_D&&IX){
		int i,j;int min=INT_MAX,minindex=-1;
		int sortc=0;
		for(i=0;i<length;i++){
			for(j=0;j<length;j++){
				if(D[j]<min){
					min=D[j];
					minindex=j;
				}
			}
			s_D[sortc]=min;
			IX[sortc]=minindex;
			sortc++;
			D[minindex]=INT_MAX;
			min=INT_MAX;minindex=-1;
		}
		copy_matrix(D_copy,D,0,length,0);
		free_matrix(D_copy);
		return IX;
	}
	return NULL;
			
}

int *sort_double(double *D,double *s_D,int length)
{
	int *IX=init_matrix(length);
	double *D_copy=init_matrix_double(length);
	copy_matrix_double(D,D_copy,0,length,0);
	if(s_D&&IX){
		int i,j;double min=INT_MAX*1.0;
		int minindex=-1;
		int sortc=0;
		for(i=0;i<length;i++){
			for(j=0;j<length;j++){
				if(D[j]<min){
					min=D[j];
					minindex=j;
				}
			}
			s_D[sortc]=min;
			IX[sortc]=minindex;
			sortc++;
			D[minindex]=INT_MAX*1.0;
			min=INT_MAX*1.0;minindex=-1;
		}
		copy_matrix_double(D_copy,D,0,length,0);
		free_matrix_double(D_copy);
		return IX;
	}
	return NULL;
			
}
/* return the sum of numbers in *D */
int sum_1(int *D,int length)
{
	if(!D) return ERROR;
	int i,sum=0;
	for(i=0;i<length;i++)
		sum+=D[i];
	return sum;
}

double sum_1_double(double *D,int length)
{
	if(!D) return ERROR;
	int i;
	double sum=0.0;
	for(i=0;i<length;i++)
		sum+=D[i];
	return sum;	
}

/*return 1 if all number equal in *a and *b*/
int equal_int_1(int *a,double *b,int length)
{
	int i;
	for(i=0;i<length;i++){
		double tmp=a[i]*1.0;
		if(tmp!=b[i])
			return 0;
	}
	return 1;
}

/* return the edge in **adj */
int edge_matrix_double(double **adj,int row,int column)
{
	if(!adj) return ERROR;
	int i,j;
	int edge=0;
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			if(adj[i][j]!=0.0)
				edge++;
		}
	}
	return edge;
}
/* find the minmum num and return the index */
int min_double(double *D,double *min,int length)
{
	if(!D) return ERROR;
	int i;
	int minindex=-1;
	*min=INT_MAX*1.0;
	for(i=0;i<length;i++){
		if(D[i]<*min){
			*min=D[i];
			minindex=i;
		}
	}
	return minindex;
	
}
/* return sum of diagonal*/
double trace(double **adj,int row)
{
	double sum=0.0;
	int i;
	for(i=0;i<row;i++)
		sum+=adj[i][i];
		
	return sum;
}

/* return the r_length is *adj include how many numbers is different,*r_adj include 
all numbers which is different*/
int *unique(int *adj,int length,int *r_length)
{
	if(!adj) return NULL;
	int *r_adj=init_matrix(length);
	r_adj[0]=adj[0];
	*r_length=1;
	int i,j;
	int symbol=0;
	for(i=1;i<length;i++){
		symbol=0;
		for(j=0;j<(*r_length);j++){
			if(r_adj[j]==adj[i])
				symbol=1;
			
		}
		if(!symbol){
			r_adj[*r_length]=adj[i];
			(*r_length)++;
		}
	}
	return r_adj;
}

static double getA(double **arcs,int n,int row,int column)
{
	if(n==1)
	{
		return arcs[0][0];
	}
	double ans = 0.0;
	double **temp=init_2_matrix_double(row,column);
	int i,j,k;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-1;j++)
		{
			for(k=0;k<n-1;k++)
			{
				temp[j][k] = arcs[j+1][(k>=i)?k+1:k];
				
			}
		}
		double t = getA(temp,n-1,row,column);
		if(i%2==0)
		{
			ans += arcs[0][i]*t;
		}
		else
		{
			ans -=  arcs[0][i]*t;
		}
	}
	free_2_matrix_double(temp,row);
	return ans;
}

/* return inverse matrix */
double **inv(int **adj,int row,int column)
{
	double **ans=init_2_matrix_double(row,column);
	int n=row;//*column;
	if(n==1)
	{
		ans[0][0] = 1.0;
		return ans;
	}
	int i,j,k,t;
	double **temp=init_2_matrix_double(row,column);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			for(k=0;k<n-1;k++)
			{
				for(t=0;t<n-1;t++)
				{
					temp[k][t] = adj[k>=i?k+1:k][t>=j?t+1:t]*1.0;
				}
			}

		
			ans[j][i]  =  getA(temp,n-1,row,column);
			if((i+j)%2 == 1)
			{
				ans[j][i] = - ans[j][i];
			}
		}
	}
	free_2_matrix_double(temp,row);
	return ans;
}

/* if num is in *adj return index */
int find_num(int *adj,int length,int num)
{
	int i;
	for(i=0;i<length;i++){
		if(adj[i]==num)
			return i;
	}
	return -1;
}
















	

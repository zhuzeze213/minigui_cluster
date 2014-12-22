#include "mystd.h"

double Calculate_Q(int **football,int **best_community,int Nnode,int col,int edges)
{
	double value_Q=0.0;
	int row=Nnode;
	int step_row_1=0;
	double edge_between[row][row];
	int i,j;
	for(i=0;i<row;i++)
		for(j=0;j<row;j++)
			edge_between[i][j]=0.0;
	while(step_row_1<row){
		int step_row_2=step_row_1;
		while(step_row_2<row){
			int len1=col;
			int step_col_1=0;
			while(step_col_1<len1){
				int step_col_2=0;
				int len2=col;
				while(step_col_2<len2){
					if(best_community[step_row_1][step_col_1]!=-1&&best_community[step_row_2][step_col_2]!=-1){
						if(football[best_community[step_row_1][step_col_1]][best_community[step_row_2][step_col_2]]==1)
							edge_between[step_row_1][step_row_2] = edge_between[step_row_1][step_row_2] + 1;
					}
					step_col_2++;
				}
				step_col_1++;
			}
			edge_between[step_row_2][step_row_1] = edge_between[step_row_1][step_row_2];
			if (step_row_2 == step_row_1)
				edge_between[step_row_1][step_row_2] = edge_between[step_row_1][step_row_2]/2;
			step_row_2++;
		}
		step_row_1++;
	}
	for(i=0;i<row;i++)
		for(j=0;j<row;j++)
			edge_between[i][j]=edge_between[i][j]/edges;
	int step_row=0;
	double e=0;
	double a[row];
	for(i=0;i<row;i++)
		a[i]=0.0;
	while(step_row<row){
		e+=edge_between[step_row][step_row];
		int step_col=0;
		while(step_col<row){
			a[step_col]+=edge_between[step_row][step_col];
			step_col++;
		}
		step_row++;
	}
	value_Q=e;
	step_row=0;
	while(step_row<row){
		value_Q=value_Q-a[step_row]*a[step_row];
		step_row++;
	}
	return value_Q;
}


void Get_Connected_Number(int **matrix,int vertices,int *communities_num,int **communities)
{
	int *visted=init_matrix(vertices);
	int vertex=0;
	*communities_num=-1;
	while(vertex<vertices){
		if(visted[vertex]==0){
			visted[vertex]=1;
			(*communities_num)++;
			int length=0;
			communities[*communities_num][length]=vertex;
			length++;
			int *queue=init_matrix(vertices);
			int que_in=0,que_out=0;
			queue[que_in]=vertex;
			que_in++;
			while(que_in-que_out>0){
				int v=queue[que_out];
				que_out++;
				int col=0;
				while(col<vertices){
					if(matrix[v][col]==1&&visted[col]==0){
						queue[que_in]=col;
						que_in++;
						visted[col]=1;
						communities[*communities_num][length]=col;
						length++;
					}
					col++;
				}
			}
		}
		vertex++;
	}
	
}

void G_N4(int **edges_array,int **tri_edges,int *number_per_row,int *tri_number,int vertices,int edges,double *deleted_edge,int *pos1,int *pos2,int *position)
{
	int source=0;
	double **edge_dependency=zeros_double(edges/2,3);
	
	while(source<vertices){
		double *vertex_dependency=init_matrix_double(vertices);
		int *distance=init_matrix(vertices);
		int i;
		for(i=0;i<vertices;i++)
			distance[i]--;
		int *weight=init_matrix(vertices);
		int *queue=init_matrix(vertices);
		
		int que_in=0,que_out=0;
		distance[source]=0;
		weight[source]=1;
		queue[que_in]=source;
		que_in++;
		
		int **edges_order=zeros(edges/2,2);
		i=0;
		while(que_in-que_out>0){
			int v=queue[que_out];
			que_out++;
			int step=0,pos=0;
			while(step<v){//!
				pos+=number_per_row[step];
				step++;
			}
			while(pos<edges&&edges_array[pos][0]==v){
				int w=edges_array[pos][1];
				if(distance[w]<0){
					queue[que_in]=w;
					que_in++;
					distance[w]=distance[v]+1;
				}
				if(distance[w]==distance[v]+1){
					weight[w]+=weight[v];
					edges_order[i][0]=v;
					edges_order[i][1]=w;
					i++;
				}
				pos++;
			}
		}
		
		i--;
		while(i>=0){
			int w=edges_order[i][1];
			while(i>=0&&edges_order[i][1]==w){
				int v=edges_order[i][0];
				double partialdependency=weight[v]/weight[w];
				partialdependency=partialdependency*(1+vertex_dependency[w]);
				vertex_dependency[v]+=partialdependency;
				int row_here=w;
				int col_here=v;
				if(w>v){
					row_here=v;
					col_here=w;
				}
				int row=0,place=0;
				while(row<row_here){//!
					place+=tri_number[row];
					row++;
				}
				while(place<edges/2&&tri_edges[place][1]!=col_here)
					place++;
				edge_dependency[place][2] = edge_dependency[place][2]+ partialdependency;
				edge_dependency[place][0] = row_here;
				edge_dependency[place][1] = col_here;
				i--;
			}
		}
		source++;
	}
	double max=edge_dependency[0][2];
	int step = 0;
	*position = 0;
	while(step < edges/2){
		if(edge_dependency[step][2] > max){
			*position = step;
			max = edge_dependency[step][2];
		}
		step = step + 1;
	}
	*pos1 = 0;
	*pos2 = 0;
	step = 0;
	double *temp=row_num_double(edge_dependency,*position,edges/2,3);
	while(step < edges){
		if(edges_array[step][0]==temp[0]&&edges_array[step][1]==temp[1])
			*pos1 = step;
		if(edges_array[step][0]==temp[1]&& edges_array[step][1] == temp[0])
			*pos2 = step;

		if(*pos1 > -1 && *pos2 > -1)
			break;
		step = step + 1;
	}
	deleted_edge = row_num_double(edge_dependency,*position,edges/2,3);
	
}

double GN(int **adj,int **best_community,int count,int row2,int edge)
{
	int vertices=row2;
	int edges=edge;
	double **deleted_edge=zeros_double(edges,3);
	int deleted_edge_number=0;
	int **community=init_2_matrix(count,vertices);//!
	int x,y;
	for(x=0;x<count;x++)
		for(y=0;y<vertices;y++)
			community[x][y]=-1;
	int **best_matrix=zeros(vertices,vertices);
	int *community_number=init_matrix(edges);
	
	int number_community=0;
	int k_max=0;
	double q_max=INT_MIN*1.0;
	int edges_copy=edges;
	int **edges_array=zeros(edges*2,2);
	int **tri_edges=zeros(edges,2);
	int *number_tri_row=init_matrix(vertices);
	int *number_row=init_matrix(vertices);
	int row=0,step=0,tri_step=0;
	
	while(row<vertices){
		int col=0;
		while(col<vertices){
			if(adj[row][col]==1){
				edges_array[step][0]=row;
				edges_array[step][1]=col;
				step++;
				if(col>row){
					number_tri_row[row]++;
					tri_edges[tri_step][0]=row;
					tri_edges[tri_step][1]=col;
					tri_step++;
				}
				number_row[row]++;
			}
			col++;
		}
		row++;
	}
	
	int num=0;
	
	while(edges>0&&num<count-1){//!
/* [temp,pos1,pos2,pos] = G_N4(edges_array,tri_edges,number_row,number_tri_row,vertices, edges*2);*/ 
		double *temp;
		int pos,pos1,pos2;
		G_N4(edges_array,tri_edges,number_row,number_tri_row,vertices, edges*2,temp,&pos,&pos1,&pos2);
		int i;
		for(i=0;i<3;i++)
			deleted_edge[deleted_edge_number][i]=temp[i];
		
		int **matrix=init_2_matrix(row2,row2);
		copy_2_matrix(adj,matrix,row2,row2);
		matrix[(int)temp[0]][(int)temp[1]]=0;
		matrix[(int)temp[1]][(int)temp[0]]=0;
		
		int min=(int)temp[0];
		if(min>(int)temp[1])
			min=(int)temp[1];
	
		number_tri_row[min]--;
		number_row[(int)temp[0]]--;
		number_row[(int)temp[1]]--;
		
		Get_Connected_Number(matrix,vertices,&num,community);
		community_number[deleted_edge_number]=num;
		if(num==count-1){
			number_community=num;
			double quantity=Calculate_Q(adj,community,vertices,vertices,edges_copy);
			if(quantity>q_max){
				q_max=quantity;
				copy_2_matrix(matrix,best_matrix,vertices,vertices);
				k_max=num;
				copy_2_matrix(community,best_community,count,vertices);
			}
		}
		deleted_edge_number++;
		edges--;
	}
	return q_max;
}

int main(int argc,char *argv[])
{
	struct network network;
	if(loadmatrix(argv[1],&network)){
		int count=atoi(argv[2]);
		int **best_community=init_2_matrix(count,network.node);
		GN(network.adj,best_community,count,network.row,network.edge);
		free_2_matrix(network.adj,network.row);
	}
	return 0;
}

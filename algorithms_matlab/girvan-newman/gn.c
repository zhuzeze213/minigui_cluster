#include "mystd.h"

void G_N4(int **edges_array,int **tri_edges,int *number_per_row,int *tri_number,int vertices,int edges,double *deleted_edge,int *pos1,int *pos2,int *position)
{
	int source=0;
	double **edge_dependency=zeros(edges/2,3);
	
	while(source<vertices){
		double *vertex_dependency=init_matrix(vertices);
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
			while(step<v-1){//!
				pos+=number_per_row[step];
				step++;
			}
			while(pos<edges&&edges_array[pos,0]==v){
				int w=edges_array(pos,1);
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
				while(row<row_here-1){//!
					place+=tri_number[row];
					row++;
				}
				while(place<edges/2&&tri_edges[place][1]!=col_here)
					place++;
				edge_dependency[place][2] = edge_dependency(place, 3) + partialdependency;
				edge_dependency[place][0] = row_here;
				edge_dependency[place][1] = col_here;
				i--;
			}
		}
		source++;
	}
	double max=edge_dependency[0][2];
	step = 0;
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
	double *tmp=row_num_double(edge_dependency,*position,edges/2,3);
	while(step < edges){
		if(sum_1(edges_array[step])==1&&equal_int_1(edges_array[step],tmp,2))
			*pos1 = step;
		if(edges_array[step][0]==temp[1]&& edges_array[step][1] == temp(0))
			*pos2 = step;

		if(*pos1 > -1 && pos2 > -1)
			break;
		step = step + 1;
	}
	deleted_edge = row_num_double(edge_dependency,*position,edges/2,3);
	
}

double GN(int **adj,int **best_community,int count,int row,int edge)
{
	int vertices=row;
	int edges=edge;
	int **deleted_edge=zeros(edges,3);
	int deleted_edge_number=0;
	int *community=init_matrix(vertices);
	int **best_matrix=zeros(vertices,vertices);
	int *community_number=init_matrix(edges);
	
	int number_community=0;
	double k_max=0.0;
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}


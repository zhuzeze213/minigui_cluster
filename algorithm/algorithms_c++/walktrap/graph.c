#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int small(Edge E1,Edge E2)
{
	return(E1.neighbor < E2.neighbor);
}

void __initv(struct Vertex *v)
{
	v->degree=0;
	v->edges=0;
	v->total_weight=0.0;
}

void __destroyv(struct Vertex *v)
{
	if(v->edges)
		free(v->edges);
}

void initv(struct Vertex *v)
{
	v->initv=__initv;
	v->destroyv=__destroyv;
	v->initv(v);
}

void __initg(struct Graph *g)
{
	g->nb_vertices = 0;
	g->nb_edges = 0;
	g->vertices = 0;
	g->index = 0;
	g->total_weight = 0.;
}

void __destroyg(struct Graph *g)
{
	if(g->vertices)
		free(g->vertices);
}

struct Edge_list
{
	int *V1;
	int *V2;
	float *W;
	int size;
	int size_max;
	void(*add)(struct Edge_list *E,int v1,int v2,float w);
	void (*inite)(struct Edge_list *E);
	void (*destroye)(struct Edge_list *E);
};

void __inite(struct Edge_list *E)
{
	E->size = 0;
    E->size_max = 1024;
    E->V1 =(int *)malloc(1024*sizeof(int));
    E->V2 =(int *)malloc(1024*sizeof(int));
    E->W =(float *)malloc(1024*sizeof(float));
}
void __destroye(struct Edge_list *E)
{
	if(E->V1) free(E->V1);
	if(E->V2) free(E->V2);
	if(E->W) free(E->W);
}

void __add(struct Edge_list *E,int v1,int v2,float w)
{
	if(E->size==E->size_max){
		int *tmp1=(int *)malloc(2*E->size_max*sizeof(int));
		int *tmp2=(int *)malloc(2*E->size_max*sizeof(int));
		float *tmp3=(float *)malloc(2*E->size_max*sizeof(float));
		int i;
		for(i=0;i<E->size_max;i++){
			tmp1[i] = E->V1[i];
			tmp2[i] = E->V2[i];      
			tmp3[i] = E->W[i];
		}
		free(E->V1);
		free(E->V2);
		free(E->W);
		E->V1=tmp1;
		E->V2=tmp2;
		E->W=tmp3;
		E->size_max*=2;
	}
	E->V1[E->size]=v1;
    E->V2[E->size]=v2;
    E->W[E->size]=w;
	(E->size)++;
}

void inite(struct Edge_list *E)
{
	E->add=__add;
	E->inite=__inite;
	E->destroye=__destroye;
	E->inite(E);
}

void sort(Edge *edges,int length)
{
	int i,j,temp1;float temp2;
	for(i=0;i<=length-1;i++){
		for(j=0;j<length-1-i;j++){
			if(edges[j].neighbor>edges[j+1].neighbor){
				temp1=edges[j].neighbor;
				edges[j].neighbor=edges[j+1].neighbor;
				edges[j+1]=temp1;
				temp2=edges[j].weight;
				edges[j].weight=edges[j+1].weight;
				edges[j+1].weight=temp2;
			}
		}
	}
}

void in2G(File *fp,Graph *G)
{
	if(G->vertices) free(G->vertices);
	int nb_line=0;
	int max_vertex=0;
	Edge_list EL;
	inite(&EL);
	int v1,v2;float w;
	while(fscanf(fp,"%d %d %f",&v1,&v2,&w)==3&&v1>=0&&v2>=0&&f>0){
		if(v1>max_vertex) max_vertex=v1;
		if(v2>max_vertex) max_vertex=v2;
		EL.add(&EL,v1,v2,w);
	}
	G->nb_vertices=max_vertex+1;
	G->vertices=(Vertex *)malloc(G->nb_vertices*sizeof(Vertex));
	G->nb_edges=0;
	G->total_weight=0.0;
	
	for(int i = 0; i < EL.size; i++) {
		G->vertices[EL.V1[i]].degree++;
		G->vertices[EL.V2[i]].degree++;
		G->vertices[EL.V1[i]].total_weight += EL.W[i];
		G->vertices[EL.V2[i]].total_weight += EL.W[i];
		G->nb_edges++;
		G->total_weight += EL.W[i];
    }
	
	for(int i = 0; i < G->nb_vertices; i++) {
		if(G->vertices[i].degree == 0) {
			exit(0);
		}
		G->vertices[i].edges = (Edge *)malloc(sizeof(Edge)*(G->vertices[i].degree + 1));
		G->vertices[i].edges[0].neighbor = i;
		G->vertices[i].edges[0].weight = G->vertices[i].total_weight/(double)(G->vertices[i].degree);
		G->vertices[i].total_weight+= G->vertices[i].total_weight/(double)(G->vertices[i].degree);
		G->vertices[i].degree = 1;
	}
	for(int i = 0; i < EL.size; i++) {
		G->vertices[EL.V1[i]].edges[G->vertices[EL.V1[i]].degree].neighbor = EL.V2[i];
		G->vertices[EL.V1[i]].edges[G->vertices[EL.V1[i]].degree].weight = EL.W[i];
		G->vertices[EL.V1[i]].degree++;
		G->vertices[EL.V2[i]].edges[G->vertices[EL.V2[i]].degree].neighbor = EL.V1[i];
		G->vertices[EL.V2[i]].edges[G->vertices[EL.V2[i]].degree].weight = EL.W[i];
		G->vertices[EL.V2[i]].degree++;
	}  
  
	for(int i = 0; i < G.nb_vertices; i++)
		sort(G.vertices[i].edges, G.vertices[i].degree);

	for(int i = 0; i < G.nb_vertices; i++) {  // merge multi edges
		int a = 0;
		for(int b = 1; b < G.vertices[i].degree; b++) {
			if(G.vertices[i].edges[b].neighbor == G.vertices[i].edges[a].neighbor)
				G.vertices[i].edges[a].weight += G.vertices[i].edges[b].weight;
			else 
				G.vertices[i].edges[++a] = G.vertices[i].edges[b];
		}
		G.vertices[i].degree = a+1;
	}
}

long memory(struct Graph g)
{
	long m = 0;
	m += g.nb_vertices*sizeof(struct Vertex);
	m += 2*g.nb_edges*sizeof(struct Edge);
	m += sizeof(struct Graph);
	if(g.index != 0) {
		m += g.nb_vertices*sizeof(char*);
		for(int i = 0; i < g.nb_vertices; i++)
		m += strlen(g.index[i]) + 1;
	}
	return m;
}

bool load_index(char *input_file,struct Graph *g)
{
	File *fp=fopen(input_file,"r");
	if(fp){
		in2G(fp,g);
		return true;
	}
	return false;
}

void initg(struct Graph *g)
{
	g->initg=__initg;
	g->destroyg=__destroyg;
	g->memory=memory;
	g->load_index=load_index;
	g->initg(g);
}




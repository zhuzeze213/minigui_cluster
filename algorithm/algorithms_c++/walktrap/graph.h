#ifndef GRAPH_H
#define GRAPH_H

#include<stdio.h>
#define bool int
#define false 0
#define true 1
struct Edge
{
	int neighbor;
	float weight;
};

int small(Edge E1,Edge E2);

struct Vertex
{
	Edge *edges;
	int degree;
	float total_weight;
	void (*initv)(struct Vertex *v);
	void (*destroyv)(struct Vertex *v);
};

struct Graph
{
	int nb_vertices;
	int nb_edges;
	float total_weight;
	Vertex *vertices;
	
	long (*memory)(struct Graph g);
	char **index;
	bool (*load_index)(char *input_file,struct Graph *g);
	void (*initg)(struct Graph *g);
	void (*destroyg)(struct Graph *g);
};

File *in2G(File *fp,Graph *G);

#endif







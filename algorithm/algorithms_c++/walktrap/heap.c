#include "heap.h"
#include<stdlib.h>
#include<stdio.h>

void move_up(struct Neighbor_heap *n,int index)
{
	while(n->H[index/2]->delta_sigma > n->H[index]->delta_sigma) {
		Neighbor* tmp = n->H[index/2];
		n->H[index]->heap_index = index/2;
		n->H[index/2] = n->H[index];
		tmp->heap_index = index;
		n->H[index] = tmp;
		index = index/2;
	}
}

void move_down(struct Neighbor_heap *n,int index)
{
	while(true) {
		int min = index;
		if((2*index < n->size) && (n->H[2*index]->delta_sigma < n->H[min]->delta_sigma))
			min = 2*index;
		if(2*index+1 < n->size && n->H[2*index+1]->delta_sigma < n->H[min]->delta_sigma)
			min = 2*index+1;
		if(min != index) {
			Neighbor* tmp = n->H[min];
			n->H[index]->heap_index = min;
			n->H[min] = n->H[index];
			tmp->heap_index = index;
			n->H[index] = tmp;
			index = min;
		}
		else break;
	}
}

struct Neighbor* get_first(struct Neighbor_heap *n)
{
	if(n->size==0) return 0;
	else return n->H[0];
}

void remove(struct Neighbor_heap *n,struct Neighbor* N)
{
	if(N->heap_index == -1 || n->size == 0) return;
	Neighbor* last_N = n->H[--size];
	n->H[N->heap_index] = last_N;
	last_N->heap_index = N->heap_index;
	move_up(last_N->heap_index);
	move_down(last_N->heap_index);  
	N->heap_index = -1;
}

void add(struct Neighbor_heap *n,struct Neighbor* N)
{
	if(n->size >= max_size) return;
    N->heap_index = (n->size)++;
    n->H[N->heap_index] = N;
	move_up(N->heap_index);
}

void update(struct Neighbor_heap *n,struct Neighbor* N)
{
	if(N->heap_index == -1) return;
	move_up(N->heap_index);
	move_down(N->heap_index);
}

long memory(struct Neighbor_heap n)
{
	return (sizeof(struct Neighbor_heap) + long(n.max_size)*sizeof(struct Neighbor *));
}

void __initnh(struct Neighbor_heap *n,int max_s)
{
	n->max_size = max_s;
	n->size = 0;
	n->H = (struct Neighbor **)malloc(max_s*sizeof(struct Neighbor *));
}

void __destroy(struct Neighbor_heap *n)
{
	free(n->H);
}

bool is_empty(struct Neighbor_heap n)
{
	return(n.size==0);
}

//################################################













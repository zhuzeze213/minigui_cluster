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
void move_up(struct Min_delta_sigma_heap *m,int index)
{
	while(m->delta_sigma[m->H[index/2]] < delta_sigma[m->H[index]]) {
		int tmp = m->H[index/2];
		m->I[m->H[index]] = index/2;
		m->H[index/2] = m->H[index];
		m->I[tmp] = index;
		m->H[index] = tmp;
		index = index/2;
	}	
}

void move_down(struct Min_delta_sigma_heap *m,int index)
{
	while(true) {
		int max = index;
		if(2*index < m->size && m->delta_sigma[m->H[2*index]] > m->delta_sigma[m->H[max]])
			max = 2*index;
		if(2*index+1 < m->size && m->delta_sigma[m->H[2*index+1]] > m->delta_sigma[m->H[max]])
			max = 2*index+1;
		if(max != index) {
			int tmp = m->H[max];
			m->I[m->H[index]] = max;
			m->H[max] = m->H[index];
			m->I[tmp] = index;
			m->H[index] = tmp;
			index = max;
		}
		else break;
	}
}

int get_max_community(struct Min_delta_sigma_heap m)
{
	if(m.size==0) return -1;
	else return m.H[0];
}

void remove_community(struct Min_delta_sigma_heap *m,int community)
{
	if(m->I[community] == -1 || m->size == 0) return;
	int last_community = m->H[--size];
	m->H[m->I[community]] = last_community;
	m->I[last_community] = m->I[community];
	move_up(m,I[last_community]);
	move_down(m,I[last_community]);  
	m->I[community] = -1;
}	

void update(struct Min_delta_sigma_heap *m,int community)
{
	if(community < 0 || community >= m->max_size) return;
	if(m->I[community] == -1) {
		m->I[community] = (m->size)++;
		m->H[m->I[community]] = community;
	}
	move_up(m,m->I[community]);
	move_down(m,m->I[community]);
}

long memory(struct Min_delta_sigma_heap m)
{
	return (sizeof(struct Min_delta_sigma_heap) + long(m->max_size)*(2*sizeof(int) + sizeof(float)));
}

void initmd(struct Min_delta_sigma_heap *m,int max_s)
{
	m->max_size = max_s;
	m->size = 0;
	m->H = (int *)malloc(max_s*sizeof(int));
	m->I = (int *)malloc(max_s*sizeof(int));
	m->delta_sigma = (float *)malloc(max_s*sizeof(float));
	for(int i = 0; i < m->max_size; i++) {
		m->I[i] = -1;
		m->delta_sigma[i] = 1.;
	}
}

void destroymd(struct Min_delta_sigma_heap *m)
{
	free(m->H);
	free(m->I);
	free(m->delta_sigma);
}

bool is_empty(struct Min_delta_sigma_heap m)
{
	return (m.size==0);
}






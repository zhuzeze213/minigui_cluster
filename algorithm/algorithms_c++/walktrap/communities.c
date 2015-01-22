#include "communities.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void initP(struct Probabilities *p)
{
	p->length=0;
	p->tmp_vector1=0;
	p->tmp_vector2=0;
	p->id=0;
	p->vertices1=0;
	p->vertices2=0;
	p->current_id=0;
	p->C=C;
}

void initn(struct Neighbor *n)
{
	n->next_community1 = 0;
    n->previous_community1 = 0;
    n->next_community2 = 0;	     
    n->previous_community2 = 0;
    n->heap_index = -1;
}

void destroyp(struct Probabilities *p)
{
	p->memory_used-=p->memory(*p);
	if(p->P) free(p->P);
	if(p->vertices) free(p->vertices);
}

void initp(struct Probabilities *p,int community)
{
	Graph* G = C->G;
	int nb_vertices1 = 0;
	int nb_vertices2 = 0;
	
	float initial_proba = 1.0/(float)(C->communities[community].size);
	int last =  C->members[C->communities[community].last_member];  
	for(int m = C->communities[community].first_member; m != last; m = C->members[m]) {
		p->tmp_vector1[m] = initial_proba;
		p->vertices1[nb_vertices1++] = m;
	}
  
	for(int t = 0; t < length; t++) {
		p->current_id++;    
		if(nb_vertices1 > (G->nb_vertices/2)) {
			nb_vertices2 = G->nb_vertices;
			for(int i = 0; i < G->nb_vertices; i++)
				p->tmp_vector2[i] = 0.0;
			if(nb_vertices1 == G->nb_vertices) {
				for(int i = 0; i < G->nb_vertices; i++) {
					loat proba = p->tmp_vector1[i]/G->vertices[i].total_weight;
					for(int j = 0; j < G->vertices[i].degree; j++)
					p->tmp_vector2[G->vertices[i].edges[j].neighbor] += proba*G->vertices[i].edges[j].weight;
				}
			}
			else {
				for(int i = 0; i < nb_vertices1; i++) {
					int v1 = p->vertices1[i];
					float proba = p->tmp_vector1[v1]/G->vertices[v1].total_weight;
					for(int j = 0; j < G->vertices[v1].degree; j++)
					p->tmp_vector2[G->vertices[v1].edges[j].neighbor] += proba*G->vertices[v1].edges[j].weight;
				}
			}
		}
		else {
			nb_vertices2 = 0;
			for(int i = 0; i < nb_vertices1; i++) {
				int v1 = p->vertices1[i];
				float proba = p->tmp_vector1[v1]/G->vertices[v1].total_weight;
				for(int j = 0; j < G->vertices[v1].degree; j++) {
					int v2 = G->vertices[v1].edges[j].neighbor;
					if(p->id[v2] == p->current_id)
						p->tmp_vector2[v2] += proba*G->vertices[v1].edges[j].weight;
					else {
						p->tmp_vector2[v2] = proba*G->vertices[v1].edges[j].weight;
						p->id[v2] = p->current_id;
						p->vertices2[nb_vertices2++] = v2;
					}
				}
			}
		}
		float* tmp = p->tmp_vector2;
		p->tmp_vector2 = p->tmp_vector1;
		p->tmp_vector1 = tmp;
		
		int* tmp2 = vertices2;
		p->vertices2 = p->vertices1;
		p->vertices1 = tmp2;
		
		nb_vertices1 = nb_vertices2;
	}
	if(nb_vertices1 > (G->nb_vertices/2)) {
		P = new float[G->nb_vertices];
		p->size = G->nb_vertices;
		p->vertices = 0;
		if(nb_vertices1 == G->nb_vertices) {
			for(int i = 0; i < G->nb_vertices; i++)
			P[i] = p->tmp_vector1[i]/sqrt(G->vertices[i].total_weight);
		}
		else {
			for(int i = 0; i < G->nb_vertices; i++)
				P[i] = 0.;
			for(int i = 0; i < nb_vertices1; i++)
				P[vertices1[i]] = p->tmp_vector1[vertices1[i]]/sqrt(G->vertices[vertices1[i]].total_weight);
		}
	}
	else {
		P = new float[nb_vertices1];
		p->size = nb_vertices1;
		vertices = new int[nb_vertices1];
		int j = 0;
		for(int i = 0; i < G->nb_vertices; i++) {
			if(p->id[i] == p->current_id) {
				P[j] = p->tmp_vector1[i]/sqrt(G->vertices[i].total_weight);
				p->vertices[j] = i;
				j++;
			}
		}
	}
  C.memory_used += p->memory(*p);
}

void initp2(struct Probabilities *p,int community1,int community2)
{
	struct Probabilities* P1 = C->communities[community1].P;
  struct Probabilities* P2 = C->communities[community2].P;
  
  float w1 = float(C->communities[community1].size)/float(C->communities[community1].size + C->communities[community2].size);
  float w2 = float(C->communities[community2].size)/float(C->communities[community1].size + C->communities[community2].size);


  if(P1->size == C->G->nb_vertices) {
    p->P = new float[C->G->nb_vertices];
    p->size = C->G->nb_vertices;
    p->vertices = 0;
    
    if(P2->size == C->G->nb_vertices) {	// two full vectors
      for(int i = 0; i < C->G->nb_vertices; i++)
	p->P[i] = P1->P[i]*w1 + P2->P[i]*w2;
    }
    else {  // P1 full vector, P2 partial vector
      int j = 0;
      for(int i = 0; i < P2->size; i++) {
	for(; j < P2->vertices[i]; j++)
	  p->P[j] = P1->P[j]*w1;
	p->P[j] = P1->P[j]*w1 + P2->P[i]*w2;
	j++;
      }
      for(; j < C->G->nb_vertices; j++)
	p->P[j] = P1->P[j]*w1;
    }
  }
  else {
    if(P2->size == C->G->nb_vertices) { // P1 partial vector, P2 full vector
      p->P = new float[C->G->nb_vertices];
      p->size = C->G->nb_vertices;
      p->vertices = 0;

      int j = 0;
      for(int i = 0; i < P1->size; i++) {
	for(; j < P1->vertices[i]; j++)
	  p->P[j] = P2->P[j]*w2;
	p->P[j] = P1->P[i]*w1 + P2->P[j]*w2;
	j++;
      }
      for(; j < C->G->nb_vertices; j++)
	p->P[j] = P2->P[j]*w2;
    }
    else {  // two partial vectors
      int i = 0;
      int j = 0;
      int nb_vertices1 = 0;
      while((i < P1->size) && (j < P2->size)) {
	if(P1->vertices[i] < P2->vertices[j]) {
	  p->tmp_vector1[P1->vertices[i]] = P1->P[i]*w1;
	  p->vertices1[nb_vertices1++] = P1->vertices[i];
	  i++;
	  continue;
	}
	if(P1->vertices[i] > P2->vertices[j]) {
	  p->tmp_vector1[P2->vertices[j]] = P2->P[j]*w2;
	  p->vertices1[nb_vertices1++] = P2->vertices[j];
	  j++;
	  continue;
	}
	p->tmp_vector1[P1->vertices[i]] = P1->P[i]*w1 + P2->P[j]*w2;
	p->vertices1[nb_vertices1++] = P1->vertices[i];
	i++;
	j++;
      }
      if(i == P1->size) {
	for(; j < P2->size; j++) {
	  p->tmp_vector1[P2->vertices[j]] = P2->P[j]*w2;
	  p->vertices1[nb_vertices1++] = P2->vertices[j];
	}
      }
      else {
	for(; i < P1->size; i++) {
	 p->tmp_vector1[P1->vertices[i]] = P1->P[i]*w1;
	  p->vertices1[nb_vertices1++] = P1->vertices[i];
	}
      }

      if(nb_vertices1 > (C->G->nb_vertices/2)) {
	p->P = new float[C->G->nb_vertices];
	p->size = C->G->nb_vertices;
	p->vertices = 0;
	for(int i = 0; i < C->G->nb_vertices; i++)
	  p->P[i] = 0.;
	for(int i = 0; i < nb_vertices1; i++)
	 p->P[vertices1[i]] = p->tmp_vector1[vertices1[i]];
      }
      else {
	p->P = new float[nb_vertices1];
	p->size = nb_vertices1;
	p->vertices = new int[nb_vertices1];
	for(int i = 0; i < nb_vertices1; i++) {
	  p->vertices[i] = p->vertices1[i];
	 p->P[i] = p->tmp_vector1[vertices1[i]];
	}
      }
    }
  }

  C->memory_used += p->memory(*p);
}

double compute_distance(struct Probabilities p,const Probabilities* P2)
{
	double r = 0.;
  if(p.vertices) {
    if(P2->vertices) {  // two partial vectors
      int i = 0;
      int j = 0;
      while((i < p.size) && (j < P2->size)) {
	if(p.vertices[i] < P2->vertices[j]) {
	  r += p.P[i]*p.P[i];
	  i++;
	  continue;
	}
	if(p.vertices[i] > P2->vertices[j]) {
	  r += P2->P[j]*P2->P[j];
	  j++;
	  continue;
	}
	r += (p.P[i] - P2->P[j])*(p.P[i] - P2->P[j]);
	i++;
	j++;
      }
      if(i == p.size) {
	for(; j < P2->size; j++)
	  r += P2->P[j]*P2->P[j];
      }
      else {
	for(; i < size; i++)
	  r += p.P[i]*p.P[i];
      }
    }
    else {  // P1 partial vector, P2 full vector 

      int i = 0;
      for(int j = 0; j < p.size; j++) {
	for(; i < p.vertices[j]; i++)
	  r += P2->P[i]*P2->P[i];
	r += (p.P[j] - P2->P[i])*(p.P[j] - P2->P[i]);
	i++;
      }
      for(; i < P2->size; i++)
	r += P2->P[i]*P2->P[i];      
    }
  }
  else {
    if(P2->vertices) {  // P1 full vector, P2 partial vector
      int i = 0;
      for(int j = 0; j < P2->size; j++) {
	for(; i < P2->vertices[j]; i++)
	  r += p.P[i]*p.P[i];
	r += (p.P[i] - P2->P[j])*(p.P[i] - P2->P[j]);
	i++;
      }
      for(; i < size; i++)
	r += p.P[i]*p.P[i];
    }
    else {  // two full vectors
      for(int i = 0; i < p.size; i++)
	r += (p.P[i] - P2->P[i])*(p.P[i] - P2->P[i]);
    }
  }
  return r;
}

long memory(struct Probabilities p)
{
	  if(vertices)
    return (sizeof(struct Probabilities) + (long)(p.size)*(sizeof(float) + sizeof(int)));
  else
    return (sizeof(struct Probabilities) + (long)(p.size)*sizeof(float));
}

void initc(struct Community *c)
{
  c->P = 0;
  c->first_neighbor = 0;
  c->last_neighbor = 0;
  c->sub_community_of = -1;
  c->sub_communities[0] = -1;
  c->sub_communities[1] = -1;
  c->sigma = 0.;
  c->internal_weight = 0.;
  c->total_weight = 0.;
}

void destroy(struct Community *c)
{
	if(c->P) free(c->P);
}

void initC(struct Communities *c,struct Probabilities *p,struct Graph* G, int random_walks_length = 3, bool silent = false, int details = 1, long max_memory = -1)
{
  c->silent = s;
  c->details = d;
  c->max_memory = m;
  c->memory_used = 0;
  c->G = graph;
  
  p->C = this;
  p->length = random_walks_length;
  p->tmp_vector1 = new float[G->nb_vertices];
  p->tmp_vector2 = new float[G->nb_vertices];
  p->id = new int[G->nb_vertices];
  for(int i = 0; i < G->nb_vertices; i++) p->id[i] = 0;
  p->vertices1 = new int[G->nb_vertices];
  p->vertices2 = new int[G->nb_vertices];
  p->current_id = 0;

  
  c->members = new int[G->nb_vertices];  
  for(int i = 0; i < G->nb_vertices; i++)
    c->members[i] = -1;

  c->H = (struct Neighbor_heap *)malloc(sizeof(struct Neighbor_heap)*G->nb_edges);
  c->communities =(struct Community *)malloc(sizeof(struct Community)*2*G->nb_vertices);

// init the n single vertex communities

  if(c->max_memory != -1)
    c->min_delta_sigma = (struct Min_delta_sigma_heap *)malloc(sizeof(struct Min_delta_sigma_heap)*G->nb_vertices*2);
  else c->min_delta_sigma = 0;
  
  for(int i = 0; i < G->nb_vertices; i++) {
    c->communities[i].this_community = i;
    c->communities[i].first_member = i;
    c->communities[i].last_member = i;
    c->communities[i].size = 1;
    c->communities[i].sub_community_of = 0;
  }

  c->nb_communities = G->nb_vertices;
  c->nb_active_communities = G->nb_vertices;

  if(!silent) printf("computing random walks and the first distances:");
  for(int i = 0; i < G->nb_vertices; i++)
    for(int j = 0; j < G->vertices[i].degree; j++)
      if (i < G->vertices[i].edges[j].neighbor) {
	c->communities[i].total_weight += G->vertices[i].edges[j].weight/2.;
	c->communities[G->vertices[i].edges[j].neighbor].total_weight += G->vertices[i].edges[j].weight/2.;
	struct Neighbor* N = (struct Neighbor *)malloc(sizeof(struct Neighbor));
	N->community1 = i;
	N->community2 = G->vertices[i].edges[j].neighbor;
	N->delta_sigma = -1.0/(double)(min(G->vertices[i].degree,  G->vertices[G->vertices[i].edges[j].neighbor].degree));
	N->weight = G->vertices[i].edges[j].weight;
	N->exact = false;
	c->add_neighbor(c,N);
      }

  if(c->max_memory != -1) {
    c->memory_used += min_delta_sigma->memory(*min_delta_sigma);
    c->memory_used += 2*long(G->nb_vertices)*sizeof(struct Community);
    c->memory_used += long(G->nb_vertices)*(2*sizeof(float) + 3*sizeof(int)); // the static data of Probabilities class
    c->memory_used += H->memory(*H) + long(G->nb_edges)*sizeof(struct Neighbor);
    c->memory_used += G->memory(*G);    
  }

  int cc = 0;
  struct Neighbor* N = H->get_first(H);  
  while(!N->exact) {
    c->update_neighbor(N, compute_delta_sigma(c,N->community1, N->community2));
    N->exact = true;
    N = H->get_first(H);
    if(max_memory != -1) c->manage_memory(c);
    if(!silent) {
      cc++;
      for(int k = (500*(cc-1))/G->nb_edges + 1; k <= (500*cc)/G->nb_edges; k++) {
	if(k % 50 == 1) {printf("\n%f%% ",k/5};
	printf(".");
      }
    }
  }
  
  if(!silent) printf("\n\n");;

  if (details >= 2) printf("Partition 0 %d communities",G->nb_vertices);
  if (details >= 2) for(int i = 0; i < G->nb_vertices; i++) c->print_community(*c,i);
  if (details >= 2) printf("\n");
}

void destroyC(struct Communities *c,struct Probabilities *p)
{
	free(c->members);
	free(c->communities);
	free(c->H);
	if(c->min_delta_sigma) free(c->min_delta_sigma);
	free(p->tmp_vector1);
	free(p->tmp_vector2);
	free(p->id);
	free(p->vertices1);
	free(p->vertices2);
}

float min_delta_sigma(struct Community c)
{
	float r = 1.0;
  for(struct Neighbor* N = first_neighbor; N != 0;) {
    if(N->delta_sigma < r) r = N->delta_sigma;
    if(N->community1 == c.this_community)
      N = N->next_community1;
    else
      N = N->next_community2;
  }
  return r;
}

void add_neighborc(struct Community *c,,struct Neighbor* N)
{
	if (c->last_neighbor) {
    if(c->last_neighbor->community1 == c->this_community)
      c->last_neighbor->next_community1 = N;
    else
      c->last_neighbor->next_community2 = N;
    
    if(N->community1 == c->this_community)
      N->previous_community1 = c->last_neighbor;
    else
      N->previous_community2 = c->last_neighbor;
  }
  else {
    c->first_neighbor = N;
    if(N->community1 == c->this_community)
      N->previous_community1 = 0;
    else
      N->previous_community2 = 0;
  }
  c->last_neighbor = N;
}

void remove_neighborc(struct Community *c,struct Neighbor* N)
{
	if (N->community1 == c->this_community) {
    if(N->next_community1) {
//      if (N->next_community1->community1 == this_community)
	N->next_community1->previous_community1 = N->previous_community1;
//      else 
//	N->next_community1->previous_community2 = N->previous_community1;
    }
    else c->last_neighbor = N->previous_community1;
    if(N->previous_community1) {
      if (N->previous_community1->community1 == c->this_community)
	N->previous_community1->next_community1 = N->next_community1;
      else 
	N->previous_community1->next_community2 = N->next_community1;
    }
    else c->first_neighbor = N->next_community1;
  }
  else {
    if(N->next_community2) {
      if (N->next_community2->community1 == c->this_community)
	N->next_community2->previous_community1 = N->previous_community2;
      else 
	N->next_community2->previous_community2 = N->previous_community2;
    }
    else c->last_neighbor = N->previous_community2;
    if(N->previous_community2) {
//      if (N->previous_community2->community1 == this_community)
//	N->previous_community2->next_community1 = N->next_community2;
//      else 
	N->previous_community2->next_community2 = N->next_community2;
    }
    else c->first_neighbor = N->next_community2;
  }
}

void remove_neighborC(struct Communities *c,struct Neighbor* N)
{
	c->communities[N->community1].remove_neighbor(&(c->communities[N->community1]),N);
  c->communities[N->community2].remove_neighbor(&(c->communities[N->community2]),N);
  c->H->remove(H,N);

  if(c->max_memory !=-1) {
    if(N->delta_sigma == c->min_delta_sigma->delta_sigma[N->community1]) {
      c->min_delta_sigma->delta_sigma[N->community1] = c->communities[N->community1].min_delta_sigma();
      if(communities[N->community1].P) c->min_delta_sigma->update(N->community1);
    }

    if(N->delta_sigma == c->min_delta_sigma->delta_sigma[N->community2]) {
      c->min_delta_sigma->delta_sigma[N->community2] = c->communities[N->community2].min_delta_sigma();
      if(communities[N->community2].P) c->min_delta_sigma->update(N->community2);
    }
  }
}

void add_neighborC(struct Communities *c,struct Neighbor* N)
{
	c->communities[N->community1].add_neighborc(&(c->communities[N->community1]),N);
  c->communities[N->community2].add_neighborc(&(c->communities[N->community2]),N);
  H->add(H,N);

  if(c->max_memory !=-1) {
    if(N->delta_sigma < min_delta_sigma->delta_sigma[N->community1]) {
      c->min_delta_sigma->delta_sigma[N->community1] = N->delta_sigma;
      if(communities[N->community1].P) c->min_delta_sigma->update(N->community1);
    }

    if(N->delta_sigma < min_delta_sigma->delta_sigma[N->community2]) {
      c->min_delta_sigma->delta_sigma[N->community2] = N->delta_sigma;
      if(communities[N->community2].P) c->min_delta_sigma->update(N->community2);
    }
  }
}

/*   550  */











#ifndef COMMUNITIES_H
#define COMMUNITIES_H

#include "graph.h"
#include "heap.h"

struct Communities;
struct Probabilities
{
	static float* tmp_vector1;	// 
	static float* tmp_vector2;	// 
	static int* id;	    // 
	static int* vertices1;    //
	static int* vertices2;    //  
	static int current_id;    // 

	static struct Communities* C;				    // pointer to all the communities
	static int length;					    // length of the random walks

  
	int size;						    // number of probabilities stored
	int* vertices;					    // the vertices corresponding to the stored probabilities, 0 if all the probabilities are stored
	float* P;	
	long (*memory)(struct Probabilities p);
	double (*compute_distance)(struct Probabilities *p,const Probabilities* P2);
	void (*initp)(struct Probabilities *p,int community);
	void (*initp2)(struct Probabilities *p,int community1,int community2);
	void (*destroyp)(struct Probabilities *p);
};

struct  Community {
  struct Neighbor* first_neighbor;	// first item of the list of adjacent communities
  struct Neighbor* last_neighbor;	// last item of the list of adjacent communities
  
  int this_community;		// number of this community
  int first_member;		// number of the first vertex of the community
  int last_member;		// number of the last vertex of the community
  int size;			// number of members of the community
  
  struct Probabilities* P;		// the probability vector, 0 if not stored.  


  float sigma;			// sigma(C) of the community
  float internal_weight;	// sum of the weight of the internal edges
  float total_weight;		// sum of the weight of all the edges of the community (an edge between two communities is a half-edge for each community)
    
  int sub_communities[2];	// the two sub sommunities, -1 if no sub communities;
  int sub_community_of;		// number of the community in which this community has been merged
				// 0 if the community is active
				// -1 if the community is not used
  
  void (*merge)(struct Community *c,struct Community C1, struct Community C2);	// create a new community by merging C1 an C2
  void (*add_neighbor)(struct Community *c,,struct Neighbor* N);
  void remove_neighbor(struct Community *c,struct Neighbor* N);
  float (*min_delta_sigma)();			// compute the minimal delta sigma among all the neighbors of this community
  
  void (*initc)(struct Community *c);			// create an empty community
  void (*destroy)(struct Community *c);			// destructor
};

struct Communities {
  bool silent;		// whether the progression is displayed
  int details;		// between 0 and 3, how much details are printed
  long max_memory;	// size in Byte of maximal memory usage, -1 for no limit
  
  long memory_used;				    // in bytes
  struct Min_delta_sigma_heap* min_delta_sigma;    	    // the min delta_sigma of the community with a saved probability vector (for memory management)
  
  struct Graph* G;		    // the graph
  int* members;		    // the members of each community represented as a chained list.
			    // a community points to the first_member the array which contains 
			    // the next member (-1 = end of the community)
  struct Neighbor_heap* H;	    // the distances between adjacent communities.


  struct Community* communities;	// array of the communities
  
  int nb_communities;		// number of valid communities 
  int nb_active_communities;	// number of active communities
  
  float (*find_best_modularity)(struct Communities c,int community, bool* max_modularity);
  void (*print_best_modularity_partition)(struct Communities c);
  void (*print_best_modularity_partition2)(struct Communities c,int community, bool* max_modularity);

  
  void (*initC)(struct Communities *c,struct Graph* G, int random_walks_length = 3, bool silent = false, int details = 1, long max_memory = -1);    // Constructor
  void (*destroyC)(struct Communities *c);					// Destructor


  void (*merge_communities)(struct Communities *c,struct Neighbor* N);			// create a community by merging two existing communities
  double (*merge_nearest_communities)(struct Communities *c);

  
  double (*compute_delta_sigma)(int c1, int c2);		// compute delta_sigma(c1,c2) 

  void (*remove_neighbor)(struct Communities *c,struct Neighbor* N);
  void add_neighbor(struct Communities *c,struct Neighbor* N);
  void update_neighbor(struct Communities *c,struct Neighbor* N, float new_delta_sigma);

  void manage_memory(struct Communities c);
  
  void print_state(struct Communities c);
  void print_partition(struct Communities c,int nb_remaining_commities);	// print the partition for a given number of communities
  void print_community(struct Communities c,int c);				// print a community  
};



#endif










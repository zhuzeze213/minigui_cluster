#ifndef HEAP_H
#define HEAP_H

#define bool int
#define false 0
#define true 1

struct Neighbor
{
	int community1;
	int community2;
	float delta_sigma;
	float weight;
	bool exact;
	struct Neighbor *next_community1;
	struct Neighbor *next_community2;
	struct Neighbor *previous_community1;
	struct Neighbor *previous_community2;
	int heap_index;
	void (*initn)(struct Neighbor *n);
};

struct Neighbor_heap
{
	int size;
	int max_size;
	struct Neighbor **H;
	void (*move_up)(struct Neighbor_heap *n,int index);
	void (*move_down)(struct Neighbor_heap *n,int index);
	void (*add)(struct Neighbor_heap *n,struct Neighbor* N);	    // add a new distance
	void (*update)(struct Neighbor_heap *n,struct Neighbor* N);	    // update a distance 
	void (*remove)(struct Neighbor_heap *n,struct Neighbor* N);	    // remove a distance
	struct Neighbor* (*get_first)(struct Neighbor_heap *n);	    // get the first item
	long (*memory)(struct Neighbor_heap n);
	bool (*is_empty)(struct Neighbor_heap n);
  
	void (*initnh)(struct Neighbor_heap *n,int max_size);
	void (*destroynh)(struct Neighbor_heap *n);
};

struct Min_delta_sigma_heap 
{
	int size;
	int max_size;

	int* H;   // the heap that contains the number of each community
	int* I;   // the index of each community in the heap (-1 = not stored)

	void (*move_up)(int index);
	void (*move_down)(int index);

	int (*get_max_community)();			    // return the community with the maximal delta_sigma
	void (*remove_community)(int community);		    // remove a community;
	void (*update)(int community);			    // update (or insert if necessary) the community
	long (*memory)();				    // the memory used in Bytes.
	bool (*is_empty)();

	float* delta_sigma;				     // the delta_sigma of the stored communities
  
	void (*initmd)(int max_size);
	void (*destroymd)();
};
#endif





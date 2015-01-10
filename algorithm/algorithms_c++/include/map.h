#ifndef MAP_H
#define MAP_H

#include "general.h"
#define MAX_SIZE 100

#define insert(map,elem) ({   \
	(map)->data[(map)->length]=elem; \
	(map)->length++;})

#define print_index(map,type,i)   \
	(((type *)((map).data[i]))->index)

#define print_value(map,type,i)   \
	(((type *)((map).data[i]))->value)	
/*struct map_operate
{
	void (*insert)                    (struct map_struct *map,void *data);
	int  (*find)                      (struct map_struct *map,void *index);
	int  (*count)                     (struct map_struct *map,void *index);
	void (*get)                       (struct map_struct *map,void *index);
	
	void  (*erase)                    (struct map_struct *map,int num);
	void  (*erase_scope)              (struct map_struct *map,int first,int last);
	void  (*erase_key)                (struct map_struct *map,void *index);
	void  (*clear)                    (struct map_struct *map);
	
};*/

struct map_struct 
{
	void *data[MAX_SIZE];
	int length;
	//struct map_operate *ope;
};



#endif

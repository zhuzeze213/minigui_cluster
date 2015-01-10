#ifndef MULTIMAP_H
#define MULTIMAP_H

#include "list.h"

#define find(map,key,type) \
	(((type *)map->data)->index==key?1:0)


	
struct map_operate
{
	void (*insert)                    (struct map_struct *map,void *data);
	int  (*find)                      (struct map_struct *map,void *index);
	int  (*count)                     (struct map_struct *map,void *index);
	void (*get)                       (struct map_struct *map,void *index);
	struct list_head *(begin)         (struct map_struct *map);
	struct list_head *(end)           (struct map_struct *map);
	
	void  (*erase)                    (struct map_struct *map,int num);
	void  (*erase_scope)              (struct map_struct *map,int first,int last);
	void  (*erase_key)                (struct map_struct *map,void *index);
	void  (*clear)                    (struct map_struct *map);
	
}

struct map_struct 
{
	void * data;
	struct list_head list;
	struct list_head *head;
	struct list_head *tail;
	struct map_operate *ope;
}

#endif

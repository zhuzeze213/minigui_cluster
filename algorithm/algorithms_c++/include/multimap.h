#ifndef MULTIMAP_H
#define MULTIMAP_H

#include "list.h"

#define find(map,key,type) \
	(((type *)map->data)->index==key?1:0)


	
struct multimap_operate
{
	void (*init)                      (struct multimap_struct *map);
	int  (*empty)                     (struct multimap_struct map);
	void (*insert)                    (struct multimap_struct *map,void *data);
	int  (*find)                      (struct multimap_struct map,void *index);
	int  (*count)                     (struct multimap_struct map,void *index);
	
	void  (*erase)                    (struct multimap_struct *map,int num);
	void  (*erase_scope)              (struct multimap_struct *map,int first,int last);
	void  (*erase_key)                (struct multimap_struct *map,void *index);
	void  (*clear)                    (struct multimap_struct *map);
	void  (*swap)                     (struct multimap_struct *map,struct multimap_struct *new);
};

struct multimap_struct 
{
	void *data[MAX_SIZE];
	int length;
	//struct multimap_operate *ope;
};

void init(struct multimap_struct *map)
{
	int i;
	for(i=0;i<MAX_SIZE;i++)
		map->data[i]=NULL;
	map->length=0;
}
int empty(struct multimap_struct map)
{
	map.length>0?1:0;
}

void insert_mul(struct multimap_struct *map,void *data)
{
	map->data[(map)->length]=elem; 
	map->length++;
}

#define find(map,index,type,num)({    \
	for(f=0;f<map.length;f++){       \
		if(num==1&&((type *)(map.data[f])).index==*index)  \
			break;       \
		if(num==2&&!strcmp(((type *)(map.data[f])).index,index))  \
			break;      \
	}   \
})


void erase(struct multimap_struct *map,int num)
{
	int i;
	for(i=num;i<map->length;i++){
		data[i]=data[i+1];
	}
	map->length--;
}

void erase_scope(struct multimap_struct *map,int first,int last)
{
	int i;
	for(i=first;i<last;i++)
		erase(map,i);
}	 

#define erase_key(map,index,type,num)({ \
	if(f<(map)->length){    \
		erase(map,f);    \
	}    \
})

void clear(struct multimap_struct *map)
{
	int i;
	for(i=0;i<map->length;i++)
		map->data[i]=NULL;
	map.length=0;
}

void swap(struct multimap_struct *map,struct multimap_struct *new)
{
	int i;
	for(i=0;i<MAX_SIZE;i++){
		__swap(map->data[i],new->data[i]);
	}
	__swap(map->length,new->length);
}

#endif

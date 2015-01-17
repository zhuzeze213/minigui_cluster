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
struct map_operate
{
	void (*init)                      (struct map_struct *map);
	int  (*empty)                     (struct map_struct map);
	void (*insert)                    (struct map_struct *map,void *data);
	int  (*find)                      (struct map_struct map,void *index);
	int  (*count)                     (struct map_struct map,void *index);
	
	void  (*erase)                    (struct map_struct *map,int num);
	void  (*erase_scope)              (struct map_struct *map,int first,int last);
	void  (*erase_key)                (struct map_struct *map,void *index);
	void  (*clear)                    (struct map_struct *map);
	void  (*swap)                     (struct map_struct *map,struct map_struct *new);
};

struct map_struct 
{
	void *data[MAX_SIZE];
	int length;
	//struct map_operate *ope;
};

void init(struct map_struct *map)
{
	int i;
	for(i=0;i<MAX_SIZE;i++)
		map->data[i]=NULL;
	map->length=0;
}
int empty(struct map_struct map)
{
	map.length>0?1:0;
}

void insert_mul(struct map_struct *map,void *data)
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

#define insert(map,data,type,num)({   \
	find(*map,(type *)(data)->index,type,num);   \
	if(f<(map)->length&&num==1)     \
		((type *)((map)->data[f])).value=(type *)(data)->value;	\
	else if(f<(map)->length&&num==2)	\
		strcpy(((type *)((map)->data[f])).value,((type *)(data)->value));	\
	else	\
		insert_mul(map,data);	\
})
		
	

void erase(struct map_struct *map,int num)
{
	int i;
	for(i=num;i<map->length;i++){
		data[i]=data[i+1];
	}
	map->length--;
}

void erase_scope(struct map_struct *map,int first,int last)
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

void clear(struct map_struct *map)
{
	int i;
	for(i=0;i<map->length;i++)
		map->data[i]=NULL;
	map.length=0;
}

void swap(struct map_struct *map,struct map_struct *new)
{
	int i;
	for(i=0;i<MAX_SIZE;i++){
		__swap(map->data[i],new->data[i]);
	}
	__swap(map->length,new->length);
}

#endif












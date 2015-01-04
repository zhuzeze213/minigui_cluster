#ifndef SET_H
#define SET_H

#include "general.h"
#define MAX_SIZE 100
#define MAGIC 0.1234567

struct set_struct{
	double set_array[MAX_SIZE];
	/*general*/
	void (*printSet)      (struct set_struct set);
	int  (*size)          (struct set_struct set);
	int  (*empty)         (struct set_struct set);
	/*init*/
	void (*strLess)       ();
	void (*init)          (struct set_struct *set);
	void (*copy)          (struct set_struct *set,struct set_struct old);
	void (*copy_array)    (struct set_struct *set,double *array,int length);
	void (*default_sort)  (struct set_struct *set);
	/*insert*/
	int  (*insert)        (struct set_struct *set,double value);
	int  (*insert_pos)    (struct set_struct *set,double value,int pos);
	void (*insert_array)  (struct set_struct *set,double *array,int length);
	/* erase*/
	int  (*erase)         (struct set_struct *set,double value);
	void (*erase_pos)     (struct set_struct *set,int pos);
	void (*erase_scope)   (struct set_struct *set,int spos,int epos);
	void (*clear)         (struct set_struct *set);
	/*find*/
	int  (*count)         (struct set_struct *set,double value);
	int  (*find)          (struct set_struct *set,double value);
	/*exchange*/
	void (*swap)          (struct set_struct *set,struct set_struct *old);	
}

int size(struct set_struct set)
{
	int i=0;
	while(i<MAX_SIZE){
		if(set.set_array[i]!=MAGIC)
			i++;
		else
			break;
	}
	return i;
}

void printSet(struct set_struct set)
{
	print_matrix_double(set.set_array,set.size(set));
}

int empty(struct set_struct set)
{
	int i;
	if(set.set_array[0]==MAGIC)
		return 1;
	else
		return 0;
}

void init(struct set_struct *set)
{
	int i;
	for(i=0;i<MAX_SIZE;i++)
		set->set_array[i]=MAGIC;	
}

void copy(struct set_struct *set,struct set_struct old)
{
	copy_matrix_double(old.set_array,set->set_array,0,MAX_SIZE,0);
}

void copy_array(struct set_struct *set,double *array,int length)
{
	copy_matrix_double(array,set->set_array,0,length,0);
}

void default_sort(struct set_struct *set)
{
	bubblesort(set->set_array,set->size(*set));
}

int insert(struct set_struct *set,double value)
{
	if(find_num(set->set_array,set->size(*set),value)<0){
		set->set_array[set->size(*set)]=value;
		default_sort(set);
		return find_num(set->set_array,set->size(*set),value);
	}
	return -1;
}

int insert_pos(struct set_struct *set,double value,int pos)
{
	int res=0;
	if(set->set_array[pos]<value){
		if(res=insert(set,value)>0)
			return res;
	}
	return -1;		
}

void insert_array(struct set_struct *set,double *array,int length)
{
	int i;
	for(i=0;i<length;i++)
		insert(set,array[i]);
}

int erase(struct set_struct *set,double value);
{
	int pos;
	if(pos=find_num(set->set_array,set->size(*set),value)<0)
		return 0;
	else{
		int length=set->size(*set);
		int i;
		for(i=pos;i<length;i++)
			set->set_array[i]=set->set_array[i+1];
		return 1;
	}
}

void erase_pos(struct set_struct *set,int pos)
{
	int length=set->size(*set);
	int i;
	for(i=pos;i<length;i++)
		set->set_array[i]=set->set_array[i+1];
}

void erase_scope(struct set_struct *set,int spos,int epos)
{
	int i;
	for(i=spos;i<epos;i++)
		set->set_array[i]=set->set_array[i+1];
}

void clear(struct set_struct *set)
{
	init(set);
}

int count(struct set_struct *set,double value)
{
	if(find_num(set->set_array,set->size(*set),value)<0)
		return 0;
	else
		return 1;
}

int  find(struct set_struct *set,double value)
{
	return find_num(set->set_array,set->size(*set),value);
}

void swap(struct set_struct *set,struct set_struct *old)
{
	int max=MAX(set->size(*set), old->size(*old));
	int i;
	for(i=0;i<max;i++)
		__swap(set->set_array[i],old->set_array[i]);
}



#endif

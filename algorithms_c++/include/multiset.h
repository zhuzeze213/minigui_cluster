#ifndef MULTISET_H
#define MULTISET_H

#include "general.h"
#define MAX_SIZE 100
#define MAGIC 0.1234567

struct multiset_operate
{
    /*general*/
	void (*printSet)      (struct multiset_struct set);
	int  (*size)          (struct multiset_struct set);
	int  (*empty)         (struct multiset_struct set);
	/*init*/
	void (*strLess)       ();
	void (*init)          (struct multiset_struct *set);
	void (*copy)          (struct multiset_struct *set,struct multiset_struct old);
	void (*copy_array)    (struct multiset_struct *set,double *array,int length);
	void (*default_sort)  (struct multiset_struct *set);
	/*insert*/
	int  (*insert)        (struct multiset_struct *set,double value);
	int  (*insert_pos)    (struct multiset_struct *set,double value,int pos);
	void (*insert_array)  (struct multiset_struct *set,double *array,int length);
	/* erase*/
	int  (*erase)         (struct multiset_struct *set,double value);
	void (*erase_pos)     (struct multiset_struct *set,int pos);
	void (*erase_scope)   (struct multiset_struct *set,int spos,int epos);
	void (*clear)         (struct multiset_struct *set);
	/*find*/
	int  (*count)         (struct multiset_struct *set,double value);
	int  (*find)          (struct multiset_struct *set,double value);
	/*exchange*/
	void (*swap)          (struct multiset_struct *set,struct multiset_struct *old);	
};
struct multiset_struct{
	double set_array[MAX_SIZE];
	struct multiset_operate *ope;
};

int size(struct multiset_struct set)
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

void printSet(struct multiset_struct set)
{
	print_matrix_double(set.set_array,set.size(set));
}

int empty(struct multiset_struct set)
{
	int i;
	if(set.set_array[0]==MAGIC)
		return 1;
	else
		return 0;
}

void init(struct multiset_struct *set)
{
	int i;
	for(i=0;i<MAX_SIZE;i++)
		set->set_array[i]=MAGIC;	
}

void copy(struct multiset_struct *set,struct multiset_struct old)
{
	copy_matrix_double(old.set_array,set->set_array,0,MAX_SIZE,0);
}

void copy_array(struct multiset_struct *set,double *array,int length)
{
	copy_matrix_double(array,set->set_array,0,length,0);
}

void default_sort(struct multiset_struct *set)
{
	bubblesort(set->set_array,set->size(*set));
}

int insert(struct multiset_struct *set,double value)
{
	set->set_array[set->size(*set)]=value;
	default_sort(set);
	return find_num(set->set_array,set->size(*set),value);
}

int insert_pos(struct multiset_struct *set,double value,int pos)
{
	int res=0;
	if(set->set_array[pos]<value){
		if(res=insert(set,value)>0)
			return res;
	}
	return -1;		
}

void insert_array(struct multiset_struct *set,double *array,int length)
{
	int i;
	for(i=0;i<length;i++)
		insert(set,array[i]);
}

int erase(struct multiset_struct *set,double value);
{
	int pos;
	if(pos=find_num(set->set_array,set->size(*set),value)<0)
		return 0;
	else{		
		int count=0;
		int j=0;
		while(j<set->size(*set)&&pos=find_num(set->set_array,set->size(*set),value)>=0){
			int length=set->size(*set);
			for(i=pos;i<length;i++)
				set->set_array[i]=set->set_array[i+1];
			j++;
			count++;
		}
		return count;
	}
}

void erase_pos(struct multiset_struct *set,int pos)
{
	int length=set->size(*set);
	int i;
	for(i=pos;i<length;i++)
		set->set_array[i]=set->set_array[i+1];
}

void erase_scope(struct multiset_struct *set,int spos,int epos)
{
	int i;
	for(i=spos;i<epos;i++)
		set->set_array[i]=set->set_array[i+1];
}

void clear(struct multiset_struct *set)
{
	init(set);
}

int count(struct multiset_struct *set,double value)
{
	if(find_num(set->set_array,set->size(*set),value)<0)
		return 0;
	else{
		int i;int count=0;
		for(i=0;i<set->size(*set);i++){
			if(set->set_array[i]==value)
				count++;
		}
		return count;
	}			
}

int find(struct multiset_struct *set,double value)
{
	return find_num(set->set_array,set->size(*set),value);
}

void swap(struct multiset_struct *set,struct multiset_struct *old)
{
	int max=MAX(set->size(*set), old->size(*old));
	int i;
	for(i=0;i<max;i++)
		__swap(set->set_array[i],old->set_array[i]);
}



#endif

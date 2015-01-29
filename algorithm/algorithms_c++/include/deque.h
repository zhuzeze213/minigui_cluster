#ifndef DEQUE_H
#define DEQUE_H
#include "list.h"
#include "general.h"

struct deque_operate
{
	void    (*assign_scope)       (struct deque_struct *deque,int beg,int end);
	void    (*assign_repeated)    (struct deque_struct *deque,int n,void *elem);
	void *  (*at)                 (struct deque_struct deque,int idx);
	void *  (*back)               (struct deque_struct deque);
	void *  (*front)              (struct deque_struct deque);
	void    (*clear)              (struct deque_struct *deque);
	
	void    (*init_head)          (struct deque_struct *deque,int n);
	void    (*copy)               (struct deque_struct *deque,struct deque_struct *old);
	void    (*init_n)             (struct deque_struct *deque,int n);
	void    (*init_repeated)      (struct deque_struct *deque,int n,void *elem);
	void    (*init_scope)         (struct deque_struct *deque,int beg,int end);
	void    (*destruct)           (struct deque_struct *deque);
	
	int     (*empty)              (struct deque_struct deque);
	struct  list_head *(*begin)   (struct deque_struct deque);
	struct  list_head *(*end)     (struct deque_struct deque);
	struct  list_head *(*erase_pos)(struct deque_struct *deque,int pos);
	struct  list_head *(*erase_scope)(struct deque_struct *deque,int beg,int end);
	
	int     (*insert_pos)         (struct deque_struct *deque,int pos,void *elem);
	void    (*insert_pos_repeated)(struct deque_struct *deque,int pos,int n,void *elem);
	void    (*insert_pos_scope)   (struct deque_struct *deque,int pos,int beg,void *end);
	
	int     (*max_size)           ();
	void    (*pop_back)           (struct deque_struct *deque);
	void    (*pop_front)          (struct deque_struct *deque);
	void    (*push_back)          (struct deque_struct *deque,void *elem);
	void    (*push_front)         (struct deque_struct *deque,void *elem);
	
	void    (*resize)             (struct deque_struct *deque,int num);
	void    (*size)               (struct deque_struct *deque);
	
	void    (*swap)               (struct deque_struct *deque,struct deque_struct *old);
};

struct deque_struct 
{
	void * data;
	struct list_head list;
	struct list_head *head;
	
	struct deque_operate *ope;
};

void _init(struct deque_struct *h,int num)
{
	if(!head) h=(struct deque_struct *)malloc(sizeof(struct deque_struct));
	INIT_LIST_HEAD(&(h->list));
	h->head-h;
	int i;
	for(i=0;i<num;i++){
		struct deque_struct *n=(struct deque_struct *)malloc(sizeof(struct deque_struct));
		list_add(&(n->list),&(h->list));
		n->head=h;
	}	
}

void assign_scope(struct deque_struct *h,int beg,int end)
{
	int num=end-beg;
	_init(h,num);
	struct deque_struct *pos;
	int i=beg;
	list_for_each_entry(pos, h->head, list){
		pos->data=(int *)malloc(sizeof(int));
		*(pos->data)=i;
		i++;
	}		
}

#define assign_repeated(h,n,elem,type) ({ \
	_init(h,n);                    \
	struct deque_struct *pos;        \
	list_for_each_entry(pos, h->head, list){    \
		pos->data=(type *)malloc(sizeof(type)); \
		*(pos->data)=(type)(*(elem));           \
		i++;                                    \
	}                                   })                                         
                                              
void *at(struct deque_struct h,int idx)
{
	struct deque_struct *pos;
	list_for_each_entry(pos, h.head, list){
		idx--;
		if(idx<0) break;
	}
	if(idx>=0) return OUT_OF_RANGE;
	else return pos->data;		
}

void *back(struct deque_struct h)
{
	return list_entry((h.head)->prev,struct deque_struct,list)->data;
}

void *front(struct deque_struct h)
{
	return list_entry((h.head)->next,struct deque_struct,list)->data;
}
/*Attention if CLEAR all memory should alloc again !*/
void clear(struct deque_struct *h)
{
	struct deque_struct *pos;
	list_for_each_entry(pos, h->head, list){
		
	}
	
}
#
#endif









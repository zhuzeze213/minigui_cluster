#ifndef DEQUE_H
#define DEQUE_H
#include "list.h"

struct deque_operate
{
	void    (*assign_scope)       (struct deque_struct *deque,int beg,int end);
	void    (*assign_repeated)    (struct deque_struct *deque,int n,void *elem);
	double  (*at)                 (struct deque_struct deque,int idx);
	double  (*back)               (struct deque_struct deque);
	double  (*front)              (struct deque_struct deque);
	void    (*clear)              (struct deque_struct *deque);
	
	void    (*init_head)          (struct deque_struct *deque);
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
	struct list_head *tail;
	
	struct deque_operate *ope;
};

#endif

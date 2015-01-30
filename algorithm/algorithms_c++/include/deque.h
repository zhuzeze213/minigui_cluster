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
	void    (*copy)               (struct deque_struct *deque,struct deque_struct old);
	void    (*init_n)             (struct deque_struct *deque,int n);
	void    (*init_repeated)      (struct deque_struct *deque,int n,void *elem);
	void    (*init_scope)         (struct deque_struct *deque,int beg,int end);
	void    (*destruct)           (struct deque_struct *deque);
	
	int     (*empty)              (struct deque_struct *deque);
	struct  list_head *(*begin)   (struct deque_struct deque);
	struct  list_head *(*end)     (struct deque_struct deque);
	struct  list_head *(*erase_pos)(struct deque_struct *deque,int pos);
	struct  list_head *(*erase_scope)(struct deque_struct *deque,int beg,int end);
	
	struct  list_head *(*insert_pos) (struct deque_struct *deque,int pos,void *elem);
	void    (*insert_pos_repeated)(struct deque_struct *deque,int pos,int n,void *elem);
	void    (*insert_pos_scope)   (struct deque_struct *deque,int pos,int beg,int end);
	
	int     (*max_size)           ();
	void    (*pop_back)           (struct deque_struct *deque);
	void    (*pop_front)          (struct deque_struct *deque);
	void    (*push_back)          (struct deque_struct *deque,void *elem);
	void    (*push_front)         (struct deque_struct *deque,void *elem);
	
	void    (*resize)             (struct deque_struct *deque,int num);
	int     (*size)               (struct deque_struct deque);
	
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
	h->head=h;
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
	list_for_each_entry(pos, (h)->head, list){    \
		pos->data=malloc(sizeof(type)); \
		*(pos->data)=*((void *)(elem));         \
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
/*Attention! if CLEAR all memory should alloc again(use _init) !*/
void clear(struct deque_struct *h)
{
	struct deque_struct *pos;
	list_for_each_entry(pos, h->head, list){
		free(list_entry(pos->list.prev,struct deque_struct,list);
	}
}

int size(struct deque_struct h)
{
	struct deque_struct *pos;
	int ret=0;
	list_for_each_entry(pos, h.head, list){
		ret++;
	}
	return ret;
}
#define copy(h,old,type) ({                                       \
	_init((h),size(old));                                           \
	struct deque_struct tmp=old;                                  \
	list_for_each_entry(pos, (h)->head, list){                      \
		tmp=*(list_entry(tmp.list.next, struct deque_struct, list));  \
		h->data=malloc(sizeof(type));                          \
		*(h->data)=*((void *)(tmp.data))                               \
	}                    })                      


void init_n(struct deque_struct *h,int n)
{
	_init(h,n);
}

int empty(struct deque_struct *h)
{
	if(list_entry(h->list.next, struct deque_struct, list)==h)
		return 1;
	else return 0;
}

struct  list_head *begin(struct deque_struct h)
{
	return h.list.next;
}

struct  list_head *end(struct deque_struct h)
{
	return h.list.prev;
}
struct  list_head *erase_pos(struct deque_struct *h,int p)
{
	struct deque_struct *pos,save;
	list_for_each_entry(pos, h->head, list){
		p--;
		if(p<0){
			save=*pos;
			list_del(&pos->list)
			break;
		}
	}
	return save.list.next;
}

struct list_head *erase_scope(struct deque_struct *h,int beg,int end)
{
	int count=0;
	struct deque_struct *pos,save;
	list_for_each_entry(pos, h->head, list){
		if(count>=beg&&count<end)
			list_del(&pos->list);					
		if(count==end){
			save=*pos;	
			break;
		}
		count++;
	}
	return save->next;
}

#define insert_pos(h,p,elem,type)  ({           \
	struct deque_struct *pos;                   \
	list_for_each_entry(pos, h->head, list){     \
		p--;                                    \
		if(p<0) break;                          \
	}                                           \
	struct deque_struct *n=(struct deque_struct *)malloc(sizeof(struct deque_struct)); \
	n->data=malloc(sizeof(type));       \
	*(n->data)=*((void *)(elem));               \
	__list_add(&n->list,pos->list.prev,&pos->list);   })


#define insert_pos_repeated(h,p,n,elem,type,i)   ({	\
	struct deque_struct *pos;                   \
	list_for_each_entry(pos, h->head, list){     \
		p--;                                    \
		if(p<0) break;                          \
	}                                           \
	for(i=0;i<n;i++){                           \
		struct deque_struct *ne=(struct deque_struct *)malloc(sizeof(struct deque_struct)); \
		ne->data=malloc(sizeof(type));       \
		*(ne->data)=*((void *)(elem));               \
		__list_add(&ne->list,pos->list.prev,&pos->list);     \
		pos=list_next_entry(pos, list)                       \
	}                       })
		                                          
	
#endif









#include "deque.h"

struct v
{
	int index;
	char name[10];
};
int main(void)
{
	struct deque_struct h1,h,h2,*pos;
	assign_scope(&h1,1,4);
	//erase_pos(&h1,1);
	//erase_scope(&h1,1,2);
	int b=1,p=1;
	insert_pos(&h1,p,&b,int,1);p=1;int i;
	insert_pos_repeated(&h1,p,3,&b,int,i,1);
	insert_pos_scope(&h1,3,6,9);
	list_for_each_entry(pos, h1.head, list)
		printf("%d ",*(int *)pos->data);
	printf("\n");

	struct v test[3]={{1,"aaa"},{3,"ccc"},{2,"bbb"}};
	assign_repeated(&h,5,test,struct v,3);
	//clear(&h);
/*	list_for_each_entry(pos, h.head, list)
		printf("%d %s ",((struct v *)pos->data+1)->index,((struct v *)pos->data+1)->name);*/
	
//	printf("%d\n",size(&h));
/*	printf("%d ",*(int *)at(&h,1))->name);
	printf("%d ",*(int *)back(&h1));
	printf("%d ",*(int *)front(&h1));*/
	copy(&h2,&h,struct v,3);
	p=1;
	insert_pos(&h2,p,test,struct v,3);p=1;
	insert_pos_repeated(&h2,p,3,test,struct v,i,3);
	//erase_pos(&h2,1);
	list_for_each_entry(pos, h2.head, list)
		printf("%d %s ",((struct v *)pos->data+1)->index,((struct v *)pos->data+1)->name);
	struct deque_struct hc;
	_initd(&hc,0);
	int po=0;
	insert_pos(&hc,po,"aaa",char,5);po=1;
	insert_pos(&hc,po,"bbb",char,5);po=2;
	insert_pos(&hc,po,"ccc",char,5);
	//pop_back(&hc);
	pop_front(&hc);push_front(&hc,po,"ddd",char,5);
	push_back(&hc,po,"eee",char,5);
	list_for_each_entry(pos, hc.head, list)
		printf("%s ",(char *)pos->data);
	return 0;
}

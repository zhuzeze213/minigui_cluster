#include "list.h"

struct stack_double
{
	double num;
	struct list_head *tail;
	struct list_head list;
}


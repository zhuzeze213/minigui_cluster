#include "map.h"

struct v{
	double index;
	char *value;
};

int main(void)
{
	struct map_struct map1;
	map1.length=0;
	struct v *elem=(struct v*)malloc(sizeof(struct v));
	elem->index=1.111;elem->value="i am a student";
	insert(&map1,elem);insert(&map1,elem);
	printf("%f %s %d\n",print_index(map1,struct v,0),print_value(map1,struct v,0),map1.length);
	return 0;
	
}

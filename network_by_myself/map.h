#ifndef MAP_H
#define MAP_H

#define MAPX 20
#define MAPY 20
/**********i design a map that people lives********
********** i hope some animals,plants,people,buildings**
********** will work well**************************/
#define NO 0
#define TREE 1
#define ANIMAL 2
#define BUILD 3
#define FARM 4
#define GARDEN 5
#define HUMANLAND 6
struct build_struct 
{
	int x;
	int y;
};

#define BUILDNUM 20
void init_map();
extern int map[MAPX+1][MAPY+1];extern struct build_struct build[BUILDNUM];
#endif

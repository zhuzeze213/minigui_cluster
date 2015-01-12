#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h> 
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#define MAP_X 30
#define MAP_Y 60
#define FOOD_SIZE 50
#define FRESH_TIME 100000
#define FOOD_TIME 1000000
struct food
{
	int x;
	int y;
	struct food *next;
	struct food *prev;
	int n;
	int eatnum;
	int no;
};

int map[MAP_X][MAP_Y];
struct food *head;
int mynum=2,myx=MAP_X/2,myy=MAP_Y/2;
int sum=FOOD_SIZE;
int sumn=0;
void initmap()
{
	int i,j;
	for(i=0;i<MAP_X;i++)
		for(j=0;j<MAP_Y;j++)
			map[i][j]=0;
}
void printmap()
{
	printf("\033c");
	int i,j;
	for(i=0;i<MAP_X;i++){
		for(j=0;j<MAP_Y;j++){
			if(i==myx&&j==myy)
				printf("\033[35m%d\033[0m\n",mynum);
			else{
				if(map[i][j])
					printf("%d",map[i][j]);
				else
					printf(" ");
			}
		}
		printf("\n");
	}
}
void *findfood(void *arg)
{
	while(1){
	struct food *work,*eat;
	double min=10000;
	for(work=head->next;work;work=work->next){
		if(work->eatnum){
			for(eat=head->next;eat;eat=eat->next){
				if(eat->no==work->eatnum){
					if(eat->x==work->x&&eat->y==work->y&&work->n>eat->n){
						work->n+=eat->n;
						work->eatnum=0;
						eat->prev->next=eat->next;
						if(eat->next)
							eat->next->prev=eat->prev;
						sum--;
						//free(eat);
					}
					if(eat->x>work->x) work->x++;
					else if(eat->x<work->x) work->x--;
					if(eat->y>work->y) work->y++;
					else if(eat->y<work->y) work->y--;
				}
			}
		}
		else{
			for(eat=head->next;eat;eat=eat->next){
				double tmp=sqrt(abs(eat->x-work->x)*abs(eat->x-work->x)+abs(eat->y-work->y)*abs(eat->y-work->y));
				if(eat!=work&&tmp<min){
					min=tmp;
					work->eatnum=eat->no;
				}
			}
		}
		min=10000;
	}
	usleep(FOOD_TIME);
	}
	return (void *)0;	
}

void *foodmove(void *arg)
{
	while(1){
	struct food *work;
	for(work=head->next;work;work=work->next){
		int i=rand()%2;
		int j=rand()%2;
		if(i==1){			
			if(j==1){
				work->x++;
				if(work->x==MAP_X)
					work->x-=2;
			}
			else{
				work->x--;
				if(work->x==-1)
					work->x+=2;
			}
		}
		else{
			if(j==1){
				work->y++;
				if(work->y==MAP_Y)
					work->y-=2;
			}
			else{
				work->y--;
				if(work->y==-1)
					work->y+=2;
			}
		}
	}
	usleep(FOOD_TIME);
	}
	return (void *)0;
			
}

void *show()
{
	while(1){
		struct food *work;
		initmap();
		for(work=head->next;work;work=work->next)
			map[work->x][work->y]=work->n;
		map[myx][myy]=mynum;
		printmap();
		//foodmove();
		printf("left %d nodes\n",sum);
		printf("sum=%d\n",sumn);
		usleep(FRESH_TIME);
	}
	return (void *)0;
}

void initfood()
{
	head=(struct food*)malloc(sizeof(struct food));
	struct food *head_tmp=head;
	int i;
	for(i=0;i<FOOD_SIZE;i++){
		struct food *ne=(struct food*)malloc(sizeof(struct food));
		ne->x=rand()%MAP_X;
		ne->y=rand()%MAP_Y;
		ne->n=rand()%(mynum*2)+1;
		ne->no=i+1;
		ne->eatnum=0;
		head_tmp->next=ne;
		ne->prev=head_tmp;
		head_tmp=head_tmp->next;
		sumn+=ne->n;
	}	
}
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)  
int set_disp_mode(int fd,int option)  
{  
   int err;  
   struct termios term;  
   if(tcgetattr(fd,&term)==-1){  
     perror("Cannot get the attribution of the terminal");  
     return 1;  
   }  
   if(option)  
        term.c_lflag|=ECHOFLAGS;  
   else  
        term.c_lflag &=~ECHOFLAGS;  
   err=tcsetattr(fd,TCSAFLUSH,&term);  
   if(err==-1 && err==EINTR){  
        perror("Cannot set the attribution of the terminal");  
        return 1;  
   }  
   return 0;  
}  

void eat()
{
	struct food *work;
	for(work=head->next;work;work=work->next){
		if(work->x==myx&&work->y==myy&&mynum>=work->n){
			mynum+=work->n;
			work->prev->next=work->next;
		}
			
	}
}
void *move(void *arg)
{
	while(1){
		//printmap();
		char c=getchar();
		switch(c){
			case 'w':myx--;break;
			case 's':myx++;break;
			case 'a':myy--;break;
			case 'd':myy++;break;
		}
		if(myx==MAP_X) myx=0;
		if(myx==-1) myx=MAP_X-1;
		if(myy==MAP_Y) myy=0;
		if(myy==-1) myy=MAP_Y-1; 
		eat();  
	}
	return (void *)0;
}

int main(void)
{
	srand((unsigned int)time(NULL));
	set_disp_mode(STDIN_FILENO,0);
	system("stty -icanon");
	initfood();
	pthread_t showtid,movetid;
	pthread_create(&showtid,NULL,show,NULL);
	//pthread_create(&movetid,NULL,move,NULL);
	//pthread_create(&movetid,NULL,foodmove,NULL);
	pthread_create(&movetid,NULL,findfood,NULL);
	while(1){};
	return 0;
}









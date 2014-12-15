#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<limits.h>
#include<signal.h>
#include "job.h"
#include "weather.h"

volatile int day=1;
int summoney=0;
char *weather="          ";
struct people_struct *head=NULL,*work,*another,*another2,*another3,*dead_another;
int isalive[MAX_PEOPLE+1];
int noused[MAX_PEOPLE+1];

struct people_struct *init_people(struct people_struct *father,struct people_struct *mother,int no)
{	
	if(!no) return NULL;	
	struct people_struct *q=(struct people_struct *)malloc(sizeof(struct people_struct));
	q->generation=mother->generation+1;
	q->birthday=day;
	q->no=no;
	q->life=LIFE_BASE+NICE+father->strong+mother->strong-40+day;
	q->age=day;
	q->state=HEALTH;
	if(rand()%2) q->sex=FEMALE; else q->sex=MALE;
	q->no_of_another=0;
	q->strong=q->life-2*LIFERANGE+1-day;
	if(q->strong<=MINSTRONG||q->strong>=MAXSTRONG) return NULL;
        q->married=NOMARRIED;
        q->child_time=0;
        q->child_no=0;
        q->father_no=father->no;
	q->mother_no=mother->no;
			q->power=rand()%100+1;
			q->quick=rand()%100+1;
			q->intel=rand()%100+1;
			q->job=0;
			q->firsttodo=0;
			q->happy=HAPPY_BASE;
			q->skillful=SKILLFUL_BASE;
			q->money=MONEY_BASE;
	q->workx=q->worky=0;
	q->homex=mother->homex;
	q->homey=mother->homey;
        isalive[no]=ISALIVE;
        noused[no]=ISUSED;
	mother->child_no=no;
	father->child_no=no;
	mother->state=HEALTH;
	mother->child_time=0;
	return q;
}
	
void init_head()
{
	head->generation=0;
	head->birthday=0;
	head->no=0;
	head->life=INT_MAX;
	head->age=0;
	head->state=GOD;
	head->strong=INT_MAX;
}
		
int init()
{
	int i=1;
	head=(struct people_struct *)malloc(sizeof(struct people_struct));
//	child=(struct people_struct *)malloc(sizeof(struct people_struct));
	if(!head)
		return 1;
	init_head();
	struct people_struct *q=head;
	for(;i<=MAX_PEOPLE;i++)
	{
		if(!q->next)
			q->next=(struct people_struct *)malloc(sizeof(struct people_struct));
		if(!q->next)
			return 1;
		q->next->prev=q;
		q=q->next;
			q->generation=1;
			q->birthday=day;
			q->no=i;
			q->life=LIFE_BASE+NICE+rand()%LIFERANGE-LIFERANGE/2;
			q->age=INIT_AGE;
			q->state=HEALTH;
			if(rand()%2)
				q->sex=FEMALE;
			else
				q->sex=MALE;
			q->no_of_another=0;
			q->strong=q->life-2*LIFERANGE+1;
			q->married=NOMARRIED;
			q->child_time=0;
			q->child_no=0;
			q->father_no=q->mother_no=0;
			q->power=rand()%100+1;
			q->quick=rand()%100+1;
			q->intel=rand()%100+1;
			q->job=0;
			q->firsttodo=0;
			q->happy=HAPPY_BASE;
			q->skillful=SKILLFUL_BASE;
			q->money=MONEY_BASE;
			q->homex=q->homey=q->workx=q->worky=0;
		isalive[i]=ISALIVE;
		noused[i]=ISUSED;
	}
	int j;
	for(i=0;i<MAX_PEOPLE;i++)
		for(j=0;j<MAX_PEOPLE;j++)
			people_adj[i][j]=0;
	return 0;
}
void over()
{
	struct people_struct *q=head;
	for(;q;q=q->next)
	{
		free(q->other);free(q->child);
		free(q);
	}
}
int percent(int p)
{
        if(p<=100)
                return (rand()<INT_MAX/(100/p));
        else
                return 0;
}

int find_index()
{
	int i;
	for(i=1;i<=MAX_PEOPLE;i++)
	{
		if(noused[i]==NOUSED)
			return i;
	}
	return 0;
}
extern struct people_struct *find_node(int no)
{
	struct people_struct *p=head->next;
	for(;p;p=p->next)
	{
		if(p->no==no)
			return p;
	}
	return NULL;
}
int ill()
{
	int ret;
	return(rand()<(int)(INT_MAX/ILLPERCENT));
}

void people_dead(struct people_struct *node)
{
	noused[node->no]=NOUSED;
	if(node->married)
	{
		dead_another=find_node(node->no_of_another);
		dead_another->married=NOMARRIED;
		dead_another->no_of_another=0;
	}
	if(node->next)
	{
		node->prev->next=node->next;
		node->next->prev=node->prev;
		isalive[node->no]=ISDEAD;
		node->state=DEAD;
	}
	else
	{
		node->prev->next=NULL;
		isalive[node->no]=ISDEAD;
	}	
}
void give_money(struct people_struct *node)
{
	if(node->child)
		node->child->money+=node->money;
}

void people_ill(struct people_struct *node)
{
	node->life-=ILL_LIFE;
	node->state=ILL;
}
void people_married()
{
	another=head->next;
	if(work->strong<=100&&rand()<(int)(INT_MAX/MARRIED_PERCENT/(100/work->strong))&&work->married==NOMARRIED&&MARRIEDAGE(work)&&ISHEALTH(work))
	{
		for(another=head->next;another;another=another->next)
		{
			if(another->strong<=100&&rand()<(int)(INT_MAX/(100/another->strong))&&(work->sex!=another->sex)&&another->married==NOMARRIED&&work->married==NOMARRIED&&MARRIEDAGE(another)&&ISHEALTH(another))
			{
					work->no_of_another=another->no;
					another->no_of_another=work->no;
					another->married=MARRIED;
					work->married=MARRIED;
					another->other=work;
					work->other=another;
					if(work->generation==GE&&another->generation==GE)
						people_adj[work->no-1][another->no-1]=1;
					printf("NO%i(%c) get married with NO%i(%c)\n",work->no,work->sex?'M':'F',another->no,another->sex?'M':'F');
					break;
			}
		}
	}
}

void people_pergnant()
{
	if(work->married)
	{
	another2=find_node(work->no_of_another);
	if(work->strong<=100&&another2->strong<=100&&work->state!=PERGNANT&&another2->state!=PERGNANT&&rand()<(int)(INT_MAX/PERGNANT_PERCENT/(100/work->strong))&&rand()<(int)(INT_MAX/PERGNANT_PERCENT/(100/another2->strong))&&ISHEALTH(another2)&&ISHEALTH(work)&&BEARAGE(work)&&BEARAGE(another2))
	{
		if(work->sex==FEMALE)
		{
	        	printf("NO%i(%c) become pergnant\n",work->no,work->sex?'M':'F');
			work->state=PERGNANT;
			work->child_time=work->age+CHILDDAY;
		}
		else
		{
			printf("NO%i(%c) become pergnant\n",another2->no,another2->sex?'M':'F');
			another2->state=PERGNANT;
			another2->child_time=another2->age+CHILDDAY;
		}
	}
	}//end  if
}

void people_come()
{
	if(work->state==PERGNANT)
	{
	struct people_struct *child;
	//another3=find_node(work->no_of_another);
	another3=work->other;
	int i=find_index();
	if(day-work->child_time>=0&&day-work->child_time<=10&&i)
	{
		child=init_people(another3,work,i);
		if(child)		
		{
			printf("NO%i(%c) and NO%i(%c) have a child NO%i(%c)\n",another3->no,'M',work->no,'F',child->no,ISMALE(child));
			child->next=head->next;
			child->next->prev=child;
			head->next=child;
			child->prev=head;
			work->child=another3->child=child;
		}
		else
		{
			printf("child NO%i dead,because strong\n",i);
			work->child_time=0;
			work->state=HEALTH;
		}
			
	}
	else if(day-work->child_time<0||(day-work->child_time>=0&&day-work->child_time<=10&&!i))
	{
		sleep(0.25);
	}
	else
	{
		printf("NO%i's child dead,because full\n",work->no);
                work->child_time=0;work->state=HEALTH;
	}
}
}
			
void god()
{
	register int i=1;
	init_map();
//	printmap();
	while(i)
	{	
		get_weather();
		printf("\033[35mNO%i day %s\033[0m\n",day,weather);
		i=0;
//		print_job();
		for(work=head->next;work;i++,work=work->next)
		{
			get_job();
			sleep(SLEEPTIME);
			people_married();
			sleep(SLEEPTIME);	
			people_pergnant();
			sleep(SLEEPTIME);
			people_come();
			sleep(SLEEPTIME);
			work->age+=1;
			if(ill())
			{
				printf("NO%i(%c) get ill\n",work->no,work->sex?'M':'F');
				people_ill(work);
			}
			if(work->age>=work->life)
			{	
				work->state&=~GUILTY;//god will brush hisguilty
				switch(work->state)
				{
					case HEALTH:case PERGNANT:
						printf("NO%i(%c)%i dead,live %i days,because old\n",work->no,work->sex?'M':'F',work->generation,day-work->birthday);
						people_dead(work);
						give_money(work);
						break;
					case ILL:
						printf("NO%i(%c)%i dead,live %i days,because ill\n",work->no,work->sex?'M':'F',work->generation,day-work->birthday);
						people_dead(work);
						give_money(work);
						break;
					case KILL:
						printf("NO%i(%c)%i dead,live %i days,because kill someone\n",work->no,work->sex?'M':'F',work->generation,day-work->birthday);
						people_dead(work);
						break;
					case BEKILL:
						printf("NO%i(%c)%i dead,live %i days,because is killed\n",work->no,work->sex?'M':'F',work->generation,day-work->birthday);
						people_dead(work);
						give_money(work);
						break;
						
					defalut:
						goto over;
				}
			
			}
			
		}
		if(head->next)
			day++;
		else
			goto over;
		sleep(SLEEPTIME);
	}
over:	printf("all people die,%i day\n",day);
}

void handler(int signo)  
{
        if(signo==SIGINT)
        {
                printf("WELCOME TO GOD MODE,PLEASE DO WHATEVER YOU WANT\n");
                char temp;
                scanf("%c",&temp);
                switch(temp)
                {
                        case 'k':
                                kill_people();break;
                        case 'i':
                                insert_people();break;
                        case 'c':
                                change_people();break;
                        default:
                                printf("COMMANDS INVAILD\n");
                }
        }
}

void change_print_adj()
{
	FILE *fp=fopen("people.txt","w");
	int i,j;
	for(i=0;i<MAX_PEOPLE;i++)
		for(j=0;j<MAX_PEOPLE;j++)
			people_adj[i][j]=people_adj[j][i];
	for(i=0;i<MAX_PEOPLE;i++){
		for(j=0;j<MAX_PEOPLE;j++)
			fprintf(fp,"%d ",people_adj[i][j]);
		fprintf(fp,"\n");
	}
	fclose(fp);
}
int main(void)
{

	if(signal(SIGINT, handler) == SIG_ERR)
        {
                printf("can't set handler for SIGINT\n");
                exit(1);
        } 	
	srand((unsigned int)time(NULL));
	if(!init())
		god();
	change_print_adj();
	over();
	return 0;
}
			
						

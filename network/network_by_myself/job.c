#include <stdio.h>
#include <stdlib.h>
#include "job.h"

void do_policeman()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	struct people_struct *p=head->next,*q;
	for(;p;p=p->next)
	{
		if(p->job==KILLER&&p->skillful&&percent((p->skillful+work->skillful)*5))
		{
				printf("NO%i policeman catch the killerNO%i\n",work->no,p->no);
				summoney+=(int)p->money/2;
				work->money+=(int)p->money/2;
				work->skillful+=1;
				p->state=KILL;
				p->life=day;
				for(q=head->next;q;q=q->next)
					q->happy+=(int)HAPPY_BASE/10;
				if(work->generation==GE&&p->generation==GE)
					people_adj[work->no-1][p->no-1]=1;
		}
	}
	work->money+=10;
}		

void do_sport()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
		work->life+=(int)INIT_AGE/10;
	}
	if(!day%10&&percent((int)work->power/5+work->skillful))
	{
		printf("congratulation,NO%i get the champion in the OYLIMPIC games\n",work->no);
		work->money+=100;
		work->happy+=(int)HAPPY_BASE/10;
		work->skillful+=1;
	}
	work->money+=5;
}
void do_cleaner()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	struct people_struct *p=head->next;
	for(;p;p=p->next)
		p->happy+=(int)HAPPY_BASE/100;
	if(percent(10))
	{
		printf("NO%i catch 10 yuan in the street\n",work->no);
		work->money+=10;
		work->happy+=(int)HAPPY_BASE/20;
	}
	work->money+=5;
}
void do_driver()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	int i;
	i=rand()%MAX_PEOPLE+1;
	struct people_struct *p=find_node(i);
	if(p&&p->money>=10&&percent(50))
	{
		p->money-=10;
		p->life+=1;
		p->happy+=(int)HAPPY_BASE/10;
		work->money+=10;
		printf("NO%i drive NO%i,help save a lot time\n",work->no,p->no);
		if(work->generation==GE&&p->generation==GE)
			people_adj[work->no-1][p->no-1]=1;		
	}
}
void do_carpenter()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	while(work->skillful<200)
	{
		int t1,t2;
		t1=rand()%MAPX+1;
		t2=rand()%MAPY+1;
		if(map[t1][t2]==TREE)
		{
			work->skillful+=1000;
			printf("NO%i get many trees\n",work->no);
			if(map[t1+1][t2]==ANIMAL||map[t1][t2+1]==ANIMAL||map[t1-1][t2]==ANIMAL||map[t1][t2-1]==ANIMAL)
			{
				printf("NO%i is attacked by beasts\n",work->no);
				work->life-=10;
				work->happy-=(int)HAPPY_BASE/10;
			}
		}
	}
}
void do_worker()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
}
void do_machanic()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
}
void do_clerk()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	work->money+=work->skillful;
	work->skillful=0;
	work->skillful+=10;
}
extern char *weather;
void do_farmer()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	if(!strcmp(weather,"sunny"))
	{
		if(percent(20))
		{
			printf("it is a good day,farmer NO%i have a good harvest\n",work->no);
			work->skillful+=100;
			work->happy+=(int)HAPPY_BASE/20;
		}
	}
}
void do_soldier()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	if(percent(20))
	{
		printf("soldierNO%i exercise everyday,get more strong\n",work->no);
		work->power+=5;
	}
	work->money+=15;
}

void do_actor()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	if(day%4==0)
	{
		printf("NO %i perform a nice TV SHOW\n",work->no);
		struct people_struct *p;
		for(p=head->next;p;p=p->next)
		{	if(work->workx==p->workx&&work->worky==p->worky&&p->money>=5)
			{
				p->happy+=HAPPY_BASE/10;
				p->money-=5;
				work->money+=5;
				if(work->generation==GE&&p->generation==GE)
					people_adj[work->no-1][p->no-1]=1;
			}
		}
	}		
}
void do_clown()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
		if(day%5==0)
		{
			printf("NO %i perform a nice circus show\n",work->no);
			struct people_struct *p;
			for(p=head->next;p;p=p->next)
			{
				if(work->workx==p->workx&&work->worky==p->worky&&p->money>=5)
				{
					p->happy+=HAPPY_BASE/10;
					p->money-=5;
					work->money+=5;
					if(work->generation==GE&&p->generation==GE)
						people_adj[work->no-1][p->no-1]=1;
				}
			}
		}
}
void do_barber()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	struct people_struct *p;
	p=find_node(rand()%MAX_PEOPLE+1);
	if(p&&day-p->birthday>=20&&p->money>=10)
	{
		if(p->sex==MALE)
			printf("NO%i helpNO%i scrape beard\n",work->no,p->no);
		else
			printf("NO%i help NO%i cut hair\n",work->no,p->no);
		p->strong+=5;
		p->happy+=HAPPY_BASE/10;
		p->money-=10;
		work->money+=10;
		if(work->generation==GE&&p->generation==GE)
				people_adj[work->no-1][p->no-1]=1;
	}	
}
void do_cook()
{
	FIRSTTODO
 	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	struct people_struct *p,*q;
	for(p=head->next;p;p=p->next)
	{
		if(p->job==FARMER&&p->skillful)
		{
			p->money+=p->skillful*0.5;
			work->skillful+=p->skillful;
			work->money-=p->skillful*0.5;
			p->skillful=0;
			if(work->generation==GE&&p->generation==GE)
				people_adj[work->no-1][p->no-1]=1;
		}
	}
	int count=0;
	while(work->skillful>0)
	{
		q=find_node(rand()%MAX_PEOPLE+1);
		if(q&&q->money>8)
		{
			work->money+=8;
			work->skillful-=12;
			q->money-=8;
			q->happy=(int)HAPPY_BASE/20;
			count++;
			if(work->generation==GE&&q->generation==GE)
				people_adj[work->no-1][q->no-1]=1;
		}
	}
	if(count>0)
		printf("NO%i serve %i people food\n",work->no,count);		
}
void do_dancer()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	if(!strcmp(weather,"cloudy"))
	{
	struct people_struct *p;
	int j=rand()%(MAX_JOB-1)+1;
	for(p=head->next;p;p=p->next)
	{
		if(p->job==j)
			p->happy+=HAPPY_BASE/5;
		if(work->generation==GE&&p->generation==GE)
			people_adj[work->no-1][p->no-1]=1;
	}
	work->money+=10;
	printf("NO%i have a dance with many people(%s)\n",work->no,jobname[j]);
	}
}
void do_detective()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	struct people_struct *p;
	p=find_node(rand()%MAX_PEOPLE+1);
	if(p&&percent(20))
	{
		if(p->other)
		{
			printf("NO%i find NO%i have another people\n",work->no,p->no);
			p->state|=GUILTY;
			p->happy-=HAPPY_BASE/10;
		    if(work->generation==GE&&p->generation==GE)
				people_adj[work->no-1][p->no-1]=1;			
		}
		else if(p->job==UMPLOY)
		{
			printf("NO%i find NO%i steal something\n",work->no,p->no);
			p->state|=GUILTY;
			p->happy-=HAPPY_BASE/10;
			if(work->generation==GE&&p->generation==GE)
				people_adj[work->no-1][p->no-1]=1;
		}
		work->money+=40;

	}
}
void do_killer()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	struct people_struct *p=head->next,*q;
	for(;p;p=p->next)
	{
		if(p->job!=POLICEMAN&&percent(p->skillful+1)&&percent(5))
		{
				printf("NO%i kill the NO%i\n",work->no,p->no);
				work->money+=p->money;
				work->skillful+=1;
				p->state=BEKILL;
				p->life=day;
				for(q=head->next;q;q=q->next)
					q->happy-=(int)HAPPY_BASE/10;
				if(work->generation==GE&&p->generation==GE)
					people_adj[work->no-1][p->no-1]=1;
		}
	}
	
}
void do_lawyer()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	struct people_struct *p;
	for(p=head->next;p;p=p->next)
	{
		if(p->state&GUILTY)
		{
			if(p->money>=50)
			{
				p->money-=50;
				p->state&=~GUILTY;
				p->happy+=HAPPY_BASE/10;
				work->money+=50;
				printf("NO%i help NO%i become annocent\n",work->no,p->no);	
				if(work->generation==GE&&p->generation==GE)
					people_adj[work->no-1][p->no-1]=1;
			}
		}
	}
}
void do_doctor()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	struct people_struct *p;
	int temp=work->skillful+1,count=100;
	while(temp&&count)
	{
		p=find_node(rand()%MAX_PEOPLE+1);
		if(p&&p->money>=20&&p->state==ILL)
		{
			printf("NO%i cure NO%i illness\n",work->no,p->no);
			p->state=HEALTH;
			p->money-=20;
			p->life+=10;
			p->happy+=HAPPY_BASE/10;
			work->money+=20;
			work->skillful++;
			temp--;
			if(work->generation==GE&&p->generation==GE)
				people_adj[work->no-1][p->no-1]=1;
		}
		count--;
	}
				
}
void do_gardener()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	struct people_struct *p;
	int job=rand()%(MAX_JOB-1)+1;
	if(!strcmp(weather,"windy"))
	{
		for(p=head->next;p;p=p->next)
		{
			if(p->job==job)
				p->happy+=HAPPY_BASE/10;
		}
		work->money+=20;
		printf("NO%i give people flowers(%s)\n",work->no,jobname[job]);
	}			
	
}
void do_umploy()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	if(work->state==HEALTH&&percent(20))
		__get_job(find_best());		
}

void do_teacher()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	struct people_struct *p;int count=0;
	for(p=head->next;p;p=p->next)
	{
		if(!p->job)
		{
			p->workx=work->workx;
			p->worky=work->worky;
			count++;
			switch(rand()%3)
			{
				case 0:p->power++;break;
				case 1:p->quick++;break;
				case 2:p->intel++;break;
				default:p->happy++;
			}
			if(work->generation==GE&&p->generation==GE)
				people_adj[work->no-1][p->no-1]=1;
		}
	}
	if(count)
		printf("NO%i teach %i students\n",work->no,count);
	work->money+=20;
		
}
#define MAX_GAME 4
char gamename[MAX_GAME+1][10]={{},{"rthree"},{"DOTA"},{"LOL"},{"WAR3"}};
int complete[MAX_GAME+1]={0,0,0,0,0};
int jindu[MAX_GAME+1]={0,0,0,0,0};
void do_coder()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	int i;
	for(i=1;i<=MAX_GAME;i++)
	{
		if(complete[i])
		{
			jindu[i]++;
		}
		if(jindu[i]==100)
		{
			printf("NO %icomplete the game %s\n",work->no,gamename[i]);
			work->happy+=HAPPY_BASE/4;
			work->money+=50;
		}
	}
	work->money+=20;
	
}
void do_scientist()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
}
void do_fete()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	struct people_struct *p=find_node(rand()%MAX_PEOPLE+1);
	if(p)
	{
		p->life+=3;
		printf("NO%i increase NO%i life 3days\n",work->no,p->no);
		if(work->generation==GE&&p->generation==GE)
			people_adj[work->no-1][p->no-1]=1;
	}
	p=find_node(rand()%MAX_PEOPLE+1);
	if(p)
	{
		p->happy+=HAPPY_BASE/10;
		printf("NO%i increase NO %i happy %i\n",work->no,p->no,HAPPY_BASE/10);
		if(work->generation==GE&&p->generation==GE)
			people_adj[work->no-1][p->no-1]=1;
	}
	p=find_node(rand()%MAX_PEOPLE+1);
	if(p&&p->state!=HEALTH)
	{
		p->state=HEALTH;
		printf("NO%i let NO %i healthy\n",work->no,p->no);
		if(work->generation==GE&&p->generation==GE)
			people_adj[work->no-1][p->no-1]=1;		
	}
	work->money+=80;

}
void do_officer()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	struct people_struct *p;int count=0;
	for(p=head->next;p;p=p->next)
	{
		if(p->job==CLERK||p->job==STAFF)
		{
			work->money+=p->skillful/5;
			p->skillful-=p->skillful/5;
			p->happy-=HAPPY_BASE/50;
			count++;
			if(work->generation==GE&&p->generation==GE)
				people_adj[work->no-1][p->no-1]=1;
		}
	}
	if(count)
		printf("NO%i get money from %i clerks and staffs\n",work->no,count);
	work->money+=10;
}
void do_staff()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	work->money+=work->skillful;
	work->skillful=0;
	work->skillful+=10;
}
void do_translator()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	/* this job i will write it in the V3.0 maybe,it can communicate with other country,if no translator two will fight*/
}
void do_gamer()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	int i;
	if(percent(50))
	{
	for(i=1;i<=MAX_GAME;i++)
	{
		if(complete[i]&&jindu[i]==100)
		{
			struct people_struct *p;int no[10];int count=1;
			for(p=head->next;p;p=p->next)
			{
				if(p->job==GAMER)
				{
					no[count]=p->no;
					count++;
					if(work->generation==GE&&p->generation==GE)
						people_adj[work->no-1][p->no-1]=1;
				}
			}
			int a=rand()%count;
			if(a)
			{
				find_node(no[a])->money+=50;
				find_node(no[a])->happy+=HAPPY_BASE/20;
				printf("NO%i win the game %s\n",no[a],jobname[i]);
			}
		}
	}
	}
		
	
}
void do_accountant()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	struct people_struct *p;int sum=0;
	for(p=head->next;p;p=p->next)
	{
		sum+=p->money;
	}
	work->money+=30;
				
		printf("NO%i report sum money %i\n",work->no,sum);
}
void do_designer()
{
	FIRSTTODO
	{
		printf("\033[31mNO%i become %s\033[0m\n",work->no,jobname[work->job]);	
		work->firsttodo=1;
	}
	if(percent(50))
	{
		int i;
		i=rand()%MAX_GAME+1;
		if(!complete[i])
		{
			printf("NO%i design a game %s\n",work->no,gamename[i]);
			complete[i]=1;
			work->happy+=HAPPY_BASE/2;
			work->money+=100;
		}
	}
	work->money+=30;
	
}

int find_best()
{
	int a=work->power>work->quick?work->power:work->quick;
	int b=a>work->intel?a:work->intel;
	if(b==work->power)	return ISPOWER;
	else if(b==work->quick) return ISQUICK;
	else                    return ISINTEL;
}
void __get_job(int best)
{
	int i;
	switch(best)
	{
		case ISPOWER:
		i=rand()%MAX_PEOPLE+1;
		if(i<=8*PERCENT) {work->job=POLICEMAN;work->jobfunction=do_policeman;}
		else if(i<=12*PERCENT) {work->job=SPORT;work->jobfunction=do_sport;}
		else if(i<=19*PERCENT) {work->job=CLEANER;work->jobfunction=do_cleaner;}
		else if(i<=39*PERCENT) {work->job=DRIVER;work->jobfunction=do_driver;}
		else if(i<=43*PERCENT) {work->job=CARPENTER;work->jobfunction=do_carpenter;}
		else if(i<=58*PERCENT) {work->job=WORKER;work->jobfunction=do_worker;}
		else if(i<=63*PERCENT) {work->job=MACHANIC;work->jobfunction=do_machanic;}
		else if(i<=75*PERCENT) {work->job=CLERK;work->jobfunction=do_clerk;}
		else if(i<=95*PERCENT) {work->job=FARMER;work->jobfunction=do_farmer;}
		else {work->job=SOLDIER;work->jobfunction=do_soldier;}
		break;
		
		case ISQUICK:
		i=rand()%MAX_PEOPLE+1;
		if(i<=4*PERCENT) {work->job=ACTOR;work->jobfunction=do_actor;}
		else if(i<=12*PERCENT) {work->job=BARBER;work->jobfunction=do_barber;}
		else if(i<=27*PERCENT) {work->job=COOK;work->jobfunction=do_cook;}
		else if(i<=31*PERCENT) {work->job=DANCER;work->jobfunction=do_dancer;}
		else if(i<=35*PERCENT) {work->job=DETECTIVE;work->jobfunction=do_detective;}
		else if(i<=41*PERCENT) {work->job=KILLER;work->jobfunction=do_killer;}
		else if(i<=46*PERCENT) {work->job=LAWYER;work->jobfunction=do_lawyer;}
		else if(i<=52*PERCENT) {work->job=DOCTOR;work->jobfunction=do_doctor;}
		else if(i<=64*PERCENT) {work->job=GARDENER;work->jobfunction=do_gardener;}
		else if(i<=80*PERCENT) {work->job=CLOWN;work->jobfunction=do_clown;}
		else {work->job=UMPLOY;work->jobfunction=do_umploy;}
		break;
			
		case ISINTEL:
		i=rand()%MAX_PEOPLE+1;
		if(i<=6*PERCENT) {work->job=TEACHER;work->jobfunction=do_teacher;}
		else if(i<=21*PERCENT) {work->job=CODER;work->jobfunction=do_coder;}
		else if(i<=25*PERCENT) {work->job=SCIENTIST;work->jobfunction=do_scientist;}
		else if(i<=28*PERCENT) {work->job=FETE;work->jobfunction=do_fete;}
		else if(i<=34*PERCENT) {work->job=OFFICER;work->jobfunction=do_officer;}
		else if(i<=64*PERCENT) {work->job=STAFF;work->jobfunction=do_staff;}
		else if(i<=70*PERCENT) {work->job=TRANSLATOR;work->jobfunction=do_translator;}
		else if(i<=80*PERCENT) {work->job=GAMER;work->jobfunction=do_gamer;}
		else if(i<=85*PERCENT) {work->job=ACCOUNTANT;work->jobfunction=do_accountant;}
		else if(i<=93*PERCENT) {work->job=DESIGNER;work->jobfunction=do_designer;}
		else {work->job=UMPLOY;work->jobfunction=do_umploy;}
		break;
		
		default:
		work->job=0;
	}
	int temp;
	temp=rand()%BUILDNUM;
	work->workx=build[temp].x;
	work->worky=build[temp].y;
}
void get_job()
{
	if(!work->job&&day-work->birthday>=rand()%10+20)
		__get_job(find_best());
	if(work->job)
		work->jobfunction();
}
void print_job()
{
	if(day==22){
	struct people_struct *p=head->next;
	for(;p;p=p->next)
	{
		printf(" %i ",p->job);
	}
}}

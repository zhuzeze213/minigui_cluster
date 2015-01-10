#ifndef ARG_H
#define ARG_H

#define MAX_PEOPLE 100
#define LIFE_BASE 100
#define INIT_AGE 0 
#define MONEY_BASE 100
#define HAPPY_BASE 100
#define SKILLFUL_BASE 0
#define ILL_LIFE 20

#define ISALIVE 1
#define ISDEAD 0

#define ISUSED 1
#define NOUSED 0
/* the state of people */
#define HEALTH 0
#define ILL 1
#define DEAD 2
#define PERGNANT 4
#define KILL 8
#define BEKILL 16
#define GUILTY 32
#define GOD 64

#define ILLPERCENT 100/4
/* 1s represent 1day */
#define SLEEPTIME 0.25
#define NICE 0  //random to change people's life 
#define LIFERANGE 40

#define MINSTRONG 0
#define MAXSTRONG 100
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define MALE 1
#define FEMALE 0
#define ISMALE(p) (p)->sex?'M':'F'
#define MARRIED 1
#define NOMARRIED 0
#define MARRIEDBARRIER 50
#define MINMARRIEDAGE 20
#define MAXMARRIEDAGE 40
#define MARRIEDAGE(p) (p)->age>=MINMARRIEDAGE+(p)->birthday&&(p)->age<=MAXMARRIEDAGE+(p)->birthday
#define ISHEALTH(p) (p)->state==HEALTH
/* the following two percents is really important to human */
#define MARRIED_PERCENT 30 //10
#define PERGNANT_PERCENT 5  //3
#define MINBEARAGE 30   //give birth to
#define MAXBEARAGE 70
#define BEARAGE(p) (p)->age>=MINBEARAGE+(p)->birthday&&(p)->age<=MAXBEARAGE+(p)->birthday
#define CHILDDAY 10
struct people_struct
{
/*personal information*/
	int generation;
	int birthday;
	int no;
	int life;
	int age;
	int state;
	int sex;
	int no_of_another;
	int strong;
/*social relationship*/
	int married;
	int child_time;
	int child_no;
	int father_no;
	int mother_no;
	struct people_struct *next;
	struct people_struct *prev;
	struct people_struct *other;
	struct people_struct *child;
/*identical skill and advantages*/
	int power;
	int quick;
	int intel;
	int job;
	void (*jobfunction)(void);
	int firsttodo;
/*add so many job.so i should add some attributes*/
	int happy;
	int skillful; 
	int money;
	int workx,worky;
	int homex,homey;
	
}__attribute__((aligned(4)));

struct people_struct *find_node(int);
int find_index();
struct people_struct *init_people(struct people_struct *,struct people_struct *,int);
void people_dead(struct people_struct *);
struct people_struct *head,*work;
volatile int day;
int summoney;		
int percent(int);

/* i want to define a 2dimension matrix to record the relationship from people */
int people_adj[MAX_PEOPLE][MAX_PEOPLE];
#define GE 1

#endif

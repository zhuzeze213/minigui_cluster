#ifndef JOB_H
#define JOB_H
#include "arg.h"
#include "map.h"
//#include "jobstruct.h"
/* following is all jobs */

#define POWERJOB 1
/*power jobs*/
#define POLICEMAN 1
#define CARPENTER 2
#define CLERK 3
#define SPORT 4
#define WORKER 5
#define FARMER 6
#define CLEANER 7
#define MACHANIC 8
#define SOLDIER 9
#define DRIVER 10

#define QUICKJOB 11
/*quick jobs*/
#define ACTOR 11
#define CLOWN 12
#define BARBER 13
#define COOK 14
#define DANCER 15
#define DETECTIVE 16
#define KILLER 17 //IS A GOOD JOB I THINK
#define LAWYER 18
#define DOCTOR 19
#define GARDENER 20
#define UMPLOY 31

#define INTELJOB 21
/*intel jobs*/
#define TEACHER 21
#define CODER 22
#define SCIENTIST 23
#define FETE 24
#define OFFICER 25
#define STAFF 26
#define TRANSLATOR 27
#define GAMER 28
#define ACCOUNTANT 29
#define DESIGNER 30

#define MAX_JOB 31
#define JOB_LENGTH 15
#define ISPOWER 1
#define ISQUICK 2
#define ISINTEL 3
#define PERCENT (MAX_PEOPLE/100)

#define FIRSTTODO if(!work->firsttodo)
void get_job();
void __get_job(int);
int find_best();
static char jobname[MAX_JOB+1][JOB_LENGTH]=
{{},{"policeman"},{"carpenter"},{"clerk"},{"sport"},{"worker"},{"farmer"},{"cleaner"},{"machanic"},{"soldier"},
{"driver"},{"actor"},{"clown"},{"barber"},{"cook"},{"dancer"},{"detective"},{"killer"},{"lawyer"},{"doctor"},
{"gardener"},{"teacher"},{"coder"},{"scientist"},{"fete"},{"officer"},{"staff"},{"translator"},{"gamer"},
{"accountant"},{"designer"},{"umploy"}};
/* following all is job functions  my god so many */
#endif

#ifndef MYSTD_H
#define MYSTD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({			\
        const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
        (type *)( (char *)__mptr - offsetof(type,member) );})
		
# define MAX(a, b)	(((a) > (b))? (a) : (b))

# define MIN(a, b)	(((a) < (b))? (a) : (b))

#define swap(a,b)  ({(a)+=(b); (b)=(a)-(b); (a)=(a)-(b);})

#define ERROR -1
#define DONE 1
#define BOOL int
#define NO_DIRECT 0
#define YE_DIRECT 1

#define NO_POWER 0
#define YE_POWER 0

#define BUFFERSIZE 4096
#define TMPFILE "../tmp/fcm.txt"
struct network
{
	int **adj;
	int row;
	int column;
	int node;
	int edge;
	BOOL direct;
	BOOL power;
};
/* network.c */
int *init_matrix(int num);
void free_matrix(int **matrix);
double *init_matrix_double(int num);
void free_matrix_double(double **matrix);
int **init_2_matrix(int row,int column);
void free_2_matrix(int ***matrix,int row);
double **init_2_matrix_double(int row,int column);
void free_2_matrix_double(double ***matrix,int row);

int copy_2_matrix(int **old,int ***new,int row,int column);
int copy_2_matrix_double(double **old,double ***new,int row,int column);
void print_matrix_double(double *adj,int length);
void print_2_matrix_double(double **adj,int row,int column);

/* matlab.c */
int size(int ***matrix,int num);
int length(int ***matrix);
int *find(int *matrix,int column);
int fill(int ***adj,int num,int row,int column);
int fill_double(double ***adj,double num,int row,int column) ;
int **zeros(int row,int column);
double **zeros_double(int row,int column);
int **ones(int row,int column);
double **ones_double(int row,int column);
double **rand_matlab(int row,int column);
int *sum(int **adj,int num,int row,int column);
double *sum_double(double **adj,int num,int row,int column);
int *row_num(int **adj,int num,int row,int column);
int *column_num(int **adj,int num,int row,int column);
int **transposition(int **matrix,int row,int column);
double **transposition_double(double **matrix,int row,int column);
int **create_diag(int *v,int n,int pos);
double **copy_double(double *old,int copy,int length);
double **matrix_operate_double(double **pri,double **beh,char ope,int row,int column);
double **matrix_operate_double_int_1(int **pri,double **beh,char ope,int row,int column);
double **matrix_multiply(double **pri,double **beh,int row1,int column1,int row2,int column2);
double **matrix_multiply_int_2(double **pri,int **beh,int row1,int column1,int row2,int column2);
void print_2_matrix_double_f(double **adj,int row,int column,char *filename);



#endif

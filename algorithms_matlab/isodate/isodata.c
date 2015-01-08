#include "../include/mystd.h"

#define MAXNUM  1000            //���ģʽ����
#define MAXDIM  1000             //���ģʽά��
#define K  0.5                       //����ʱʹ�õı�ֵ
#define MAXDOUBLE   1.0e20     //���˫����ֵ
#define N2 100

struct Pattern            //ģʽ�ṹ��
{
 int n;                //ģʽ���
 float s[MAXDIM];      //ģʽ����
 
};  
struct Cluster                   //��ṹ��           
{
    struct Pattern z;            //������
 int n;                       //���а�����ģʽ��Ŀ
    float avg_d;                 //ģʽ�����ĵ�ƽ������
 struct Pattern y[MAXNUM];    //ģʽ
    float sigma[MAXDIM];         //�����ı�׼��
 int max;                     //���ڼ�¼���ھ����׼��ʸ�����ķ����±�
 float sigma_max;             //���ڷ��������׼�����ֵ
};
int N=100;
struct Pattern x[N2];            //ȫ��ģʽ

int DIM=0;

//����Ϊ����������
int c=3;                          //Ԥ�ڵ�����
int Nc=1;                         //��ʼ�������ĸ���
int ON=1;                         //ÿһ�������������ģʽ����С�ڴ������ɵ������ࣩ
float OS=1;                       //���ڷ����ֲ��ı�׼�����ޣ����ڴ����ͷ��ѣ�
float  OC=4;                      //�������ļ����С�������ޣ�С�ڴ�������ϲ���
int L=1;                          //��ÿ�ε����п��Ժϲ������������
int I=4;                          //����������

struct Cluster w[N2];               //ȫ����
float  D[MAXNUM][MAXNUM];       //��������ļ�ľ���
float dis;                      //����ƽ������
int  iter=1;                    //��¼��������
int  i,j;                      //ѭ������

void InitPattern(int **adj,int row,int column)   //������ģʽ���г�ʼ��
{
	int i,j;
	for(i=0;i<row;i++){
		x[i].n=i;
		for(j=0;j<column;j++){
			x[i].s[j]=adj[i][j];
		}
	}
}
//����Ϊ�����õ��ĵ��ú���
void Init();
void ISODATA();
void InitCenter();
void Clustering();
float Distance(struct Pattern x1,struct Pattern x2);
struct Cluster Insert(struct Pattern a,struct Cluster b);                         
int CheckAndUnion();
void CalParameter();
struct Pattern CalCenter(struct Cluster a);
float Cal_D(int i);
void CalSigma();
int divide();
void CalCenterDis();
int UnionByOC();
void Union(int a,int b);
void PrintCluster();
int main(int argc,char *argv[])
{ 
struct network network;
	if(loadmatrix(argv[1],&network)){
c=atoi(argv[2]);
 N=network.row;
DIM=network.column;
 Init();
 
InitPattern(network.adj,N,DIM);
/* for(i=0;i<N;i++)                                         //��ӡ��������ʹ������
 {
  printf("\tX (%d): (",x[i].n);
  for(j=0;j<DIM-1;j++)
   printf("%3.2f,",x[i].s[j]);
  printf("%3.2f);\n",x[i].s[j]);
  
 }*/
 
    ISODATA();  	//ISODATA�������
	}
return 0;
}

void Init()                                                  //�����ṹ�������ʼ��������ֵ��
{
 int i,j,k,l;
 for(i=0;i<N;i++)
 {
  x[i].n=0;
  w[i].n=0;
  w[i].avg_d=0;
  w[i].max=0;
  w[i].sigma_max=0;
  w[i].z.n=0;
  for(j=0;j<MAXDIM;j++)
  {
   x[i].s[j]=0;
   w[i].sigma[j]=0;
   w[i].z.s[j]=0;
  }
  for(k=0;k<MAXNUM;k++)
  {
   w[i].y[k].n=0;
   for(l=0;l<MAXDIM;l++)
    w[i].y[k].s[l]=0;
  }
  
 }
 for(i=0;i<MAXNUM;i++)
  for(j=0;j<MAXNUM;j++)
   D[i][j]=0;
}
void InitCenter()                                            //�����ѡ����ʼ��������
{ 
 int i,j,k,l;
 for(j=0;j<Nc;j++)
 {
  
  w[j].z=x[j];
  w[j].z.n=0;
 }
}

void Clustering()                                           //����С����ԭ��ȫ��ģʽ����
{
 float temp=0.0,min=MAXDOUBLE;
 int i,j,l=0;
 for(j=0;j<Nc;j++)
 {
  w[j].n=0;
  w[j].z.n=0;
 }
 for(i=0;i<N;i++)
 {
  min=MAXDOUBLE;
  l=0;
  for(j=0;j<Nc;j++)
  {
   temp=Distance(x[i],w[j].z);
   
   if(min>temp)
   {
    min=temp;
    l=j;
    
   }
  }
  
  w[l]=Insert(x[i],w[l]);
 }
}
float Distance(struct Pattern x1,struct Pattern x2)         //��������ģʽ����ĺ���
{
 int i;
 float temp=0.0;
 for(i=0;i<DIM;i++)
  temp+=(x1.s[i]-x2.s[i])*(x1.s[i]-x2.s[i]);
 return sqrt(temp);
}
struct Cluster Insert(struct Pattern a,struct Cluster b)          //��ĳģʽ�����Ӧ��           
{
 b.n++;
 b.y[b.n-1]=a;
 return b;
 
 
}
int CheckAndUnion()   //����ON�жϺϲ�������w[j]��ģʽ��С��ON��ȡ�����ģ�Nc=Nc-1,ת��step2:
{
 int j=0,k;
 do
 {
  if(w[j].n<ON)
  {
   for(k=j;k<Nc;k++)
    w[k].z=w[k+1].z;
   Nc--;
   
   return 1;
  }
        j++;
 }while(j<Nc);
 
 return 0;
}
struct Pattern CalCenter(struct Cluster a)                       //��������
{
 int i,j;
 struct Pattern temp;
 for(j=0;j<DIM;j++)
  temp.s[j]=0;
 temp.n=0;
 for(i=0;i<a.n;i++)
 {  
  
  for(j=0;j<DIM;j++)
   temp.s[j]+=a.y[i].s[j];
 }
 
 for(i=0;i<DIM;i++)
 {
  temp.s[i]/=a.n;
  
 }
 return temp;
}
float Cal_D(int j)                    //�����ģʽ�����ĵ�ƽ������
{
 int i;
    float avg_d=0.0; 
 for(i=0;i<w[j].n;i++)
  avg_d+=Distance(w[j].y[i],w[j].z);
 avg_d/=w[j].n;
 w[j].avg_d=avg_d;
 return avg_d;
}
void CalParameter()                                      //��������������������ġ�����ƽ�������Լ�����ƽ������
{
 int i;
 struct Pattern temp;
 dis=0.0;  
 for(i=0;i<Nc;i++)
 {
  
  
  dis+=w[i].n*Cal_D(i);
  
 }
    dis/=N;
}
void CalSigma()                                                 //����������ھ���ı�׼��ʸ��
{
 int i,j,k;
 
 for(j=0;j<Nc;j++)
 {
  
  for(k=0;k<DIM;k++)
  {  
   float temp=0.0;
   for(i=0;i<w[j].n;i++)
   {
    struct Pattern z;
    //z=CalCenter(w[j]);
    temp+=(w[j].y[i].s[k]-w[j].z.s[k])*(w[j].y[i].s[k]-w[j].z.s[k]);
   }
   w[j].sigma[k]=sqrt(temp/w[j].n);
   if(w[j].sigma_max<w[j].sigma[k])
   {
    w[j].sigma_max=w[j].sigma[k];
    w[j].max=k;
   }
  }
  
 }
 
}
int divide()                                                      //�жϷ���
{
 int i,j,l;
 
 for(j=0;j<Nc;j++)
 {
  float sigma_temp=w[j].sigma_max;
  if((w[j].avg_d>dis)&&(w[j].n>2*(ON+1))||(Nc<=c/2))
  {
   i=w[j].max;  
   for(l=Nc;l>j;l--)
    w[l].z=w[l-1].z;
   w[j+1].z.s[i]-=K*sigma_temp;
   w[j].z.s[i]+=K*sigma_temp;
   Nc++;
   return 1;
  }
 }
 return 0;
}
void CalCenterDis()                                               //�����������ļ�ľ���
{
 int i,j;
 for(i=0;i<Nc-1;i++)
  for(j=i+1;j<Nc;j++)
   D[i][j]=Distance(w[i].z,w[j].z);
}
void Union(int a,int b)                        //������δ�ϲ���ʱ�����кϲ�
{
 int i;
 if((w[a].z.n<0)||(w[b].z.n<0))
  return ;
 
 for(i=0;i<DIM;i++)
  w[a].z.s[i]=(1/(w[a].n+w[b].n))*(w[a].z.s[i]*w[a].n+w[b].n*w[b].z.s[i]); 
 w[a].z.n=-1;
 w[b].z.n=-2;
 
 
}
int UnionByOC()                                              //����OC�жϺϲ�
{
 int i,j,k,l;
 int num=0;
    int flag=0;
 struct
 {
  float d;
  int i;
  int j;
 }Dmin[N];
 for(i=0;i<L;i++)
 {
  Dmin[i].d=OC;
  Dmin[i].i=-1;
  Dmin[i].j=-1;
 }
 for(i=0;i<Nc-1;i++)
  for(j=i+1;j<Nc;j++)
   if(D[i][j]<OC)
    for(k=0;k<L;k++)
     if(D[i][j]<Dmin[k].d)
     {
      for(l=L-1;l>k;l--)
       Dmin[l]=Dmin[l-1];
      Dmin[k].d=D[i][j];
      Dmin[k].i=i;
      Dmin[k].j=j;
      break;
     }
     for(i=0;i<L;i++)
      if(Dmin[i].i>-1&&Dmin[i].j>-1)
      {
     
       Union(Dmin[i].i,Dmin[i].j); 
       flag=1;
      }
      for(j=0;j<Nc;j++)
      { 
              if(w[j].z.n==-2)
       {
        for(k=j;k<Nc;k++)
         w[k].z=w[k+1].z;
        
        Nc--;
       }
      }
      return flag;
}
void PrintCluster()                                                       //��ӡ��ǰģʽ�������
{
 int i,j,k;
 for(i=0;i<Nc;i++)
 {
  printf("\t %d modules heart is:(",i+1);
//        for(j=0;j<DIM-1;j++)
//  printf("%3.2f,",w[i].z.s[j]);
  printf("%3.2f )\n",w[i].z.s[DIM-1]);
  printf("include the model:\n");
  for(k=0;k<w[i].n;k++)
  {
   printf("\tX (%d):(\n",w[i].y[k].n);
//   for(j=0;j<DIM-1;j++)
 //   printf("%3.2f,",w[i].y[k].s[j]);
 //  printf("%3.2f)\n",w[i].y[k].s[DIM-1]);
  }
  printf("\n");
 }
}
 
void ISODATA()
{
 int changed=1;
 int i;
start:                                                                      //�������
/* printf("\nset analyze control parameter:\n");
 printf("number of clusters c:");
 scanf("%d",&c);
 printf("initial heart of clusters(may not euqal with c):");
 scanf("%d",&Nc);
 printf("each module minmum number of models ON(miner than this number can't be a cluster):");
 scanf("%d",&ON);
 printf("standard deviation OS(biger can split):");
 scanf("%4f",&OS);
 printf("distance between modules OC(smaller can combine):");
 scanf("%4f",&OC);
 printf("can combine cluster each iteration LOG L: ");                
 scanf("%d",&L);
 printf("max iteration I�� ");
 scanf("%d",&I);
 printf("\n"); */
step1:
    InitCenter();
 
step2:
 changed=0;
    Clustering();
 if(iter==0)
  printf("\n---------------choose the heart of the modules---------------\n");
 else
  printf("----------------- %d iterations-----------------\n ",iter);
 PrintCluster();
 
step3:
 
 if(CheckAndUnion())
  goto step2;
 
step4:
 for(i=0;i<Nc;i++)
 {
  w[i].z=CalCenter(w[i]);        //�����������
 }
 CalParameter();                   //ÿ������������뿪�����ĵ�ƽ�������Լ����������뿪����Ӧ�������ĵ�ƽ������ 
step5:                                  //����iter,Nc�ж�ֹͣ�����ѻ��Ǻϲ�
 if(iter==I)
 {
  OC=0;
        goto step8;
 }
 if (Nc<=c/2)
  goto step6;
    if((Nc>=2*c)||iter%2==0)
  goto step8; 
step6:
 
 CalSigma();
step7:
 if(divide())
 {
  iter++;
  goto step2;
 }
step8:
 CalCenterDis();
step9:
 if(UnionByOC())
  changed=1;
 
 
step10:
 if(iter>=I)                                     //�ж�ѭ�������˳�
 {
  printf("--------------- %d iteration,reach the count--------------\n",iter);
  return;
 }
 else
 {
  if(changed==1)
  {
   char ch;
   iter++;
/*   printf("iteration complete,want to change parameter��Y/N��������");
   while(!isspace(ch=getchar()));
   if(ch=='y'||ch=='Y')
    goto start;
   else */goto step2;
  }
  else
  {
   iter++;
   goto step2;
  }
 } 
 
}






 

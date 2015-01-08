#include "../include/mystd.h"

#define MAXNUM  1000            //最大模式个数
#define MAXDIM  1000             //最大模式维数
#define K  0.5                       //分裂时使用的比值
#define MAXDOUBLE   1.0e20     //最大双精度值
#define N2 100

struct Pattern            //模式结构体
{
 int n;                //模式序号
 float s[MAXDIM];      //模式数据
 
};  
struct Cluster                   //类结构体           
{
    struct Pattern z;            //类中心
 int n;                       //类中包含的模式数目
    float avg_d;                 //模式到类心的平均距离
 struct Pattern y[MAXNUM];    //模式
    float sigma[MAXDIM];         //分量的标准差
 int max;                     //用于记录类内距离标准差矢量最大的分量下标
 float sigma_max;             //类内分量距离标准差最大值
};
int N=100;
struct Pattern x[N2];            //全部模式

int DIM=0;

//以下为各参数声明
int c=3;                          //预期的类数
int Nc=1;                         //初始聚类中心个数
int ON=1;                         //每一类中允许的最少模式数（小于此数不可单独成类）
float OS=1;                       //类内分量分布的标准差上限（大于此数就分裂）
float  OC=4;                      //两类中心间的最小距离下限（小于此数两类合并）
int L=1;                          //在每次迭代中可以合并的类的最大对数
int I=4;                          //最多迭代次数

struct Cluster w[N2];               //全部类
float  D[MAXNUM][MAXNUM];       //各类对中心间的距离
float dis;                      //总体平均距离
int  iter=1;                    //记录迭代次数
int  i,j;                      //循环变量

void InitPattern(int **adj,int row,int column)   //对样本模式进行初始化
{
	int i,j;
	for(i=0;i<row;i++){
		x[i].n=i;
		for(j=0;j<column;j++){
			x[i].s[j]=adj[i][j];
		}
	}
}
//以下为程序用到的调用函数
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
/* for(i=0;i<N;i++)                                         //打印本程序所使用样本
 {
  printf("\tX (%d): (",x[i].n);
  for(j=0;j<DIM-1;j++)
   printf("%3.2f,",x[i].s[j]);
  printf("%3.2f);\n",x[i].s[j]);
  
 }*/
 
    ISODATA();  	//ISODATA聚类程序
	}
return 0;
}

void Init()                                                  //对两结构体变量初始化（赋零值）
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
void InitCenter()                                            //按序号选定初始聚类中心
{ 
 int i,j,k,l;
 for(j=0;j<Nc;j++)
 {
  
  w[j].z=x[j];
  w[j].z.n=0;
 }
}

void Clustering()                                           //依最小距离原则将全部模式归类
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
float Distance(struct Pattern x1,struct Pattern x2)         //计算两个模式距离的函数
{
 int i;
 float temp=0.0;
 for(i=0;i<DIM;i++)
  temp+=(x1.s[i]-x2.s[i])*(x1.s[i]-x2.s[i]);
 return sqrt(temp);
}
struct Cluster Insert(struct Pattern a,struct Cluster b)          //将某模式插入对应类           
{
 b.n++;
 b.y[b.n-1]=a;
 return b;
 
 
}
int CheckAndUnion()   //依据ON判断合并，若类w[j]中模式数小于ON，取消类心，Nc=Nc-1,转至step2:
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
struct Pattern CalCenter(struct Cluster a)                       //计算类心
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
float Cal_D(int j)                    //计算各模式到类心的平均距离
{
 int i;
    float avg_d=0.0; 
 for(i=0;i<w[j].n;i++)
  avg_d+=Distance(w[j].y[i],w[j].z);
 avg_d/=w[j].n;
 w[j].avg_d=avg_d;
 return avg_d;
}
void CalParameter()                                      //计算分类后参数：各类中心、类内平均距离以及总体平均距离
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
void CalSigma()                                                 //计算各类类内距离的标准差矢量
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
int divide()                                                      //判断分裂
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
void CalCenterDis()                                               //计算各类对中心间的距离
{
 int i,j;
 for(i=0;i<Nc-1;i++)
  for(j=i+1;j<Nc;j++)
   D[i][j]=Distance(w[i].z,w[j].z);
}
void Union(int a,int b)                        //当两类未合并过时，进行合并
{
 int i;
 if((w[a].z.n<0)||(w[b].z.n<0))
  return ;
 
 for(i=0;i<DIM;i++)
  w[a].z.s[i]=(1/(w[a].n+w[b].n))*(w[a].z.s[i]*w[a].n+w[b].n*w[b].z.s[i]); 
 w[a].z.n=-1;
 w[b].z.n=-2;
 
 
}
int UnionByOC()                                              //依据OC判断合并
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
void PrintCluster()                                                       //打印当前模式分类情况
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
start:                                                                      //读入参数
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
 printf("max iteration I： ");
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
  w[i].z=CalCenter(w[i]);        //计算聚类中心
 }
 CalParameter();                   //每个聚类的样本离开其中心的平均距离以及所有样本离开其相应聚类中心的平均距离 
step5:                                  //依据iter,Nc判断停止、分裂还是合并
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
 if(iter>=I)                                     //判断循环还是退出
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
/*   printf("iteration complete,want to change parameter（Y/N）？？：");
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






 

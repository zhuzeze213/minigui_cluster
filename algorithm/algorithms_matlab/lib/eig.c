#include "../include/mystd.h"
////////////////////////////////////////////////////////////// 
//约化对称矩阵为三对角对称矩阵 
//利用Householder变换将n阶实对称矩阵约化为对称三对角矩阵 
//a-长度为n*n的数组，存放n阶实对称矩阵 
//n-矩阵的阶数 
//q-长度为n*n的数组，返回时存放Householder变换矩阵 
//b-长度为n的数组，返回时存放三对角阵的主对角线元素 
//c-长度为n的数组，返回时前n-1个元素存放次对角线元素 
void eastrq(double a[],int n,double q[],double b[],double c[]); 
////////////////////////////////////////////////////////////// 
//求实对称三对角对称矩阵的全部特征值及特征向量 
//利用变型QR方法计算实对称三对角矩阵全部特征值及特征向量 
//n-矩阵的阶数 
//b-长度为n的数组，返回时存放三对角阵的主对角线元素 
//c-长度为n的数组，返回时前n-1个元素存放次对角线元素 
//q-长度为n*n的数组，若存放单位矩阵，则返回实对称三对角矩阵的特征向量组 
// 若存放Householder变换矩阵，则返回实对称矩阵A的特征向量组 
//a-长度为n*n的数组，存放n阶实对称矩阵 
int ebstq(int n,double b[],double c[],double q[],double eps,int l); 
////////////////////////////////////////////////////////////// 
//约化实矩阵为赫申伯格(Hessen berg)矩阵 
//利用初等相似变换将n阶实矩阵约化为上H矩阵 
//a-长度为n*n的数组，存放n阶实矩阵,返回时存放上H矩阵 
//n-矩阵的阶数 
void echbg(double a[],int n); 
////////////////////////////////////////////////////////////// 
//求赫申伯格(Hessen berg)矩阵的全部特征值 
//返回值小于0表示超过迭代jt次仍未达到精度要求 
//返回值大于0表示正常返回 
//利用带原点位移的双重步QR方法求上H矩阵的全部特征值 
//a-长度为n*n的数组，存放上H矩阵 
//n-矩阵的阶数 
//u-长度为n的数组，返回n个特征值的实部 
//v-长度为n的数组，返回n个特征值的虚部 
//eps-控制精度要求 
//jt-整型变量，控制最大迭代次数 
int edqr(double a[],int n,double u[],double v[],double eps,int jt); 
////////////////////////////////////////////////////////////// 
//求实对称矩阵的特征值及特征向量的雅格比法 
//利用雅格比(Jacobi)方法求实对称矩阵的全部特征值及特征向量 
//返回值小于0表示超过迭代jt次仍未达到精度要求 
//返回值大于0表示正常返回 
//a-长度为n*n的数组，存放实对称矩阵，返回时对角线存放n个特征值 
//n-矩阵的阶数 
//u-长度为n*n的数组，返回特征向量(按列存储) 
//eps-控制精度要求 
//jt-整型变量，控制最大迭代次数 
int eejcb(double a[],int n,double v[],double eps,int jt); 
////////////////////////////////////////////////////////////// 

#include "stdio.h" 
#include "math.h" 
//约化对称矩阵为三对角对称矩阵 
//利用Householder变换将n阶实对称矩阵约化为对称三对角矩阵 
//a-长度为n*n的数组，存放n阶实对称矩阵 
//n-矩阵的阶数 
//q-长度为n*n的数组，返回时存放Householder变换矩阵 
//b-长度为n的数组，返回时存放三对角阵的主对角线元素 
//c-长度为n的数组，返回时前n-1个元素存放次对角线元素 
void eastrq(double a[],int n,double q[],double b[],double c[]) 
{ 
int i,j,k,u,v; 
double h,f,g,h2; 
for (i=0; i<=n-1; i++) 
{ 
for (j=0; j<=n-1; j++) 
{ 
u=i*n+j; q[u]=a[u]; 
} 
} 
for (i=n-1; i>=1; i--) 
{ 
h=0.0; 
if (i>1) 
{ 
for (k=0; k<=i-1; k++) 
{ 
u=i*n+k; 
h=h+q[u]*q[u]; 
} 
} 

if (h+1.0==1.0) 
{ 
c[i-1]=0.0; 
if (i==1) 
{ 
c[i-1]=q[i*n+i-1]; 
} 
b[i]=0.0; 
} 
else 
{ 
c[i-1]=sqrt(h); 
u=i*n+i-1; 
if (q[u]>0.0) 
{ 
c[i-1]=-c[i-1]; 
} 
h=h-q[u]*c[i-1]; 
q[u]=q[u]-c[i-1]; 
f=0.0; 
for (j=0; j<=i-1; j++) 
{ 
q[j*n+i]=q[i*n+j]/h; 
g=0.0; 
for (k=0; k<=j; k++) 
{ 
g=g+q[j*n+k]*q[i*n+k]; 
} 
if (j+1<=i-1) 
{ 
for (k=j+1; k<=i-1; k++) 
{ 
g=g+q[k*n+j]*q[i*n+k]; 
} 
} 
c[j-1]=g/h; 
f=f+g*q[j*n+i]; 
} 
h2=f/(h+h); 
for (j=0; j<=i-1; j++) 
{ 
f=q[i*n+j]; 
g=c[j-1]-h2*f; 
c[j-1]=g; 
for (k=0; k<=j; k++) 
{ 
u=j*n+k; 
q[u]=q[u]-f*c[k-1]-g*q[i*n+k]; 
} 
} 
b[i]=h; 
} 
} 
b[0]=0.0; 
for (i=0; i<=n-1; i++) 
{ 
if ((b[i]!=0.0)&&(i-1>=0)) 
{ 
for (j=0; j<=i-1; j++) 
{ 
g=0.0; 
for (k=0; k<=i-1; k++) 
{ 
g=g+q[i*n+k]*q[k*n+j]; 
} 
for (k=0; k<=i-1; k++) 
{ 
u=k*n+j; 
q[u]=q[u]-g*q[k*n+i]; 
} 
} 
} 
u=i*n+i; 
b[i]=q[u]; 
q[u]=1.0; 
if (i-1>=0) 
{ 
for (j=0; j<=i-1; j++) 
{ 
q[i*n+j]=0.0; 
q[j*n+i]=0.0; 
} 
} 
} 
return; 
}
//求实对称三对角对称矩阵的全部特征值及特征向量 
//利用变型QR方法计算实对称三对角矩阵全部特征值及特征向量 
//n-矩阵的阶数 
//b-长度为n的数组，返回时存放三对角阵的主对角线元素 
//c-长度为n的数组，返回时前n-1个元素存放次对角线元素 
//q-长度为n*n的数组，若存放单位矩阵，则返回实对称三对角矩阵的特征向量组 
// 若存放Householder变换矩阵，则返回实对称矩阵A的特征向量组 
//a-长度为n*n的数组，存放n阶实对称矩阵 
int ebstq(int n,double b[],double c[],double q[],double eps,int l) 
{ 
int i,j,k,m,it,u,v; 
double d,f,h,g,p,r,e,s; 
c[n-1]=0.0; 
d=0.0; 
f=0.0; 
for (j=0; j<=n-1; j++) 
{ 
it=0; 
h=eps*(fabs(b[j])+fabs(c[j])); 
if (h>d) 
{ 
d=h; 
} 
m=j; 
while ((m<=n-1)&&(fabs(c[m])>d)) 
{ 
m=m+1; 
} 
if (m!=j) 
{ 
do 
{ 
if (it==l) 
{ 
printf("fail\n"); 
return(-1); 
} 
it=it+1; 
g=b[j]; 
p=(b[j+1]-g)/(2.0*c[j]); 
r=sqrt(p*p+1.0); 
if (p>=0.0) 
{ 
b[j]=c[j]/(p+r); 
} 
else 
{ 
b[j]=c[j]/(p-r); 
} 
h=g-b[j]; 
for (i=j+1; i<=n-1; i++) 
{ 
b[i]=b[i]-h; 
} 
f=f+h; 
p=b[m]; 
e=1.0; 
s=0.0; 
for (i=m-1; i>=j; i--) 
{ 
g=e*c[i]; 
h=e*p; 
if (fabs(p)>=fabs(c[i])) 
{ 
e=c[i]/p; 
r=sqrt(e*e+1.0); 
c[i+1]=s*p*r; 
s=e/r; 
e=1.0/r; 
} 
else 
{ 
e=p/c[i]; 
r=sqrt(e*e+1.0); 
c[i+1]=s*c[i]*r; 
s=1.0/r; 
e=e/r; 
} 
p=e*b[i]-s*g; 
b[i+1]=h+s*(e*g+s*b[i]); 
for (k=0; k<=n-1; k++) 
{ 
u=k*n+i+1; 
v=u-1; 
h=q[u]; 
q[u]=s*q[v]+e*h; 
q[v]=e*q[v]-s*h; 
} 
} 
c[j]=s*p; 
b[j]=e*p; 
} 
while (fabs(c[j])>d); 
} 
b[j]=b[j]+f; 
} 
for (i=0; i<=n-1; i++) 
{ 
k=i; p=b[i]; 
if (i+1<=n-1) 
{ 
j=i+1; 
while ((j<=n-1)&&(b[j]<=p)) 
{ 
k=j; 
p=b[j]; 
j=j+1; 
} 
} 
if (k!=i) 
{ 
b[k]=b[i]; 
b[i]=p; 
for (j=0; j<=n-1; j++) 
{ 
u=j*n+i; 
v=j*n+k; 
p=q[u]; 
q[u]=q[v]; 
q[v]=p; 
} 
} 
} 
return(1); 
} 

//约化实矩阵为赫申伯格(Hessen berg)矩阵 
//利用初等相似变换将n阶实矩阵约化为上H矩阵 
//a-长度为n*n的数组，存放n阶实矩阵,返回时存放上H矩阵 
//n-矩阵的阶数 
void echbg(double a[],int n) 
{ int i,j,k,u,v; 
double d,t; 
for (k=1; k<=n-2; k++) 
{ 
d=0.0; 
for (j=k; j<=n-1; j++) 
{ 
u=j*n+k-1; 
t=a[u]; 
if (fabs(t)>fabs(d)) 
{ 
d=t; 
i=j; 
} 
} 
if (fabs(d)+1.0!=1.0) 
{ 
if (i!=k) 
{ 
for (j=k-1; j<=n-1; j++) 
{ 
u=i*n+j; 
v=k*n+j; 
t=a[u]; 
a[u]=a[v]; 
a[v]=t; 
} 
for (j=0; j<=n-1; j++) 
{ 
u=j*n+i; 
v=j*n+k; 
t=a[u]; 
a[u]=a[v]; 
a[v]=t; 
} 
} 
for (i=k+1; i<=n-1; i++) 
{ 
u=i*n+k-1; 
t=a[u]/d; 
a[u]=0.0; 
for (j=k; j<=n-1; j++) 
{ 
v=i*n+j; 
a[v]=a[v]-t*a[k*n+j]; 
} 
for (j=0; j<=n-1; j++) 
{ 
v=j*n+k; 
a[v]=a[v]+t*a[j*n+i]; 
} 
} 
} 
} 
return; 
} 

//求赫申伯格(Hessen berg)矩阵的全部特征值 
//利用带原点位移的双重步QR方法求上H矩阵的全部特征值 
//返回值小于0表示超过迭代jt次仍未达到精度要求 
//返回值大于0表示正常返回 
//a-长度为n*n的数组，存放上H矩阵 
//n-矩阵的阶数 
//u-长度为n的数组，返回n个特征值的实部 
//v-长度为n的数组，返回n个特征值的虚部 
//eps-控制精度要求 
//jt-整型变量，控制最大迭代次数 
int edqr(double a[],int n,double u[],double v[],double eps,int jt) 
{ 
int m,it,i,j,k,l,ii,jj,kk,ll; 
double b,c,w,g,xy,p,q,r,x,s,e,f,z,y; 
it=0; 
m=n; 
while (m!=0) 
{ 
l=m-1; 
while ((l>0)&&(fabs(a[l*n+l-1])>eps*(fabs(a[(l-1)*n+l-1])+fabs(a[l*n+l])))) 
{ 
l=l-1; 
} 
ii=(m-1)*n+m-1; 
jj=(m-1)*n+m-2; 
kk=(m-2)*n+m-1; 
ll=(m-2)*n+m-2; 
if (l==m-1) 
{ 
u[m-1]=a[(m-1)*n+m-1]; 
v[m-1]=0.0; 
m=m-1; it=0; 
} 
else if (l==m-2) 
{ 
b=-(a[ii]+a[ll]); 
c=a[ii]*a[ll]-a[jj]*a[kk]; 
w=b*b-4.0*c; 
y=sqrt(fabs(w)); 
if (w>0.0) 
{ 
xy=1.0; 
if (b<0.0) 
{ 
xy=-1.0; 
} 
u[m-1]=(-b-xy*y)/2.0; 
u[m-2]=c/u[m-1]; 
v[m-1]=0.0; v[m-2]=0.0; 
} 
else 
{ 
u[m-1]=-b/2.0; 
u[m-2]=u[m-1]; 
v[m-1]=y/2.0; 
v[m-2]=-v[m-1]; 
} 
m=m-2; 
it=0; 
} 
else 
{ 
if (it>=jt) 
{ 
printf("fail\n"); 
return(-1); 
} 
it=it+1; 
for (j=l+2; j<=m-1; j++) 
{ 
a[j*n+j-2]=0.0; 
} 
for (j=l+3; j<=m-1; j++) 
{ 
a[j*n+j-3]=0.0; 
} 
for (k=l; k<=m-2; k++) 
{ 
if (k!=l) 
{ 
p=a[k*n+k-1]; 
q=a[(k+1)*n+k-1]; 
r=0.0; 
if (k!=m-2) 
{ 
r=a[(k+2)*n+k-1]; 
} 
} 
else 
{ 
x=a[ii]+a[ll]; 
y=a[ll]*a[ii]-a[kk]*a[jj]; 
ii=l*n+l; 
jj=l*n+l+1; 
kk=(l+1)*n+l; 
ll=(l+1)*n+l+1; 
p=a[ii]*(a[ii]-x)+a[jj]*a[kk]+y; 
q=a[kk]*(a[ii]+a[ll]-x); 
r=a[kk]*a[(l+2)*n+l+1]; 
} 
if ((fabs(p)+fabs(q)+fabs(r))!=0.0) 
{ 
xy=1.0; 
if (p<0.0) 
{ 
xy=-1.0; 
} 
s=xy*sqrt(p*p+q*q+r*r); 
if (k!=l) 
{ 
a[k*n+k-1]=-s; 
} 
e=-q/s; 
f=-r/s; 
x=-p/s; 
y=-x-f*r/(p+s); 
g=e*r/(p+s); 
z=-x-e*q/(p+s); 
for (j=k; j<=m-1; j++) 
{ 
ii=k*n+j; 
jj=(k+1)*n+j; 
p=x*a[ii]+e*a[jj]; 
q=e*a[ii]+y*a[jj]; 
r=f*a[ii]+g*a[jj]; 
if (k!=m-2) 
{ 
kk=(k+2)*n+j; 
p=p+f*a[kk]; 
q=q+g*a[kk]; 
r=r+z*a[kk]; 
a[kk]=r; 
} 
a[jj]=q; 
a[ii]=p; 
} 
j=k+3; 
if (j>=m-1) 
{ 
j=m-1; 
} 
for (i=l; i<=j; i++) 
{ 
ii=i*n+k; 
jj=i*n+k+1; 
p=x*a[ii]+e*a[jj]; 
q=e*a[ii]+y*a[jj]; 
r=f*a[ii]+g*a[jj]; 
if (k!=m-2) 
{ 
kk=i*n+k+2; 
p=p+f*a[kk]; 
q=q+g*a[kk]; 
r=r+z*a[kk]; 
a[kk]=r; 
} 
a[jj]=q; 
a[ii]=p; 
} 
} 
} 
} 
} 
return(1); 
} 

//求实对称矩阵的特征值及特征向量的雅格比法 
//利用雅格比(Jacobi)方法求实对称矩阵的全部特征值及特征向量 
//返回值小于0表示超过迭代jt次仍未达到精度要求 
//返回值大于0表示正常返回 
//a-长度为n*n的数组，存放实对称矩阵，返回时对角线存放n个特征值 
//n-矩阵的阶数 
//u-长度为n*n的数组，返回特征向量(按列存储) 
//eps-控制精度要求 
//jt-整型变量，控制最大迭代次数 
int eejcb(double a[],int n,double v[],double eps,int jt) 
{ 
int i,j,p,q,u,w,t,s,l; 
double fm,cn,sn,omega,x,y,d; 
l=1; 
for (i=0; i<=n-1; i++) 
{ 
v[i*n+i]=1.0; 
for (j=0; j<=n-1; j++) 
{ 
if (i!=j) 
{ 
v[i*n+j]=0.0; 
} 
} 
} 
while (1==1) 
{ 
fm=0.0; 
for (i=0; i<=n-1; i++) 
{ 
for (j=0; j<=n-1; j++) 
{ 
d=fabs(a[i*n+j]); 
if ((i!=j)&&(d>fm)) 
{ 
fm=d; 
p=i; 
q=j; 
} 
} 
} 
if (fm<eps) 
{ 
return(1); 
} 
if (l>jt) 
{ 
return(-1); 
} 
l=l+1; 
u=p*n+q; 
w=p*n+p; 
t=q*n+p; 
s=q*n+q; 
x=-a[u]; 
y=(a[s]-a[w])/2.0; 
omega=x/sqrt(x*x+y*y); 
if (y<0.0) 
{ 
omega=-omega; 
} 
sn=1.0+sqrt(1.0-omega*omega); 
sn=omega/sqrt(2.0*sn); 
cn=sqrt(1.0-sn*sn); 
fm=a[w]; 
a[w]=fm*cn*cn+a[s]*sn*sn+a[u]*omega; 
a[s]=fm*sn*sn+a[s]*cn*cn-a[u]*omega; 
a[u]=0.0; 
a[t]=0.0; 
for (j=0; j<=n-1; j++) 
{ 
if ((j!=p)&&(j!=q)) 
{ 
u=p*n+j; 
w=q*n+j; 
fm=a[u]; 
a[u]=fm*cn+a[w]*sn; 
a[w]=-fm*sn+a[w]*cn; 
} 
} 
for (i=0; i<=n-1; i++) 
{ 
if ((i!=p)&&(i!=q)) 
{ 
u=i*n+p; 
w=i*n+q; 
fm=a[u]; 
a[u]=fm*cn+a[w]*sn; 
a[w]=-fm*sn+a[w]*cn; 
} 
} 
for (i=0; i<=n-1; i++) 
{ 
u=i*n+p; 
w=i*n+q; 
fm=v[u]; 
v[u]=fm*cn+v[w]*sn; 
v[w]=-fm*sn+v[w]*cn; 
} 
} 
return(1); 
}

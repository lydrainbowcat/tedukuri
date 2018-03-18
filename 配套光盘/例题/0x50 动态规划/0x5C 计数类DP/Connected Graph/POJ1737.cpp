#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
using namespace std;
int n;
struct H
{int a[400],len;}f[60],power[60];
inline H operator / (const H &x,const int y)
{
	H z;
	memset(z.a,0,sizeof z.a);
	z.len=0;
	int left=0;
	for(int i=x.len;i>=1;i--)
	{
		left=left*10+x.a[i];
		z.a[i]=left/y;
		left%=y;
		if(!z.len&&z.a[i]) z.len=i;
	}
	return z;
}
inline H operator + (const H &x,const H &y)
{
	H z;
	memset(z.a,0,sizeof z.a);
	for(int i=1;i<=max(x.len,y.len);i++)
	{
		z.a[i]+=x.a[i]+y.a[i];
		z.a[i+1]=z.a[i]/10;
		z.a[i]%=10;
	}
	z.len=max(x.len,y.len);
	if(z.a[z.len+1]) z.len++;
	return z;
}
inline H operator * (const H &x,const H &y)
{    
	H z;                     
	memset(z.a,0,sizeof z.a);
	for(int i=1;i<=x.len;i++)
		for(int j=1;j<=y.len;j++)
		{
			z.a[i+j-1]+=x.a[i]*y.a[j];
			z.a[i+j]+=z.a[i+j-1]/10;
			z.a[i+j-1]%=10;	
		}
	z.len=x.len+y.len-1;
	if(z.a[z.len+1]) z.len++;
	return z;
}
inline H C(int x,int y)
{
	H tot,temp;
	tot.len=1;
	tot.a[1]=1;
	for(int i=y,j=1;j<=x;i--,j++)
	{
		int t=i;
		temp.len=0;
		while(t)
		{
			temp.a[++temp.len]=t%10;
			t/=10;
		}
		tot=tot*temp/j;
	}
	return tot;
}
inline void print(const H &x)
{
	for(int i=x.len;i>=1;i--)
		printf("%d",x.a[i]);
	printf("\n");
}
int main()
{
	for(int i=1;i<=50;i++)
	{
		long long temp=((long long)(1)<<i)-1;
		while(temp)
		{
			power[i].a[++power[i].len]=temp%10;
			temp/=10;
		}
	}
	f[1].len=1;f[1].a[1]=1;
	f[2].len=1;f[2].a[1]=1;
	for(int i=3;i<=50;i++)
		for(int j=1;j<=i-1;j++)
			f[i]=f[i]+C(j-1,i-2)*f[j]*f[i-j]*power[j];
	while(scanf("%d",&n),n) print(f[n]);
	return 0;
}
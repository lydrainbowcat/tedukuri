#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct num{int s,a[1100];}ans,now,temp;
struct rec{int l,r;}a[1010];
int n,i;

bool operator <(rec a,rec b)
{
	return a.l*a.r<b.l*b.r;
}
bool operator <(num a,num b)
{
	if(a.s<b.s) return 1;
	if(a.s>b.s) return 0;
	for(int i=a.s;i;i--)
	{
		if(a.a[i]<b.a[i]) return 1;
		if(a.a[i]>b.a[i]) return 0;
	}
}

num operator *(num a,int b)
{
	num c; int i,jin=0;
	memset(&c,0,sizeof(c));
	for(i=1;i<=a.s;i++)
	{
		jin+=a.a[i]*b;
		c.a[i]=jin%10000;
		jin/=10000;
	}
	c.s=a.s;
	while(jin) c.a[++c.s]=jin%10000,jin/=10000;
	return c;
}

num operator /(num a,int b)
{
	num c; int i,rest=0;
	memset(&c,0,sizeof(c));
	for(i=a.s;i;i--)
	{
		rest=rest*10000+a.a[i];
		c.a[i]=rest/b;
		rest%=b;
	}
	c.s=a.s;
	while(c.s>1&&!c.a[c.s]) c.s--;
	return c;
}

int main()
{
	cin>>n>>a[0].l>>a[0].r;
	for(i=1;i<=n;i++) scanf("%d%d",&a[i].l,&a[i].r);
	sort(a+1,a+n+1);
	now.s=now.a[1]=ans.s=1;
	for(i=1;i<=n;i++)
	{
		now=now*a[i-1].l;
		temp=now/a[i].r;
		if(ans<temp) ans=temp;
	}
	printf("%d",ans.a[ans.s]);
	for(i=ans.s-1;i;i--) printf("%04d",ans.a[i]);
	puts("");
	return 0;
}

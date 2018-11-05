// Author: SJZEZ wccy
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

#define N 60000

using namespace std;

struct C
{
	int sm,s,w;
}c[N];
int ans,sum[N],n;

inline bool cmp(const C &a,const C &b)
{
	return a.sm<b.sm;
}

void go()
{
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&c[i].w,&c[i].s);
		c[i].sm=c[i].w+c[i].s;
	}
	sort(c+1,c+1+n,cmp);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+c[i].w;
	ans=-2147483646;
	for(int i=1;i<=n;i++) ans=max(ans,sum[i-1]-c[i].s);
	printf("%d\n",ans);
}

int main()
{
	while(scanf("%d",&n)!=EOF) go();
	return 0;
}
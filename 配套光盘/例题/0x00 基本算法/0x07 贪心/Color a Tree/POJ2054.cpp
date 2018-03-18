/*
  Author: wccy
  本程序仅供参考 
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int n,r,ans;
struct node
{int t,p,c;double w;}num[1010];
inline int find()
{
	double maxr=0;
	int res;
	for(int i=1;i<=n;i++)
		if(i!=r&&num[i].w>maxr)
		{
			maxr=num[i].w;
			res=i;
		}
	return res;
}
int main()
{
	while(scanf("%d%d",&n,&r),n||r)
	{
		ans=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&num[i].c);
			num[i].w=num[i].c;
			num[i].t=1;
			ans+=num[i].c;
		}
		for(int i=1,a,b;i<=n-1;i++)
		{
			scanf("%d%d",&a,&b);
			num[b].p=a;
		}
		for(int i=1;i<n;i++)
		{
			int pos=find();
			num[pos].w=0;
			int f=num[pos].p;
			ans+=num[pos].c*num[f].t;
			for(int j=1;j<=n;j++)
				if(num[j].p==pos)
					num[j].p=f;
			num[f].c+=num[pos].c;
			num[f].t+=num[pos].t;
			num[f].w=double(num[f].c)/num[f].t;
		}
		printf("%d\n",ans);
	}
	return 0;
}

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<stdlib.h>
#define fr(i,n) for(int i=0;i<n;i++)
using namespace std;
int n,m,x,y,u,z;
int d[220][220];
int v[220],l[220];
int dfs(int x)
{
	fr(i,n)
		if(d[x][i]&&v[i]!=u)
		{
			v[i]=u;
			if(l[i]==-1||dfs(l[i]))
				return l[i]=x,1;
		}
	return 0;
}
int main()
{
	scanf("%d %d",&n,&m);
	fr(i,m)
	{
		scanf("%d %d",&x,&y);
		d[x-1][y-1]=1;
	}
	fr(k,n)
		fr(i,n)
			fr(j,n)
				d[i][j]|=(d[i][k]&d[k][j]);
	memset(l,-1,sizeof l);
	memset(v,-1,sizeof v);
	z=n;
	for(u=0;u<n;u++)
		z-=dfs(u);
	printf("%d",z);
	return 0;
}

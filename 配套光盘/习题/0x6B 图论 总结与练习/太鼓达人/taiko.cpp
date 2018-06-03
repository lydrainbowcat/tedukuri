#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;

int n,lim;
int vis[3055000];
int a[3050500];

void dfs(int x,int y)
{
	if(x>lim/2) return;
	if(y>lim/2) return;
	if(x==lim/2&&y==lim/2)
	{
		printf("%d ",lim);
		for(int i=1;i<=lim;i++)
			printf("%d",a[i]);
		printf("\n");
		exit(0);
	}
	a[x+y+1]=0;
	int sum=0;
	for(int i=x+y-n+2;i<=x+y+1;i++)
		sum=sum*2+a[i];
	if(!vis[sum])
	{
		vis[sum]=1;
		dfs(x+1,y);
	}
	a[x+y+1]=1;
	sum=0;
	for(int i=x+y-n+2;i<=x+y+1;i++)
		sum=sum*2+a[i];
	if(!vis[sum])
	{
		vis[sum]=1;
		dfs(x,y+1);
	}	
}

int main()
{	
	scanf("%d",&n),lim=1<<n;
	vis[0]=1;
	dfs(n,0);
	return 0;
}

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int head[1010],ver[1010],next[1010],dfn[1010],low[1010],v[1010],vis[1010];
int n,m,tot,i,p,t,x,y,num,cnt,T;
unsigned long long ans;

void add(int x,int y)
{
	ver[++tot]=y,next[tot]=head[x],head[x]=tot;
}

void tarjan(int x)
{
	v[x]=1,dfn[x]=low[x]=++num;
	for(int i=head[x];i;i=next[i])
		if(!v[ver[i]])
		{
			tarjan(ver[i]);
			low[x]=min(low[x],low[ver[i]]);
			if(dfn[x]<=low[ver[i]]) v[x]++;
		}
		else low[x]=min(low[x],dfn[ver[i]]);
	if((x==1&&v[x]>2)||(x>1&&v[x]>1)) v[x]=2; else v[x]=1;
}

void dfs(int x)
{
	v[x]=3,t++;
	for(int i=head[x];i;i=next[i])
		if(v[ver[i]]==1) dfs(ver[i]);
		else if(v[ver[i]]==2&&vis[ver[i]]!=num) p++,vis[ver[i]]=num;
}

int main()
{
	while(cin>>m&&m)
	{
		memset(v,-1,sizeof(v));
		memset(head,0,sizeof(head));
		memset(vis,0,sizeof(vis));
		tot=cnt=num=n=0,ans=1;
		for(i=1;i<=m;i++)
		{
			scanf("%d%d",&x,&y);
			n=max(n,max(x,y));
			v[x]=v[y]=0;
			add(x,y),add(y,x);
		}
		for(i=1;i<=n;i++)
			if(!v[i]) tarjan(i);
		for(num=0,i=1;i<=n;i++)
			if(v[i]==1)
			{
				p=t=0; num++;
				dfs(i);
				if(p==1) cnt++,ans*=t;
			}
		if(!cnt) cnt=2,ans=n*(n-1)/2;
		printf("Case %d: %d %lld\n",++T,cnt,ans);
	}
	return 0;
}
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<string>
#include<map>
using namespace std;
int n,m,tot,w[210];
char str[2100];
bool ok[210];
int head[210],to[210],next[210],graphmr;
int f[210][210],son[210];
map<string,int> vis;
inline void add(int x,int y)
{
	int p=graphmr++;
	to[p]=y;next[p]=head[x];head[x]=p;
}
inline void dfs(int x)
{
	f[x][0]=0;
	son[x]=1;
	for(int i=head[x];~i;i=next[i])
	{
		dfs(to[i]);
		son[x]+=son[to[i]];
		for(int j=m;j>=0;j--)
			for(int k=0;k<=j;k++)
				f[x][j]=min(f[x][j],f[x][j-k]+f[to[i]][k]);
	}
	for(int i=1;i<=son[x];i++) f[x][i]=min(f[x][i],w[x]);
}
int main()
{
	scanf("%d",&n);
	while(1)
	{
		scanf("%d",&m);
		vis.clear();
		tot=0;
		memset(head,-1,sizeof head);
		memset(ok,0,sizeof ok);
		for(int i=0;i<=n;i++)
			son[i]=1;
		graphmr=0;
		for(int i=1;i<=n;i++)
		{
			int t,x;
			scanf("%s%d",str,&t);
			if(!vis[str]) vis[str]=++tot;
			x=vis[str];
			w[x]=t;
			while(getchar()!='\n')
			{
				scanf("%s",str);
				int y;
				if(!vis[str]) vis[str]=++tot;
				y=vis[str];
				add(x,y);
				ok[y]=1;
				son[x]++;
			}
		}
		memset(f,0x3f,sizeof f);
		w[0]=0x3f3f3f3f;
		for(int i=1;i<=n;i++)
			if(!ok[i])
			{
				add(0,i);
				son[0]++;
			}
		dfs(0);
		printf("%d\n",f[0][m]);
		scanf("%s",str);
		if(str[0]=='#') break;
		n=0;
		for(int i=0;str[i];i++)
			n=n*10+str[i]-'0';
	}
	return 0;
}
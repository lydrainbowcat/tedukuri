#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

const int T = 2000;

int hd[T],nxt[T],to[T],cnt,n,rt;
int f0[T],f1[T];
bool vis[T],vv[T];

inline void add(int x,int y)
{
	nxt[cnt]=hd[x],to[cnt]=y,hd[x]=cnt++;
}

void dfs(int u)
{
	f1[u]=1,f0[u]=0;
	for(int i=hd[u];~i;i=nxt[i])
	{
		dfs(to[i]);
		f1[u]+=min(f0[to[i]],f1[to[i]]);
		f0[u]+=f1[to[i]];
	}
}

void deal()
{
	memset(hd,-1,sizeof hd),cnt=0,memset(vis,0,sizeof(vis));
	memset(f0,0x3f,sizeof f0),memset(f1,0x3f,sizeof f1);
	char str[100]; 
	for(int i=0;i<n;i++)
	{
		int x,y,z;
		scanf("%s",str),sscanf(str,"%d:(%d)",&x,&y);
		for(int j=1;j<=y;j++)
		{
			scanf("%d",&z),add(x,z);
			vis[z]=1;
		}
	}
	
	for(int i=0;i<n;i++)
	{
		if(!vis[i]) { rt=i; break;}
	}
	dfs(rt);
	printf("%d\n",min(f0[rt],f1[rt]));
}

int main()
{
	while(~scanf("%d",&n))
	 deal();
	 return 0;
}
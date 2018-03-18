#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int u=200,w=100010;
int ver[w],next[w],head[u],dfn[u],low[u],c[u],s[u],v[u];
int vx[w],vy[w],ans[u],du[u],opp[u];
int n,m,tot,num,t,p,i,j,x,y,e;
char cx,cy;

void add(int x,int y)
{
	if(!num) vx[++e]=x,vy[e]=y; else du[y]++;
	ver[++tot]=y,next[tot]=head[x],head[x]=tot;
}

void tarjan(int x)
{
	int i;
	dfn[x]=low[x]=++num;
	s[++p]=x,v[x]=1;
	for(i=head[x];i;i=next[i])
		if(!dfn[ver[i]])
		{
			tarjan(ver[i]);
			low[x]=min(low[x],low[ver[i]]);
		}
		else if(v[ver[i]])
			low[x]=min(low[x],low[ver[i]]);
	if(dfn[x]==low[x])
	{
		t++;
		do{i=s[p--],v[i]=0; c[i]=t;}while(i!=x);
	}
}

void topsort()
{
	queue<int> q;
	memset(head,0,sizeof(head));
	memset(ans,0,sizeof(ans));
	memset(du,0,sizeof(du));
	tot=0;
	for(i=1;i<=e;i++)
		if(c[vx[i]]!=c[vy[i]]) add(c[vy[i]],c[vx[i]]);
	for(i=1;i<=t;i++)
		if(!du[i]) q.push(i);
	while(q.size())
	{
		x=q.front(); q.pop();
		if(!ans[x]) ans[x]=1,ans[opp[x]]=2;
		for(i=head[x];i;i=next[i])
			if(--du[ver[i]]==0) q.push(ver[i]);
	}
	if(ans[c[1]]==1) printf("1w"); else printf("1h");
	for(i=2;i<n;i++)
		if(ans[c[i]]==1) printf(" %dw",i);
		else printf(" %dh",i);
	cout<<endl;
}

int main()
{
	while(cin>>n>>m&&n&&m)
	{
		memset(head,0,sizeof(head));
		memset(dfn,0,sizeof(dfn));
		tot=num=p=t=e=0;
		add(2*n,0),add(n,n*3);
		for(i=1;i<n;i++) add(i,n*3+i),add(n*2+i,n+i),add(n+i,n*2+i),add(n*3+i,i);
		for(i=1;i<=m;i++)
		{
			scanf("%d%c%d%c",&x,&cx,&y,&cy);
			cx=(cx=='w')?0:n; cy=(cy=='w')?0:n;
			add(cx+2*n+x,cy+y),add(cy+2*n+y,cx+x);
		}
		for(i=0;i<4*n;i++)
			if(!dfn[i]) tarjan(i);
		for(i=0;i<2*n;i++)
		{
			if(c[i]==c[2*n+i]) break;
			opp[c[i]]=c[2*n+i],opp[c[2*n+i]]=c[i];
		}
		if(i<2*n) {puts("bad luck"); continue;}
		topsort();
	}
	return 0;
}
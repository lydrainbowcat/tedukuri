/*Author: lydrainbowcat*/ 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue> 
using namespace std;
const int u=10010,w=80010;
struct rec{
	int x,y;
	rec(int p,int q):x(p),y(q){}
};
int ver[w],edge[w],next[w],head[u],fa[u],a[u],len[u],d[u],f[u][16],dis[u],dist[u],v[u],g[u],del[w];
vector<int> c[u];
int n,m,tot,t,cnt,i,j,x,y,z,num,now;

void add(int x,int y,int z)
{
	ver[++tot]=y,edge[tot]=z,next[tot]=head[x],head[x]=tot;
}

void circle(int x,int e)
{
	int i,j,y=x; x=ver[e]; 
	len[++cnt]=edge[e],c[y].push_back(cnt),g[y]=cnt; 
	del[e]=del[e^1]=1,add(x,y,0),add(y,x,0);
	for(i=fa[y];(y=ver[i^1])!=x;i=fa[y])
	{ 
		c[y].push_back(cnt),len[cnt]+=edge[i],g[y]=cnt; 
		del[i]=del[i^1]=1,add(x,y,0),add(y,x,0); 
	}
	len[cnt]+=edge[i],c[x].push_back(cnt);
}

void dfs(int x)
{
	v[x]=++num;
	for(int i=head[x];i;i=next[i])
		if(i<=now)
			if(!v[ver[i]])
			{
				fa[ver[i]]=i;
				dis[ver[i]]=dis[x]+edge[i];
				dfs(ver[i]); 
			}
			else if(fa[x]!=(i^1)&&v[ver[i]]<v[x]) circle(x,i);
}

void bfs()
{
	queue<int> q; 
	memset(v,0,sizeof(v)); 
	q.push(1); v[1]=1; d[1]=1; 
	while(q.size())
	{
		x=q.front(); q.pop();
		for(i=head[x];i;i=next[i])
			if(!del[i]&&!v[y=ver[i]])
			{
				d[y]=d[x]+1; f[y][0]=x;
				for(j=1;j<15;j++) f[y][j]=f[f[y][j-1]][j-1];
				q.push(y); v[y]=1;
			}
	}
}

void spfa()
{
	memset(dist,0x3f,sizeof(dist));
	memset(v,0,sizeof(v)); 
	queue<int> q;
	q.push(1); dist[1]=0; v[1]=1;
	while(q.size())
	{
		x=q.front(); q.pop(); v[x]=0; 
		for(i=head[x];i;i=next[i])
			if(dist[ver[i]]>dist[x]+edge[i])
			{
				dist[ver[i]]=dist[x]+edge[i];
				if(!v[ver[i]]) q.push(ver[i]),v[ver[i]]=1; 
			} 
	}
} 

int lca(int x,int y)
{
	if(d[x]<d[y]) swap(x,y);
	int i,p=x,q=y;
	for(i=14;i>=0;i--)
		if(d[f[x][i]]>=d[y]) x=f[x][i];
	if(x==y) return dist[p]-dist[q];
	for(i=14;i>=0;i--)
		if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	if(g[x]&&g[x]==g[y])
	{
		i=abs(dis[y]-dis[x]); 
		return dist[p]-dist[x]+dist[q]-dist[y]+min(i,len[g[x]]-i);
	}
	else return dist[p]+dist[q]-2*dist[f[x][0]]; 
}

int main()
{
	freopen("communicate.in","r",stdin);
	freopen("communicate.out","w",stdout); 
	cin>>n>>m>>t;
	for(tot=i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z),add(y,x,z);
	}
	spfa(); 
	now=tot;
	dfs(1);
	bfs();
	for(i=1;i<=t;i++)
	{
		scanf("%d%d",&x,&y);
		printf("%d\n",lca(x,y));
	}
	fclose(stdin);
	fclose(stdout); 
	return 0;
}
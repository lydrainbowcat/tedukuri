#include<iostream>
#include<cstdio>
#include<queue>
#include<cmath>
using namespace std;
const int u=500010;
int f[u][25],d[u],v[u],ver[2*u],next[2*u],head[u];
int n,m,tot,t,i,j,x,y,z,fx,fy,fz,dx,dy,dz;
queue<int> q;

void add(int x,int y)
{
	ver[++tot]=y; next[tot]=head[x]; head[x]=tot;
}

void bfs()
{
	q.push(1); v[1]=1; d[1]=1;
	while(q.size())
	{
		x=q.front(); q.pop();
		for(i=head[x];i;i=next[i])
			if(!v[y=ver[i]])
			{
				q.push(y); v[y]=1;
				d[y]=d[x]+1;
				f[y][0]=x;
				for(j=1;j<=t;j++) f[y][j]=f[f[y][j-1]][j-1];
			}
	}
}

int lca(int x,int y)
{
	if(d[x]>d[y]) swap(x,y);
	for(int i=t;i>=0;i--)
		if(d[f[y][i]]>=d[x]) y=f[y][i];
	if(x==y) return x;
	for(int i=t;i>=0;i--)
		if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}

int main()
{
	cin>>n>>m;
	t=(int)(log(n)/log(2))+1;
	for(i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	bfs();
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		fx=lca(x,y),dx=d[x]+d[y]-d[fx]+d[z]-2*d[lca(z,fx)];
		fy=lca(y,z),dy=d[y]+d[z]-d[fy]+d[x]-2*d[lca(x,fy)];
		fz=lca(x,z),dz=d[x]+d[z]-d[fz]+d[y]-2*d[lca(y,fz)];
		if(dx>dy) dx=dy,fx=fy;
		if(dx>dz) dx=dz,fx=fz;
		printf("%d %d\n",fx,dx);
	}
	return 0;
}
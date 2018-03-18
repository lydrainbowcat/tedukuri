#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<queue>
#include<cmath>
using namespace std;
const int u=100010;
int f[u][20],a[u],d[u],v[u],ver[2*u],next[2*u],edge[2*u],head[u];
__int64 dis[u][20],ans;
int n,m,tot,t,i,j,x,y,z;
set<int> s;
typedef set<int>::iterator It;
It it;
queue<int> q;
char str[2];

void add(int x,int y,int z)
{
	ver[++tot]=y,edge[tot]=z,next[tot]=head[x],head[x]=tot;
}

void bfs()
{
	q.push(1),v[1]=1,d[1]=1;
	while(q.size())
	{
		x=q.front(); q.pop();
		for(i=head[x];i;i=next[i])
			if(!v[y=ver[i]])
			{
				q.push(y); v[y]=1;
				d[y]=d[x]+1;
				f[y][0]=x,dis[y][0]=edge[i];
				for(j=1;j<=t;j++)
				{
					f[y][j]=f[f[y][j-1]][j-1];
					dis[y][j]=dis[f[y][j-1]][j-1]+dis[y][j-1];
				}
			}
	}
}

__int64 lca(int x,int y)
{
	__int64 ans=0;
	if(d[x]>d[y]) swap(x,y);
	for(int i=t;i>=0;i--)
		if(d[f[y][i]]>=d[x]) ans+=dis[y][i],y=f[y][i];
	if(x==y) return ans;
	for(int i=t;i>=0;i--)
		if(f[x][i]!=f[y][i]) ans+=dis[x][i]+dis[y][i],x=f[x][i],y=f[y][i];
	return ans+dis[x][0]+dis[y][0];
}

void dfs(int x)
{
	v[x]=++tot,a[tot]=x;
	for(int i=head[x];i;i=next[i])
		if(!v[ver[i]]) dfs(ver[i]);
}

inline It L(It it)
{
	if(it==s.begin()) return --s.end();
	return --it;
}

inline It R(It it)
{
	if(it==--s.end()) return s.begin();
	return ++it;
}

int main()
{
	freopen("stone.in","r",stdin);
	freopen("stone.out","w",stdout); 
	cin>>n;
	t=(int)(log(n)/log(2)+0.1);
	for(i=1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z),add(y,x,z);
	}
	bfs();
	memset(v,0,sizeof(v)),tot=0;
	dfs(1);
	cin>>m;
	for(i=1;i<=m;i++)
	{
		scanf("%s",str);
		if(str[0]=='+')
		{
			scanf("%d",&x);
			if(s.size())
			{
				it=s.lower_bound(v[x]);
				if(it==s.end()) it=s.begin();
				y=*L(it);
				ans+=lca(x,a[y])+lca(x,a[*it])-lca(a[y],a[*it]);
			}
			s.insert(v[x]);
		} 
		if(str[0]=='-')
		{
			scanf("%d",&x);
			it=s.find(v[x]);
			y=*L(it),it=R(it);
			ans-=lca(x,a[y])+lca(x,a[*it])-lca(a[y],a[*it]);
			s.erase(v[x]);
		}
		if(str[0]=='?') printf("%I64d\n",ans/2);
	}
	return 0;
}

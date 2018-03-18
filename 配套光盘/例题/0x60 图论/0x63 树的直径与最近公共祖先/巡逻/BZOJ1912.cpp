#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int u=100010;
int ver[2*u],edge[2*u],next[2*u],head[u],d[u],pre[u],f[u],v[u],n,m,tot,p,i,x,y,z;
queue<int> q; 

void add(int x,int y)
{
	ver[++tot]=y; edge[tot]=1; next[tot]=head[x]; head[x]=tot;
}

int bfs(int s)
{
	int i,x,y;
	memset(d,0x3f,sizeof(d));
	q.push(s); d[s]=pre[s]=0;
	while(q.size())
	{
		x=q.front(); q.pop();
		for(i=head[x];i;i=next[i])
			if(d[ver[i]]==0x3f3f3f3f)
				d[ver[i]]=d[x]+edge[i],pre[ver[i]]=i,q.push(ver[i]);
	}
	for(x=y=1;x<=n;x++) if(d[x]>d[y]) y=x;
	return y;
}

int get()
{
	p=bfs(1);
	p=bfs(p);
	return d[p];
}

void change()
{
	for(;pre[p];p=ver[pre[p]^1]) edge[pre[p]]=edge[pre[p]^1]=-1;
}

void dp(int x)
{
	v[x]=1;
	for(int i=head[x];i;i=next[i])
		if(!v[ver[i]])
		{
			dp(ver[i]);
			y=max(y,f[ver[i]]+f[x]+edge[i]);
			f[x]=max(f[x],f[ver[i]]+edge[i]);
		}
}

int main()
{
	cin>>n>>m;
	tot=1;
	for(i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	x=get(),y=0,z=1;
	if(m==2) change(),dp(1),z=2;
	cout<<2*(n-1)-x-y+z<<endl;
	return 0;
}

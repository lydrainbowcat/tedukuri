#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int u=50010;
int ver[u*4],next[u*4],head[u],n,m,tot,i,j,t,x,y;
long long edge[u*4],d[u],f[u],a[u*10],ans,z;

void add(int x,int y,long long z)
{
	ver[++tot]=y; edge[tot]=z; next[tot]=head[x]; head[x]=tot;
}

void bfs()
{
	queue<int> q;
	memset(d,-1,sizeof(d));
	q.push(1); d[1]=0;
	while(q.size())
	{
		x=q.front(); q.pop();
		for(i=head[x];i;i=next[i])
			if(d[y=ver[i]]==-1)
			{
				d[y]=d[x]^edge[i];
				q.push(y);
			}
			else if(d[x]^d[y]^edge[i]) a[++t]=d[x]^d[y]^edge[i];
	}
}

void solve()
{
	for(i=1;i<=t;i++)
		for(j=60;j>=0;j--)
			if(a[i]>>j&1)
				if(!f[j]) {f[j]=a[i]; break;} else a[i]^=f[j];
	ans=d[n];
	for(i=60;i>=0;i--)
		if(!(ans>>i&1)) ans^=f[i];
}

int main()
{
	cin>>n>>m;
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%lld",&x,&y,&z);
		add(x,y,z),add(y,x,z);
	}
	bfs();
	solve();
	cout<<ans<<endl;
	return 0;
}
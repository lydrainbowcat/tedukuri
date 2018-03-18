#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int u=400010;
int ver[u],edge[u],next[u],head[u],n,m,tot,i,x,y,z;
long long d[u],f[u],ans;
void add(int x,int y,int z)
{
	ver[++tot]=y,edge[tot]=z,next[tot]=head[x],head[x]=tot;
}
int bfs(int s)
{
	memset(d,0x3f,sizeof(d));
	queue<int> q;
	q.push(s),d[s]=0;
	while(q.size())
	{
		int x=q.front();q.pop();
		for(i=head[x];i;i=next[i])
			if(d[ver[i]]>d[x]+edge[i])
				d[ver[i]]=d[x]+edge[i],q.push(ver[i]);
	}
	for(i=1;i<=n;i++)
		if(d[i]>d[s]) s=i;
	return s;
}
int main()
{
	cin>>n>>m;
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z),add(y,x,z);
	}
	x=bfs(1);
	y=bfs(x);
	memcpy(f,d,sizeof(d));
	bfs(y);
	for(i=1;i<=n;i++)
		ans=max(ans,min(d[i],f[i])+f[y]);
	cout<<ans<<endl;
	return 0; 
}
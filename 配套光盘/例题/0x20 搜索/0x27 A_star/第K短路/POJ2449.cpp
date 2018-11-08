// Author: SJZEZ wccy
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
using namespace std;
struct P
{
	int g,h,num;
};
struct cmp
{
	inline bool operator () (const P &x,const P &y) const
	{
		return x.g+x.h>y.g+y.h;
	}
};
const int T=1010;
const int M=100010;
priority_queue <P,vector<P>,cmp> q;
int dis[T];
int hd[T],to[M],nxt[M],w[M],gr;
int hd1[T],to1[M],nxt1[M],w1[M],gr1;
int n,m,cnt[T],st,ed,K;
bool vis[T];
inline void add(int x,int y,int z)
{
	nxt[gr]=hd[x],to[gr]=y,w[gr]=z,hd[x]=gr++;
}
inline void add1(int x,int y,int z)
{
	nxt1[gr1]=hd1[x],to1[gr1]=y,w1[gr1]=z,hd1[x]=gr1++;
}
int A()
{
	queue <int> qq;
	qq.push(ed),vis[ed]=1;
	memset(dis,0x3f,sizeof dis),dis[ed]=0;
	while(!qq.empty())
	{
		int u=qq.front();	qq.pop(),vis[u]=0;
		for(int i=hd1[u];~i;i=nxt1[i])
			if(dis[to1[i]]>dis[u]+w1[i])
			{
				dis[to1[i]]=dis[u]+w1[i];
				if(!vis[to1[i]])	vis[to1[i]]=1,qq.push(to1[i]);
			}
	}
	P tmp;	tmp.num=st,tmp.g=0,tmp.h=dis[st],q.push(tmp);
	while(!q.empty())
	{
		P now=q.top();	q.pop();
		++cnt[now.num];
		if(cnt[now.num]>K)	continue;
		if(now.num==ed&&cnt[ed]==K)	return now.g;
		for(int i=hd[now.num];~i;i=nxt[i])
		{
			tmp.num=to[i],tmp.g=now.g+w[i],tmp.h=dis[to[i]];
			q.push(tmp);
		}
	}
	return -1;
}
int main()
{
	memset(hd,-1,sizeof hd),memset(hd1,-1,sizeof hd1);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int x,y,z; scanf("%d%d%d",&x,&y,&z),add(x,y,z),add1(y,x,z);
	}
	scanf("%d%d%d",&st,&ed,&K);
	if(st==ed)	++K;
	printf("%d\n",A());
	return 0;
}
/*
    Author: wccy
    本程序仅供参考
*/
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int Mn = 10000 + 10 , Me = 2 * 10000 + 10;
int hd[Mn],nxt[Me],to[Me],w[Me],cnt;
int size[Mn],dis[Mn],g[Mn],tot;
bool vis[Mn];
int n,k;
inline void add(int x, int y, int z)
{
	to[cnt] = y;
	w[cnt] = z;
	nxt[cnt] = hd[x];
	hd[x] = cnt++;
}
inline void dfs_dis(int x,int dist,int p)
{
	dis[++tot] = dist;
	for(int i = hd[x]; ~i; i = nxt[i])
	if(!vis[to[i]] && i != p)
	dfs_dis(to[i],dist+w[i],i^1);
}
inline int find_root(int x,int p,int root)
{
	int minx = n;
	int ret(0);
	for(int i = hd[x];~i; i = nxt[i])
	if(!vis[to[i]] && i != p)
	{
		int tmp = find_root(to[i],i^1,root);
		if(g[tmp] < minx) 
		ret = tmp,minx = g[tmp];
	}
	g[x] = max(g[x],size[root]-size[x]);
	if(g[x] < minx) ret = x;
	return ret;
}
inline void dfs_root(int x,int p)
{
	size[x] = 1;
	g[x] = 0;
	for(int i = hd[x];~i; i = nxt[i])
	if(!vis[to[i]] && i != p)
	{
		dfs_root(to[i],i^1);
		size[x] += size[to[i]];
		g[x] = max(g[x],size[to[i]]);
	}
}
inline int get_root(int x)
{
	dfs_root(x,-1);
	return find_root(x,-1,x);
}
inline int calc(int x, int y)
{
	tot = 0;
	dfs_dis(x,y,-1);
	sort(dis+1,dis+tot+1);
	int j = tot;
	int res(0);
	for(int i = 1; i < j; i++)
	{
		while(dis[i] + dis[j] > k && i < j) j--;
		res += j-i;
	}
	return res;
}
inline int dfs(int x)
{
	int root = get_root(x);
	vis[root] = true;
	int res(0);
	res += calc(root,0);
	for(int i = hd[root]; ~i; i = nxt[i])
	if(!vis[to[i]])
	{
		res -= calc(to[i],w[i]);
		res += dfs(to[i]);
	}
	return res;
}
int main()
{
	while(scanf("%d%d",&n,&k),n+k)
	{
		cnt = 0;
		memset(hd,-1,sizeof hd);
		memset(vis,false,sizeof vis);
		for(int i = 1; i < n; i++)
		{
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			add(x,y,z);
			add(y,x,z);
		}
		printf("%d\n",dfs(1));
	}
}
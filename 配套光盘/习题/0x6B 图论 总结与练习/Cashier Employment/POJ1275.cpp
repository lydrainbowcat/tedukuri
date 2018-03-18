/*
    Author: wccy
    本程序仅供参考
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
using namespace std;
const int Mn = 3000, Me = 100000 + 10;
int hd[Mn],nxt[Me],to[Me],w[Me],cnt;
int dis[Mn],que[100000],tot[Mn];
bool vis[Mn];
int r[Mn],num[Mn],n;
inline void add(int x, int y, int z)
{
	to[cnt] = y;
	w[cnt] = z;
	nxt[cnt] = hd[x];
	hd[x] = cnt++;
}
inline bool spfa(int sum)
{
	memset(vis,false,sizeof vis);
	memset(dis,0x80,sizeof dis);
	memset(tot,0,sizeof tot);
	int h = 1, t = 2;
	que[1] = 0;
	dis[0] = 0;
	vis[0] = true;
	while(h < t)
	{
		int sta = que[h++];
		vis[sta] = false;
		tot[sta]++;
		if(tot[sta] > 24) return false;
		for(int i = hd[sta]; ~i; i = nxt[i])
		if(dis[to[i]] < dis[sta] + w[i])
		{
			dis[to[i]] = dis[sta] + w[i];
			if(!vis[to[i]])
			{
				vis[to[i]] = true;
				que[t++] = to[i];
			}
		}
	}
	return true;
}
inline void build(int sum)
{
	memset(hd,-1,sizeof hd);
	cnt = 0;
	for(int i = 1; i <= 24; i++)add(i,i-1,-num[i]),add(i-1,i,0);
	for(int i = 1; i <= 7; i++) add(i+16,i,r[i]-sum);
	for(int i = 8; i <= 24; i++) add(i-8,i,r[i]);
	add(0,24,sum);
	add(24,0,-sum);
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		memset(num,0,sizeof num);
		for(int i = 1; i <= 24; i++)
			scanf("%d",&r[i]);
		scanf("%d",&n);
		for(int i = 1; i <= n; i++)
		{
			int x;
			scanf("%d",&x);
			num[x+1]++;
		}
		bool flag = false;
		for(int i = 0; i <= n; i++)
		{
			build(i);
			if(spfa(i))
			{
				flag = true;
				printf("%d\n",i);
				break;
			}
		}
		if(!flag)
		puts("No Solution");
	}
	return 0;
}
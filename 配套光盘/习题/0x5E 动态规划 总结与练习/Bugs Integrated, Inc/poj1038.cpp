#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;
int n,m,k;
bool map[160][15];
int f[2][60000];
int a[2][60000];
int now[12];
int ans(0);
int p[15],q[15];
inline void open(int res[15], int x)
{
	for(int i = 1;i <= m; i++)
	{
		res[i] = x%3;
		x /= 3;
	}
}
inline int close(int ori[15])
{
	int res(0);
	int tmp = 1;
	for(int i = 1; i <= m; i++,tmp *= 3)
		res += ori[i] * tmp;
	return res;
}
inline void dfs(int pos, int s, int dt)
{
	int now = close(q);
	if(f[s][now] <= dt)
	{
		f[s][now] = dt;
		ans = max(ans,f[s][now]);
		for(int i = pos; i <= m; i++)
		{
			if(i + 1 <= m && p[i] == 0 && q[i] == 0 && p[i+1] == 0 && q[i+1] == 0)
			{
				p[i] = p[i+1] = q[i] = q[i+1] = 2;
				dfs(i+2,s,dt+1);
				p[i] = p[i+1] = q[i] = q[i+1] = 0;
			}
			else if(i + 2 <= m && q[i] == 0 && q[i+1] == 0 && q[i+2] == 0)
			{
				q[i] = q[i+1] = q[i+2] = 2;
				dfs(i+3,s,dt+1);
				q[i] = q[i+1] = q[i+2] = 0;
			}
		}
	}
	
}
int main()
{
	
	int T;
	scanf("%d",&T);
	while(T--)
	{
		ans  = 0;
		memset(map,false,sizeof map);
		memset(f,-1,sizeof f);
		scanf("%d%d%d",&n,&m,&k);
		for(int i = 1,x,y; i <= k; i++)
			scanf("%d%d",&x,&y),map[x][y] = true;
		int tot = (int)pow(3.0,double(m))-1;
		for(int i = 0; i <= tot; i++)
		a[0][i] = 2;
		f[0][tot] = 0;
		for(int i = 0; i < n; i++)
		{
			int last = i&1;
			int now = (i+1)&1;
			memset(f[now],-1,sizeof f[now]);
			for(int j = 0; j <= tot; j++)
			if(~f[last][j])
			{
				open(p,j);
				for(int k = 1; k <= m; k++)	q[k] = p[k]>0?p[k]-1:0;
				for(int k = 1; k <= m; k++)	q[k] = map[i+1][k]?2:q[k];
				dfs(1,now,f[last][j]);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;
bool map[15][15];
int f[15][1<<13];
bool ok[1<<13];
int n,m,tot;
inline bool judge(int x)
{
	while(x)
	{
		if((x&1) && ((x>>1)&1)) return false;
		x >>= 1;
	}
	return true;
}
inline bool fit(int num,int x)
{
	if(!ok[x]) 
		return false;
	int cnt(1);
	while(x)
	{
		if((x&1) && !map[num][cnt]) return false;
		cnt ++;
		x >>= 1;	
	}
	return true;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			scanf("%d",&map[i][j]);
	tot = (1<<m)-1;
	for(int i = 0; i <= tot; i++) ok[i] = judge(i);
	for(int i = 0; i <= tot; i++) if(fit(1,i)) f[1][i] = 1;
	for(int i = 2; i<= n; i++)
		for(int j = 0; j <= tot;j++)
			for(int k = 0; k <= tot; k++)
				if(fit(i,j) && (j & k) == 0)
					f[i][j] += (f[i-1][k])%100000000,f[i][j] %= 100000000;
	int ans(0);
	for(int i = 0; i <= tot; i++)
		ans += f[n][i]%100000000,ans %= 100000000;
	printf("%d\n",ans%100000000);
	return 0;
}
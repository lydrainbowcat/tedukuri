#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
int f[210][210][210],a[210],p[210],b[210];
inline int dp(int i, int j, int k)
{
	if(~f[i][j][k]) return f[i][j][k];
	if(i == j) return f[i][j][k] = (a[j]+k)*(a[j]+k);
	f[i][j][k] = dp(i,j-1,0)+(a[j]+k)*(a[j]+k);
	for(int l = p[j];l >= i;l = p[l])
		f[i][j][k] = max(f[i][j][k],dp(i,l,a[j]+k)+dp(l+1,j-1,0));
	return f[i][j][k]; 
}
int main()
{
	int T,cas(0);
	scanf("%d",&T);
	while(T--)
	{
		memset(f,-1,sizeof f);
		memset(b,0,sizeof b);
		int n;
		scanf("%d",&n);
		int y(-1),tot(0);
		for(int i = 1; i <= n; i++)
		{
			int x;
			scanf("%d",&x);
			if(x == y)
			a[tot]++;
			else 
			{
				p[++tot] = b[x];
				b[x] = tot;
				a[tot] = 1;
				y = x;
			}
		}
		printf("Case %d: %d\n",++cas,dp(1,tot,0));
	}
}
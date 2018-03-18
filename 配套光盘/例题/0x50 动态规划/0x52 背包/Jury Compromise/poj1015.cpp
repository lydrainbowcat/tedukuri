#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int f[30][810],path[30][810],a[210],b[210];
int n,m,now;
inline bool find(int i, int j, int k)
{
	if(i == 0) return false;
	if(path[i][j] == k) return true;
	return find(i-1,j-a[path[i][j]],k);
}
int main()
{
	int cas(0);
	while(scanf("%d%d",&n,&m),n+m)
	{
		memset(f,-1,sizeof f);
		now = 20 * m;f[0][now] = 0;
		for(int i = 1; i <= n; i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			a[i] = x-y;
			b[i] = x+y;
		}
		for(int i = 1; i <= m; i++)
			for(int j = 0;j <= 2 * now; j++)
				if(~f[i-1][j])
					for(int k = 1;k <= n; k++)
						if(!find(i-1,j,k))
							if(f[i][j+a[k]] < f[i-1][j] + b[k])
							{
								f[i][j+a[k]] = f[i-1][j] + b[k];
								path[i][j+a[k]] = k;
							}

		int ans(0x7fffffff),num,sum;
		for(int i = now;i <= 2*now;i++)
		if(~f[m][i])
		{
			ans = i - now;
			num = i;
			sum = f[m][i];
			break;
		}
		for(int i = now; i >= 0; i--)
		if(~f[m][i])
			if(now - i < ans ||(now - i == ans && f[m][i] > sum))
			{
				ans = i - now;
				num = i;
				sum = f[m][i];
				break;
			}
		printf("Jury #%d\n",++cas);
		int x = (sum+ans)>>1,y = sum - x;
		printf("Best jury has value %d for prosecution and value %d for defence: \n",x,y);
		x=m,y=num;
		int tot(0);
		int out[210];
		while(x)
		{
			out[++tot] = path[x][y];
			y -= a[path[x][y]];
			x--;
		}
		sort(out+1,out+tot+1);
		for(int i = 1; i <= tot; i++)
		printf(" %d",out[i]);
		puts("\n");
	}
	return 0;
} 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
bool a[30][30];
int b[30],n,m,i,j,k;
char x,y;
int main()
{
	while(~scanf("%d%d\n",&n,&m)&&n)
	{
		memset(a,0,sizeof(a));
		for(i=1;i<=n;i++) a[i][i]=1;
		for(i=1;i<=m;i++)
		{
			scanf("%c<%c\n",&x,&y);
			x=x-'A'+1,y=y-'A'+1;
			a[x][y]=1;
			for(j=1;j<=n;j++)
				for(k=1;k<=n;k++)
					if(a[j][x]&&a[y][k]) a[j][k]=1;
			for(j=1;j<n;j++)
				for(k=j+1;k<=n;k++)
					if(a[j][k]&&a[k][j])
					{
						printf("Inconsistency found after %d relations.\n",i);
						j=n; break;
					}
					else if(!a[j][k]&&!a[k][j]) x=0;
			if(j==n+1) break;
			if(x&&j==n)
			{
				printf("Sorted sequence determined after %d relations: ",i);
				memset(b,0,sizeof(b));
				for(j=1;j<n;j++)
					for(k=j+1;k<=n;k++)
						if(a[j][k]) b[j]++; else b[k]++;
				for(j=n-1;j>=0;j--)
					for(k=1;k<=n;k++)
						if(b[k]==j) {putchar(k+'A'-1); break;}
				puts(".");
				break;
			}
		}
		if(i>m) puts("Sorted sequence cannot be determined.");
		for(i++;i<=m;i++) scanf("%c<%c\n",&x,&y);
	}
	return 0;
}
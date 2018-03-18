#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int d[110][110],n,m,i,j,k,x,y,z;
long long f[110][110];
double ans;

int main()
{
	cin>>n>>m;
	memset(d,0x3f,sizeof(d));
	for(i=1;i<=n;i++) d[i][i]=0;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++) f[i][j]=1;
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		d[x][y]=d[y][x]=z;
	}
	for(k=1;k<=n;k++)
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				if(i!=j&&i!=k&&j!=k)
					if(d[i][k]+d[k][j]==d[i][j])
						f[i][j]+=f[i][k]*f[k][j];
					else if(d[i][k]+d[k][j]<d[i][j])
						d[i][j]=d[i][k]+d[k][j],f[i][j]=f[i][k]*f[k][j];
	for(i=1;i<=n;i++)
	{
		ans=0;
		for(j=1;j<=n;j++)
			for(k=1;k<=n;k++)
				if(i!=j&&i!=k&&d[j][i]+d[i][k]==d[j][k])
					ans+=f[j][i]*f[i][k]*1.0/f[j][k];
		printf("%.3f\n",ans);
	}
	return 0;
}
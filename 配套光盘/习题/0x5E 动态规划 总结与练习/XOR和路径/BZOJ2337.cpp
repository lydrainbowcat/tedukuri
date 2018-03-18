#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
double c[110][110],a[110],ans;
int ver[20010],edge[20010],next[20010],head[110],du[110];
int n,m,tot,x,y,z,i,j,k;

void add(int x,int y,int z)
{
	ver[++tot]=y; edge[tot]=z; next[tot]=head[x]; head[x]=tot; du[x]++;
}

void solve()
{
	int i,j,k,p;
	double x;
	for(i=1;i<n;i++)
	{
		for(p=j=i;j<n;j++) if(fabs(c[j][i])>fabs(c[p][i])) p=j;
		for(k=0;k<=n;k++) swap(c[i][k],c[p][k]);
		for(j=i+1;j<=n;j++)
		{
			x=c[j][i]/c[i][i];
			for(k=0;k<=n;k++) c[j][k]=c[i][k]*x-c[j][k];
		}
	}
	for(i=n;i;i--)
	{
		for(j=i+1;j<=n;j++) c[i][0]-=c[i][j]*a[j];
		a[i]=c[i][0]/c[i][i];
	}
}

int main()
{
	cin>>n>>m;
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		if(x!=y) add(y,x,z);
	}
	for(k=0;k<31;k++)
	{
		memset(c,0,sizeof(c));
		memset(a,0,sizeof(a));
		for(i=1;i<=n;i++) c[i][i]=1;
		for(i=1;i<n;i++)
			for(j=head[i];j;j=next[j])
				if(edge[j]>>k&1) c[i][ver[j]]+=1.0/du[i],c[i][0]+=1.0/du[i]; else c[i][ver[j]]-=1.0/du[i];
		solve();
		ans+=a[1]*(1<<k);
	}
	printf("%.3f\n",ans);
	return 0;
}
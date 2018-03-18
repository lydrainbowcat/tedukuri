#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
__int64 f[110][100010],s[100010],a[100010],d[100010];
int n,m,p,i,j,k;
int main()
{
	cin>>n>>m>>p;
	for(i=2;i<=n;i++)
	{
		cin>>j;
		d[i]=d[i-1]+j;
	}
	for(i=1;i<=m;i++)
	{
		cin>>j>>k;
		a[i]=k-d[j];
	}
	sort(a+1,a+m+1);
	for(i=1;i<=m;i++) s[i]=s[i-1]+a[i];
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(i=1;i<=p;i++)
		for(j=1;j<=m;j++)
		{
			f[i][j]=f[i-1][j];
			for(k=0;k<j;k++)
				f[i][j]=min(f[i][j],f[i-1][k]+a[j]*(j-k)-(s[j]-s[k]));
		}
	cout<<f[p][m]<<endl;
}

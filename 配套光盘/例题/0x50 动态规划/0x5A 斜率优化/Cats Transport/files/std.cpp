#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
__int64 f[110][100010],s[100010],a[100010],d[100010],q[100010],g[100010];
int n,m,p,i,j,k,l,r;
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
	{
		for(j=1;j<=m;j++) g[j]=f[i-1][j]+s[j];
		q[l=r=1]=0;
		for(j=1;j<=m;j++)
		{
			while(l<r&&g[q[l+1]]-g[q[l]]<=a[j]*(q[l+1]-q[l])) l++;
			f[i][j]=min(f[i-1][j],g[q[l]]+a[j]*(j-q[l])-s[j]);
			if(g[j]>=0x3f3f3f3f3f3f3f3fll) continue;
			while(l<r&&(g[j]-g[q[r]])*(q[r]-q[r-1])<=(g[q[r]]-g[q[r-1]])*(j-q[r])) r--;
			q[++r]=j;
		}
	}
	cout<<f[p][m]<<endl;
}

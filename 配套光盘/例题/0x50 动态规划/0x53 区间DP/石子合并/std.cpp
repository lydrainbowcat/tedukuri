#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int f[310][310],a[310],sum[310],n;
int main()
{
	cin>>n;
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
		f[i][i]=0;
	}
	for(int len=1;len<n;len++)
		for(int i=1;i<=n-len;i++)
		{
			int j=i+len;
			for(int k=i;k<j;k++)
				f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]+sum[j]-sum[i-1]);
		}
	cout<<f[1][n]<<endl;
}
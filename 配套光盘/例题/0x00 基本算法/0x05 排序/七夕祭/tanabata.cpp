#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int u=100010; 
long long b[u],c[u],f[u];
long long n,m,t,i,j,x,y;

long long calc(long long a[u],int n)
{
	long long ans=0; int i;
	for(i=1;i<=n;i++)
	{
		a[i]-=a[0]/n;
		f[i]=f[i-1]+a[i];
	}
	sort(f+1,f+n+1);
	for(i=1;i<=n;i++) ans+=abs(f[i]-f[n+1>>1]);
	return ans;
}

int main()
{
	freopen("tanabata.in","r",stdin);
	freopen("tanabata.out","w",stdout); 
	cin>>n>>m>>t;
	for(i=1;i<=t;i++)
	{
		scanf("%d%d",&x,&y);
		b[x]++,c[y]++; 
	}
	for(i=1;i<=n;i++) b[0]+=b[i];
	for(i=1;i<=m;i++) c[0]+=c[i];
	if(b[0]%n==0&&c[0]%m==0)
		printf("both %lld\n",calc(b,n)+calc(c,m));
	else if(b[0]%n==0)
		printf("row %lld\n",calc(b,n));
	else if(c[0]%m==0)
		printf("column %lld\n",calc(c,m));
	else puts("impossible");
	return 0;
}

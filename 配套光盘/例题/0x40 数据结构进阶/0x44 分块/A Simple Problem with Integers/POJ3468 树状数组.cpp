#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int SIZE=100010;
int a[SIZE],n,m;
long long c[2][SIZE],sum[SIZE];

long long ask(int k,int x)
{
	long long ans=0;
	for(;x;x-=x&-x) ans+=c[k][x];
	return ans;
}

void add(int k,int x,int y)
{
	for(;x<=n;x+=x&-x) c[k][x]+=y;
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	while(m--)
	{
		char op[2]; int l,r,d;
		scanf("%s%d%d",op,&l,&r);
		if(op[0]=='C')
		{
			scanf("%d",&d);
			add(0,l,d);
			add(0,r+1,-d);
			add(1,l,l*d);
			add(1,r+1,-(r+1)*d);
		}
		else{
			long long ans=sum[r]+(r+1)*ask(0,r)-ask(1,r);
			ans-=sum[l-1]+l*ask(0,l-1)-ask(1,l-1);
			printf("%lld\n",ans);
		}
	}
}
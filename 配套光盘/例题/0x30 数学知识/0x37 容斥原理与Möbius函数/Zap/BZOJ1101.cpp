#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
int p[50010],n,a,b,c,d,i,j,ans;

int prime(int m)
{
	int i,temp=0,k=m;
	for(i=2;i*i<=k;i++)
		if(!(m%i))
		{
			temp++; m/=i;
			if(!(m%i)) return 0;
		}
	if(m>1) temp++;
	return (temp&1)?-1:1;
}

int main()
{
	for(i=1;i<=50000;i++) 
		p[i]=p[i-1]+prime(i);
	cin>>n;
	for(i=1;i<=n;i++)
	{
		scanf("%d%d%d",&a,&b,&d);
		a/=d; b/=d;
		if(a>b) swap(a,b);
		ans=0;
		for(j=1;j<=a;j=c+1)
		{
			c=min(a/(a/j),b/(b/j));
			ans+=(p[c]-p[j-1])*(a/j)*(b/j);
		}
		printf("%d\n",ans);
	}
	return 0;
}

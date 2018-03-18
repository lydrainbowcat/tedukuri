/*
    Author: wccy
    本程序仅供参考
*/
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using namespace std;
int x,y,n,m,l;
long long a,b,c,k0,t0,ans;
long long gcd(long long p,long long q)
{
	if(q==0) return p;
	return gcd(q,p%q);
}
void ext_gcd(long long p,long long q)
{
	if(q==0)
	{
		k0=1;
		t0=0;
		return;
	}
	ext_gcd(q,p%q);
	long long temp=k0;
	k0=t0;
	t0=temp-p/q*t0;
}
int main()
{
	scanf("%d%d%d%d%d",&x,&y,&m,&n,&l);
	a=m-n;b=y-x;
	if(a<0) a=-a,b=-b;
	c=gcd(a,l);
	if(b%c!=0) { printf("Impossible\n");return 0;}
	ext_gcd(a,l);
	ans=b/c*k0;
	l/=c;
	ans%=l;
	if(ans<=0) ans+=l;
	printf("%lld\n",ans);
	return 0;
}
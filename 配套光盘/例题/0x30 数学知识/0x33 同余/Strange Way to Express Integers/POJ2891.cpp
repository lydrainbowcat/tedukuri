#include<iostream>
#include<cstdio>
using namespace std;
typedef long long LL;
int n,i,fail;
LL a,b,lcm,now,k,d,x,y;

LL exgcd(LL a,LL b,LL &x,LL &y)
{
	if(!b) {x=1; y=0; return a;}
	LL c=exgcd(b,a%b,x,y),z=x;
	x=y; y=z-y*(a/b);
	return c;
}

int main()
{
	while(cin>>n)
	{
		scanf("%lld%lld",&a,&b);
		lcm=a; now=b; fail=0;
		for(i=1;i<n;i++)
		{
			scanf("%lld%lld",&a,&b);
			b=(b-now%a+a)%a;
			d=exgcd(lcm,a,x,y);
			if(b%d==0) k=x*(b/d)%a; else fail=1;
			now+=k*lcm;
			lcm=lcm/d*a;
			now=(now%lcm+lcm)%lcm;
		}
		if(fail) cout<<"-1\n"; else cout<<now<<endl;
	}
	return 0;
}
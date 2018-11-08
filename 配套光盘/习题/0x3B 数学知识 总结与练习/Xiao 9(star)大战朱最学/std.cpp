#include<cstdio>
using namespace std;
typedef long long ll;
const ll N=15;
ll a[N],b[N];
ll re()
{
	ll x=0;
	char c=getchar();
	bool p=0;
	for(;c<'0'||c>'9';c=getchar())
		p=(c=='-'||p)?1:0;
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+(c-'0');
	return p?-x:x;
}
ll exgcd(ll a,ll b,ll& x,ll& y)
{
	int c,d;
	if(!b)
	{
		x=1;
		y=0;
		return a;
	}
	c=exgcd(b,a%b,x,y);
	d=x;
	x=y;
	y=d-y*(a/b);
	return c;
}
int main()
{
	ll i,x,y,n,s=0,M=1;
	n=re();
	for(i=1;i<=n;i++)
	{
		a[i]=re();
		b[i]=re();
		M*=a[i];
	}
	for(i=1;i<=n;i++)
	{
		exgcd(M/a[i],a[i],x,y);
		x=(x+a[i])%a[i];
		(s+=b[i]*(M/a[i])*x)%=M;
	}
	printf("%lld",s);
	return 0;
}
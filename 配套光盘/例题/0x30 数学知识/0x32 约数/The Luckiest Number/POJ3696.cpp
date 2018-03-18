#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
ll a[200000],n,p,ans,i;
int t,m;

ll gcd(ll a,ll b)
{
	return b?gcd(b,a%b):a;
}

ll phi(ll n)
{
	ll i,m=n;
	for(i=2;i*i<=n;i++)
		if(n%i==0)
		{
			m=m/i*(i-1);
			while(n%i==0) n/=i;
		}
	if(n>1) m=m/n*(n-1);
	return m;
}

ll mul(ll a,ll b)
{
	int c=1000000;
	return (a*(b%c)%n+(a*c%n)*(b/c))%n;
}

ll pow(ll a,ll b)
{
	ll c=1;
	for(;b;b>>=1)
	{
		if(b&1) c=mul(c,a);
		a=mul(a,a);
	}
	return c;
}

int main()
{
	while(cin>>n&&n)
	{
		n=9*n/gcd(8,n);
		cout<<"Case "<<++t<<": ";
		if(gcd(10,n)==1)
		{
			p=phi(n); m=0;
			for(i=1;i*i<=p;i++)
				if(p%i==0)
				{
					a[++m]=i;
					if(i*i!=p) a[++m]=p/i;
				}
			sort(a+1,a+m+1);
			for(i=1;i<=m;i++)
				if(pow(10,a[i])==1) break;
			cout<<a[i]<<endl;
		}
		else cout<<"0\n";
	}
	return 0;
}
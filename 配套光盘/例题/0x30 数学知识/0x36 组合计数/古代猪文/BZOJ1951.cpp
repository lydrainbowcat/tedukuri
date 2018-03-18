#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
typedef long long ll;
const int a[4]={2,3,4679,35617};
int p[36000],b[4],n,g,ans,i,j,x,y,mod=999911658;

int power(int a,int b)
{
	int c=1;
	for(;b;b>>=1)
	{
		if(b&1) c=(ll)c*a%mod;
		a=(ll)a*a%mod;
	}
	return c;
}

void exgcd(int a,int b,int &x,int &y)
{
	if(!b) {x=1,y=0; return;}
	exgcd(b,a%b,x,y);
	int z=x; x=y; y=z-y*(a/b);
}

int inv(int a,int p)
{
	int x,y;
	exgcd(a,p,x,y);
	return (x%p+p)%p;
}

int calc(int x,int mod)
{
	int ans=1,y,a,b;
	for(y=n;x;x/=mod,y/=mod)
	{
		a=x%mod,b=y%mod;
		ans=(ll)ans*p[b]%mod*inv(p[a],mod)%mod*inv(b<a?0:p[b-a],mod)%mod;
	}
	return ans;
}

int main()
{
	cin>>n>>g;
	g%=mod+1;
	if(!g) {cout<<"0\n"; return 0;}
	for(p[0]=i=1;i<=a[3];i++) p[i]=(ll)p[i-1]*i%mod;
	for(i=1;i*i<=n;i++)
		if(n%i==0)
		{
			for(j=0;j<4;j++) b[j]=(b[j]+calc(i,a[j]))%a[j];
			if(i*i!=n)
				for(j=0;j<4;j++) b[j]=(b[j]+calc(n/i,a[j]))%a[j]; 
		}
	for(i=0;i<4;i++)
	{
		exgcd(mod/a[i],a[i],x,y);
		ans=(ans+(ll)x*(mod/a[i])%mod*b[i])%mod;
	}
	ans=(ans+mod)%mod,mod++;
	ans=power(g,ans);
	cout<<ans<<endl;
	return 0;
}
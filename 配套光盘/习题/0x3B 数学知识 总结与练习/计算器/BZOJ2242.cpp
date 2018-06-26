#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
typedef long long ll;
ll a[100010],b[100010],y,z,p,n,j,x,u,w,ans,d;
int head[100010],next[100010],i,tot,mod=99991,t,k;

ll power(ll a,ll b)
{
	ll t=1;
	for(;b;b>>=1)
	{
		if(b&1) t=t*a%p;
		a=a*a%p;
	}
	return t;
}

ll exgcd(ll a,ll b,ll &x,ll &y)
{
	if(!b) {x=1,y=0; return a;}
	ll d=exgcd(b,a%b,x,y),z;
	z=x,x=y,y=z-y*(a/b);
	return d;
}

void hash(ll z,ll y,ll j)
{
	ll x=z*power(y,j)%p,h=x%mod;
	for(int i=head[h];i;i=next[i])
		if(a[i]==x) {b[i]=j; return;}
	a[++tot]=x,b[tot]=j;
	next[tot]=head[h],head[h]=tot;
}

ll get(ll y,ll j)
{
	ll x=power(y,j),h=x%mod;
	for(int i=head[h];i;i=next[i])
		if(a[i]==x) return b[i];
	return -1;
}

int main()
{
	cin>>t>>k;
	while(t--)
	{
		cin>>y>>z>>p;
		memset(head,0,sizeof(head)); tot=0;
		if(k==1) ans=power(y,z);
		if(k==2)
		{
			if(!y&&z) ans=-1;
			else{
				z%=p; d=exgcd(y,p,u,w); p/=d;
				if(z%d) ans=-1; else ans=(u*z/d%p+p)%p;
			}
		}
		if(k==3)
		{
			z%=p;
			n=(int)sqrt(p)+1;
			x=power(y,n);
			if(!x) if(!z) ans=1; else ans=-1;
			else{
				for(i=0;i<=n;i++) hash(z,y,i);
				for(ans=-1,i=1;i<n;i++)
					if((j=get(x,i))!=-1)
						{ans=i*n-j; break;}
			}
		}
		if(ans==-1) cout<<"Orz, I cannot find x!\n"; else cout<<ans<<endl;
	}
	return 0;
}

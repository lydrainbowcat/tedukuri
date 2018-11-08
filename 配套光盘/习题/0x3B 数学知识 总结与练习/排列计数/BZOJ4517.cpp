#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define p 1000000007
#define N 1000000
#define ll long long
using namespace std;
ll d[N+3],jc[N+3];
ll n,m,t;
ll quickpow(ll num,ll x)
{
    ll base=num%p; ll ans=1;
    while (x)
    {
        if (x&1)
         ans=ans*base%p;
        x>>=1;
        base=base*base%p;
    } 
    return ans%p;
}
ll solve(ll n,ll m)
{
    ll a=quickpow(jc[m]*jc[n-m],p-2);
    return jc[n]*a%p;
}
void calc()
{
   jc[1]=1;
   for (ll i=2;i<=N;i++)
    jc[i]=jc[i-1]*i%p;
}
int main()
{
    scanf("%lld",&t);
    d[0]=1; d[1]=0; d[2]=1;
    for (ll i=3;i<=N;i++)
     d[i]=(i-1)*(d[i-1]+d[i-2])%p;
    calc();
    for (int T=1;T<=t;T++)
     {
        scanf("%lld%lld",&n,&m);
        if (m==0)
         {
            printf("%lld\n",d[n]);
            continue;
         }
        if (n==m)
         {
            printf("1\n");
            continue;
         }
        ll ans=solve(n,m)*d[n-m]%p;
        printf("%lld\n",ans%p);
     }
}
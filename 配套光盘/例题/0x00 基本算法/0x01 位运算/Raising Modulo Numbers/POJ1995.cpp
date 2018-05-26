#include<cstdio>
#include<iostream>
using namespace std;
typedef long long ll;
ll mod_pow(ll a,ll b,ll p)
{
    ll ans=1ll;
    a%=p;
    while(b)
    {
        if(b&1)
        ans=(ans*a)%p;
        a=(a*a)%p;
        b>>=1;
    } 
    return ans;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ll M,a,b,ans=0ll;
        scanf("%lld",&M);
        int H;
        scanf("%d",&H);
        while(H--)
        {
            scanf("%lld%lld",&a,&b);
            ans=(ans+mod_pow(a,b,M))%M;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
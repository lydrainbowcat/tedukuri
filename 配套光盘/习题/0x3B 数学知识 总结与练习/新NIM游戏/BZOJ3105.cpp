#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define N 105
#define ll long long
using namespace std;

int n,bin[35],a[N],ins[N];

int main()
{
    bin[0]=1;
    for (int i=1;i<=30;i++)
        bin[i]=bin[i-1]*2;
    scanf("%d",&n);
    ll ans=0;
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        ans+=a[i];
    }
    sort(a+1,a+n+1);
    for (int i=n;i>=1;i--)
    {
        int x=a[i];
        for (int j=30;j>=0;j--)
            if (a[i]&bin[j])
                if (!ins[j])
                {
                    ins[j]=a[i];
                    break;
                }
                else a[i]^=ins[j];
            if (a[i]) ans-=x;
    }
    printf("%lld",ans);
    return 0;
}

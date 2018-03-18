#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
int a[5100],f[5100],k[5100];
int main()
{
    int n; 
    scanf("%d",&n);
    for(int i = 1; i <= n; i++) scanf("%d",&a[i]);
    a[0] = 0x3f3f3f3f;
    for(int i = 1; i <= n; i++)
        for(int j = 0; j < i; j++)
            if(a[i] < a[j])
                f[i] = max(f[i],f[j]+1);
    k[0] = 1;
    for(int i = 1; i <= n; i++)
        for(int j = i-1; j >= 0; j--)
        {
            if(a[i] < a[j] && f[j] + 1 == f[i])
                k[i] += k[j]; 
            if(a[i] == a[j]) break;
        }
    int ans(0);
    for(int i = 1; i <= n; i++)
        ans = max(f[i],ans);
    int tot(0);
    for(int i = 1; i <= n; i++)
    if(f[i] == ans)
        tot += k[i];
    printf("%d %d\n",ans,tot);
    return 0;
}
#include <stdio.h>
#include <string.h>
const int maxn = 1000;
int  t[maxn], A[maxn];
char str1[maxn], str2[maxn];
int n, m;
void solve()
{
    int i, len, k;
    len = strlen(str1);
    for(i=len; i>=0; --i) t[len-1-i] = str1[i] -(str1[i]<58 ? 48: str1[i]<97 ? 55: 61);
    for(k=0; len;) {
        for(i=len; i>=1; --i) {
            t[i-1] +=t[i]%m*n;
            t[i] /= m;
        }
        A[k++] = t[0] % m;
        t[0] /=m;
        while(len>0&&!t[len-1])  len--;
    }
    str2[k] =NULL;
    for(i=0; i<k; i++)
        str2[k-1-i] = A[i]+(A[i]<10 ? 48: A[i]<36 ? 55:61);
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d%s",&n, &m, str1);
        solve();
        printf("%d %s\n%d %s\n\n", n, str1, m, str2);
    }
    return 0;
}

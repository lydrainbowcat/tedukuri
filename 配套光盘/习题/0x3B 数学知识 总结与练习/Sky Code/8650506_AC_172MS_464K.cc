#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int basket[10010], maxsign;
int odd[10010];

inline __int64 sel4 (__int64 a)
{
    if (a < 4) return 0;
    return a * (a - 1) * (a - 2) * (a - 3) / 24;
}
int judge (int a)
{
    int prime = 0, tt = a;
    for (int i = 2; i * i <= a; i++)
    {
        if (a % i == 0)
        {
            ++prime, a /= i;
            if (a % i == 0) return 0;
        }
    }
    if (a > 1) ++prime;
    if (prime & 1) return -1;
    else return 1;
}
void freethrow (int a)
{
    for (int i = 1; i * i <= a; i++)
    {
        if (a % i == 0)
        {
            ++basket[i], maxsign = max(maxsign, i);
            if (a != i * i)
            {
                int t = a / i;
                ++basket[t], maxsign = max(maxsign, t);
            }
        }
    }
}
int main ()
{
    for (int i = 1; i <= 10000; i++) odd[i] = judge(i);
    int n; while (scanf("%d", &n) == 1)
    {
        memset(basket, 0, sizeof basket), maxsign = 0;
        for (int i = 0; i < n; i++)
        {
            int a; scanf("%d", &a);
            freethrow(a);
        }
        __int64 ans = 0;
        for (int i = 1; i <= maxsign; i++)
            ans += sel4(basket[i]) * odd[i];
        printf("%I64d\n", ans);
    }
    return 0;
}

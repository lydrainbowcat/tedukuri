#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
using namespace std;

inline __int64 random (__int64 mod)
{
    unsigned __int64 ans = 0;
    for (int i = 0; i < 8; i++) ans = (ans << 8) | (rand() & 255);
    return ans % mod + 1;
}
int main ()
{
    srand(time(0));
    freopen("fra19.in", "w", stdout);
    int kase = 1000, add = 10, base = 22;
    printf("%d\n", kase);
    for (int i = 0; i < kase; i++)
    {
        int tt = rand() % add + base;
        __int64 a = random(1LL << (tt << 1)), b;
        do
        {
            b = random(1LL << (tt << 1));
        } while (b == a);
        printf("%d %I64d %I64d\n", tt, a, b);
    }
    return 0;
}

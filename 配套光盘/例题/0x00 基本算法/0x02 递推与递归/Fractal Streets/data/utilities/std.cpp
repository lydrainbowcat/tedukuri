#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

pair<__int64, __int64> recur (int stage, __int64 id)
{
    if (stage == 0) return make_pair(0, 0);
    __int64 max = 1 << (stage - 1), s = max * max;
    __int64 z = id / s, idsp = id % s;
    pair<__int64, __int64> psp = recur(stage - 1, idsp);
    if (z == 0 || z == 3) swap(psp.first, psp.second);
    if (z == 3)
    {
        psp.first = max - psp.first - 1;
        psp.second = max - psp.second - 1;
    }
    if (z == 1 || z == 2) psp.first += max;
    if (z == 3 || z == 2) psp.second += max;
    return psp;
}
int main ()
{
    freopen("fra19.in", "r", stdin);
    freopen("fra19.out", "w", stdout);
    int kase; for (scanf("%d", &kase); kase; --kase)
    {
        int n; __int64 h, o;
        scanf("%d %I64d %I64d", &n, &h, &o);
        pair<__int64, __int64> hp = recur(n, h - 1);
        pair<__int64, __int64> op = recur(n, o - 1);
        __int64 dx = abs(hp.first - op.first), dy = abs(hp.second - op.second);
        printf("%.0f\n", (double)sqrt(dx * dx + dy * dy) * 10);
    }
    return 0;
}

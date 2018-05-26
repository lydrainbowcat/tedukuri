#include <stdio.h>
#include <math.h>
#define MAX 19931117
#define min(a,b) ((a)<(b)?(a):(b))

int m, v, mins = MAX, mincake[30];

int maxcake (int n, int lr, int lh)
{
    int ans = 0, i;
    for (i = n, lr--, lh--; i <= m; i++, lr--, lh--)
    {
        ans += lr * lr * lh;
        if (ans >= 10000 || lr * lr * lh >= 10000) return 10000;
    }
    return ans;
}

void search (int n, int lr, int lh, int uv, int us)
{
    int r, h;
    if (us >= mins) return;
    else if (uv + mincake[m - n + 1] > v || uv + maxcake(n, lr, lh) < v) return;
    else if (n == m)
    {
        for (r = lr - 1; r >= 1; r--)
        {
            if ((v - uv) % (r * r)) continue;
            else
            {
                h = (v - uv) / (r * r);
                if (h >= lh) continue;
                mins = min(mins, us + 2 * r * h + (m == 1 ? r * r : 0));
            }
        } return;
    }
    else
    {
        for (r = lr - 1; r >= m - n + 1; r--)
        {
            for (h = min(lh - 1, (int)((v - uv) / (r * r))); h >= m - n + 1; h--)
            {
                if (n == 1) search(2, r, h, r * r * h, r * r + 2 * r * h);
                else search(n + 1, r, h, uv + r * r * h, us + 2 * r * h);
            }
        } return;
    }
}

int main ()
{
    int i, r, h;
    scanf("%d %d", &v, &m);
    mincake[0] = 0;
    for (i = 1; i <= m; i++)
        mincake[i] = mincake[i - 1] + i * i * i;
    search(1, 101, 10001, 0, 0);
    if (mins == MAX) printf("0\n");
    else printf("%d\n", mins);
    return 0;
}

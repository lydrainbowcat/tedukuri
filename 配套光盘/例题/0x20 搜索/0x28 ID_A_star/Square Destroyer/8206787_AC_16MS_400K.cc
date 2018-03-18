#include <cstdio>
#include <cstdlib>
using namespace std;

int n, maxs, sqmr;
__int64 square[60], base_square[6][6];

inline int hori  (int r, int c) { return (2 * n + 1) * (r - 1) + c; }
inline int verti (int r, int c) { return (2 * n + 1) * (r - 1) + c + n; }
inline __int64 place (int r) { return ((__int64)1 << (r - 1)); }

void generate (void)
{
    int i, j, l, m, k; sqmr = 0;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            square[sqmr] = (place(hori(i, j)) | place(hori(i + 1, j)) | place(verti(i, j)) | place(verti(i, j + 1)));
            base_square[i - 1][j - 1] = square[sqmr++];
        }
    }
    for (k = 2; k <= n; k++)
    {
        for (i = 1; i + k - 1 <= n; i++)
        {
            for (j = 1; j + k - 1 <= n; j++)
            {
                square[sqmr] = 0;
                for (l = 0; l <= k - 1; l++)
                {
                    for (m = 0; m <= k - 1; m++)
                        square[sqmr] ^= base_square[i + l - 1][j + m - 1];
                } sqmr++;
            }
        }
    }
}

int maxdepth;
int dfs (__int64 serial, int step)
{
    int i, h = 0;
    __int64 ch, useful = 0, t = serial;
    for (i = 0; i < sqmr; i++)
    {
        if ((t & square[i]) == square[i])
        {
            h++; t ^= square[i];
            if (useful == 0) useful = square[i];
        }
    }
    if (h == 0) return 1;
    else if (step + h > maxdepth) return 0;
    for (i = 1; i <= maxs; i++)
    {
        ch = place(i);
        if (useful & ch)
            if (dfs(serial ^ ch, step + 1)) return 1;
    } return 0;
}

int main ()
{
    int kase, k, a; __int64 ori;
    scanf("%d", &kase);
    for (; kase > 0; kase--)
    {
        scanf("%d", &n);
        maxs = 2 * n * (n + 1);
        sqmr = 0; generate();
        ori = (((__int64)1 << maxs) - 1);
        scanf("%d", &k);
        for (; k > 0; k--)
        {
            scanf("%d", &a);
            ori ^= place(a);
        }
        for (maxdepth = 0; ; maxdepth++)
            if (dfs(ori, 0)) break;
        printf("%d\n", maxdepth);
    }
    return 0;
}

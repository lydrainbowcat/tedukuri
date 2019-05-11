#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

// f[模][剩余数字数目][剩余数字的和][剩余位的模] = 合法方案数 
// f[S][i][j][k] = ∑(f[S][i - 1][j - R][(k - pwr[i - 1] * R) mod S], 0≤R≤9) 
// 边界条件 F[S][0][0][0] = 1 

int f[82][10][82][82], pwr[82][10];
inline int modabs (int a, int mod) { return ((a % mod) + mod) % mod; }
int num[10];
int count (int p, int sum, int mod, int s, bool e)
{
    if (s - sum < 0) return 0;
    else if (!e) return f[s][p + 1][s - sum][(s - mod) % s];
    else if (p == -1)
    {
        if (sum == s && mod == 0) return 1;
        else return 0;
    }
    else
    {
        int res = 0;
        for (int d = 0; d <= num[p]; d++)
            res += count(p - 1, sum + d, (mod + pwr[s][p] * d) % s, s, d == num[p]);
        return res;
    }
}
int fcount (int tt)
{
    if (tt == 0) return 0;
    int maxp = 0;
    while (tt) num[maxp++] = tt % 10, tt /= 10;
    int res = 0;
    for (int i = 1; i <= 81; i++) res += count(maxp - 1, 0, 0, i, true);
    return res;
}
int main ()
{
    freopen("mystery.in", "r", stdin);
    freopen("mystery.out", "w", stdout);
    for (int s = 1; s <= 81; s++)
    {
        memset(f[s], 0, sizeof f[s]);
        f[s][0][0][0] = 1;
        pwr[s][0] = 1 % s;
        for (int i = 1; i <= 9; i++) pwr[s][i] = (pwr[s][i - 1] * 10) % s;
        for (int i = 1; i <= 9; i++)
        {
            for (int j = 0; j <= i * 9; j++)
            {
                for (int k = 0; k <= s; k++)
                {
                    for (int d = 0; d <= 9 && j - d >= 0; d++)
                        f[s][i][j][k] += f[s][i - 1][j - d][modabs(k - pwr[s][i - 1] * d, s)];
                }
            }
        }
    }
    int l, r; while (scanf("%d %d", &l, &r) == 2) printf("%d\n", fcount(r) - fcount(l - 1));
    fclose(stdin);
    fclose(stdout);
    return 0;
}

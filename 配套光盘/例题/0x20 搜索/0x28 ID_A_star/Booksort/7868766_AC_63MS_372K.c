#include <stdio.h>

int n, shell[21];

// swap [x1, x2] and [x2 + 1, x3]
void move (int x1, int x2, int x3)
{
     int tmp[21], i, j;
     for (i = x2 + 1, j = 0; i <= x3; i++, j++)
         tmp[j] = shell[i];
     for (i = x1; i <= x2; i++, j++)
         tmp[j] = shell[i];
     for (i = x1, j = 0; i <= x3; i++, j++)
         shell[i] = tmp[j];
     return;
}

int hfunc ()
{
    int i, ans = 0;
    for (i = 0; i < n - 1; i++)
        if (shell[i + 1] != shell[i] + 1) ans++;
    if (shell[n - 1] != n) ans++;
    return ans;
}

int maxdepth;
int dfs (int depth)
{
    int x1, x2, x3, h;
    for (x1 = 0; x1 <= n - 2; x1++)
    {
        for (x2 = x1; x2 <= n - 2; x2++)
        {
            for (x3 = x2 + 1; x3 <= n - 1; x3++)
            {
                move(x1, x2, x3);
                h = hfunc();
                if (h == 0) return 1;
                else if (3 * depth + h <= 3 * maxdepth)
                {
                     if (dfs(depth + 1)) return 1;
                }
                move(x1, x1 - x2 + x3 - 1, x3);
            }
        }
    } return 0;
}

int main ()
{
    int kase, i;
    scanf("%d", &kase);
    for (; kase > 0; kase--)
    {
        scanf("%d", &n);
        for (i = 0; i < n; i++)
            scanf("%d", &shell[i]);
        maxdepth = (int)ceil((double)hfunc() / 3);
        if (maxdepth) while (maxdepth < 5 && dfs(1) == 0) maxdepth++;
        if (maxdepth == 5) printf("5 or more\n");
        else printf("%d\n", maxdepth);
    }
    return 0;
}

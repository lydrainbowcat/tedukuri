#include <stdio.h>

int c[33][33];

int deter (int zero, int one, int free)
{
    int i, ans = 0;
    if (one)
    {
        for (i = 0; i <= free; i++)
        {
            if (zero + i < one + free - i) continue;
            else ans += c[free][i];
        } return ans;
    }
    else
    {
        ans = 1;
        for (i = 1; i <= free; i++)
            ans += deter(0, 1, free - i);
        return ans;
    }
}

int cal (int a)
{
    char digit[32];
    int mr, i, zero = 0, one = 0, ans = 0;
    for (mr = 0; a > 0; mr++)
    {
        digit[mr] = a % 2;
        a /= 2;
    }
    for (i = 1; i <= mr; i++)
    {
        if (digit[mr - i])
        {
            if (one) ans += deter(zero + 1, one, mr - i);
            else ans += deter(0, 0, mr - i);
            one++;
        }
        else zero++;
    }
    if (zero >= one) ans++;
    return ans;
}

int main ()
{
    int i, j, st, ed;
    c[0][0] = 1;
    for (i = 1; i <= 32; i++)
    {
        c[i][0] = c[i][i] = 1;
        for (j = 1; j < i; j++)
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
    }
    scanf("%d %d", &st, &ed);
    printf("%d\n", cal(ed) - cal(st - 1));
    return 0;
}

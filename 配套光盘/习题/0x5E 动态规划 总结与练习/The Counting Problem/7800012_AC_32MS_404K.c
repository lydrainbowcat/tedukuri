#include <stdio.h>
#include <math.h>

__int64 ans[10], cal[10];
int tre[10], arrx[9] = {0, 1, 20, 300, 4000, 50000, 600000, 7000000, 80000000};
int arrz[9] = {0, 1, 10, 190, 2890, 38890, 488890, 5888890, 68888890};

void deter (int a)
{
    memset(tre, 0, sizeof(tre));
    if (a == 0) tre[0] = 1;
    while (a)
    {
          tre[a % 10]++;
          a /= 10;
    } return;
}

int pwr10[9] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
int absorb (int a, int s)
{
    a /= pwr10[s - 1];
    return a % 10;
}

void calc (int ed)
{
    int digi = (int)(log10(ed) + 1), i, j, k, er, nsa = 0;
    memset(cal, 0, sizeof(cal));
    if (ed == 0) { cal[0] = 1; return; }
    for (i = digi; i >= 1; i--)
    {
        nsa *= 10;
        er = absorb(ed, i);
        for (j = 0; j < er; j++)
        {
            if (nsa + j != 0 || i == 1)
            {
               deter(nsa + j);
               for (k = 0; k < 10; k++)
                   cal[k] += (__int64)tre[k] * pwr10[i - 1];
            }
            for (k = 1; k < 10; k++)
                cal[k] += arrx[i - 1];
            if (nsa + j == 0) cal[0] += arrz[i - 1];
            else cal[0] += arrx[i - 1];
        }
        nsa += er;
    }
    deter(ed);
    for (k = 0; k < 10; k++)
        cal[k] += tre[k];
    return;
}

int main ()
{
    int x, y, t, i;
    while (1)
    {
          scanf("%d %d", &x, &y);
          if (x == 0 && y == 0) break;
          if (x > y) { t = x; x = y; y = t; }
          calc(y);
          for (i = 0; i < 10; i++)
              ans[i] = cal[i];
          calc(x - 1);
          for (i = 0; i < 10; i++)
              ans[i] -= cal[i];
          for (i = 0; i < 10; i++)
              printf("%I64d ", ans[i]);
          printf("\n");
    }
    return 0;
}

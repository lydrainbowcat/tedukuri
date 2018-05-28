#include <stdio.h>
#define min(a,b) ((a)<(b)?(a):(b))

__int64 dyna[30100];
int n, sum, row[5], pwr[5];

int vali (int *a)
{
    int i;
    for (i = 0; i < n - 1; i++)
        if (a[i] < a[i + 1]) return 0;
    for (i = 0; i < n; i++)
        if (a[i] > row[i]) return 0;
    return 1;
}

int generate (int *array)
{
    int ans = 0, i;
    for (i = 0; i < n; i++)
        ans += array[i] * pwr[i];
    return ans;
}

void turn (int *array)
{
    int cur = generate(array), tar, i;
    for (i = 0; i < n; i++)
    {
        array[i]++;
        if (vali(array))
        {
            tar = generate(array);
            dyna[tar] += dyna[cur];
        }
        array[i]--;
    } return;
}

void serial (int remain, int last, int *array, int idx)
{
    int i;
    if (remain == 0)
    {
        turn(array);
        return;
    }
    else if (idx == n - 1)
    {
        array[idx] = remain;
        if (vali(array)) turn(array);
        array[idx] = 0; return;
    }
    else
    {
        for (i = min(min(remain, last), row[idx]); i >= 1; i--)
        {
            array[idx] = i;
            serial(remain - i, i, array, idx + 1);
        }
        array[idx] = 0;
        return;
    }
}

int main ()
{
    int i, j, ar[6];
    while (1)
    {
        scanf("%d", &n);
        if (n == 0) break;
        sum = 0; memset(dyna, 0, sizeof(dyna));
        for (i = 0; i < n; i++)
        {
            scanf("%d", &row[i]);
            sum += row[i];
        }
        pwr[0] = 1;
        for (i = 1; i < n; i++)
            pwr[i] = pwr[i - 1] * (row[i - 1] + 1);
        dyna[1] = 1;
        for (i = 1; i <= sum; i++)
        {
            memset(ar, 0, sizeof(ar));
            serial(i, i, ar, 0);
        }
        printf("%I64d\n", dyna[pwr[n - 1] * (row[n - 1] + 1) - 1]);
    }
    return 0;
}

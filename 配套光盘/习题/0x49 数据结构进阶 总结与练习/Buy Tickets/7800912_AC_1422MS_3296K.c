#include <stdio.h>

int bit[200010], n;
int lowbit (int a) { return a & (-a); }
// 填充 1，很有技巧性 
void fillone ()
{
    int i;
    for (i = 1; i <= n; i++)
        bit[i] = lowbit(i);
    return;
}
void update (int idx)
{
    while (idx <= n)
    {
        bit[idx]--;
        idx += lowbit(idx);
    } return;
}
// 这是树状数组的高级操作 
int sumseek (int k)
{
    int ans = 0, sum = 0, i;
    for (i = 18; i >= 0; i--)
    {
        ans += (1 << i);
        if (ans >= n || sum + bit[ans] >= k) ans -= (1 << i);
        else sum += bit[ans];
    }
    return ans + 1;
}

int ans[200010], pos[200010], uid[200010];

int main ()
{
    int i, d;
    while (scanf("%d", &n) == 1) {
    for (i = 0; i < n; i++)
    {
        scanf("%d %d", &pos[i], &uid[i]);
        pos[i]++;
    }
    fillone();
    for (i = n - 1; i >= 0; i--)
    {
        d = sumseek(pos[i]);
        ans[d] = uid[i];
        update(d);
    }
    for (i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    printf("\n"); }
    return 0;
}



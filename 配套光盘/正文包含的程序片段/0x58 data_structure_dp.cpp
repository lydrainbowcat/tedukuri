// 例题：The Battle of Chibi
// 暴力枚举决策
const int mod = 1000000007;
memset(f, 0 ,sizeof(f));
a[0] = -(1<<30); // -INF
f[0][0] = 1;
for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++)
        for (int k = 0; k < j; k++)
            if (a[k] < a[j])
                f[i][j] = (f[i][j] + f[i-1][k]) % mod;
int ans = 0;
for (int i = 1; i <= n; i++)
    ans = (ans + f[m][i]) % mod;

// 树状数组优化
for (int i = 1; i <= m; i++) {
    memset(c, 0, sizeof(c));
    add(val(a[0]), f[i-1][0]); // 树状数组add操作
    for (int j = 1; j <= n; j++) {
        f[i][j] = ask(val(a[j]) - 1); // 树状数组ask操作
        add(val(a[j]), f[i-1][j]); // 树状数组add操作
    }
}

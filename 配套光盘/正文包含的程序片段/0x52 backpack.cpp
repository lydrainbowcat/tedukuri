// 01背包 ==========================================

memset(f, 0xcf, sizeof(f)); // -INF
f[0][0] = 0;
for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++)
        f[i][j] = f[i - 1][j];
    for (int j = v[i]; j <= m; j++)
        f[i][j] = max(f[i][j], f[i - 1][j - v[i]] + w[i]);
}

int f[2][MAX_M+1];
memset(f, 0xcf, sizeof(f)); // -INF
f[0][0] = 0;
for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++)
        f[i & 1][j] = f[(i - 1) & 1][j];
    for (int j = v[i]; j <= m; j++)
        f[i & 1][j] = max(f[i & 1][j], f[(i - 1) & 1][j - v[i]] + w[i]);
}
int ans = 0;
for (int j = 0; j <= m; j++)
    ans = max(ans, f[n & 1][j]);

int f[MAX_M+1];
memset(f, 0xcf, sizeof(f)); // -INF
f[0] = 0;
for (int i = 1; i <= n; i++)
    for (int j = m; j >= v[i]; j--)
        f[j] = max(f[j], f[j - v[i]] + w[i]);
int ans = 0;
for (int j = 0; j <= m; j++)
    ans = max(ans, f[j]);


// 例题：数字组合 ==========================================

int f[MAX_M+1];
memset(f, 0, sizeof(f));
f[0] = 1;
for (int i = 1; i <= n; i++)
    for (int j = m; j >= a[i]; j--)
        f[j] += f[j - a[i]];
cout << f[m] <<endl;


// 完全背包 ==========================================

int f[MAX_M+1];
memset(f, 0xcf, sizeof(f)); // -INF
f[0] = 0;
for (int i = 1; i <= n; i++)
    for (int j = v[i]; j <= m; j--)
        f[j] = max(f[j], f[j - v[i]] + w[i]);
int ans = 0;
for (int j = 0; j <= m; j++)
    ans = max(ans, f[j]);


// 例题：自然数拆分Lunatic版 ==========================================

unsigned int f[MAX_M+1];
memset(f, 0, sizeof(f));
f[0] = 1;
for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j++)
        f[j] = (f[j] + f[j - i]) % 2147483648u;
cout << (f[n] > 0 ? f[n] - 1 : 2147483647) <<endl;


// 多重背包，直接拆分 ==========================================

unsigned int f[MAX_M+1];
memset(f, 0xcf, sizeof(f)); // -INF
f[0] = 0;
for (int i = 1; i <= n; i++)
    for (int j = 1; j <= c[i]; j++)
        for (int k = m; k >= v[i]; k--)
            f[k] = max(f[k], f[k - v[i]] + w[i]);
int ans = 0;
for (int i = 0; i <= m; i++)
    ans = max(ans, f[i]);


// 例题：POJ1742 Coins (1) ==========================================

bool f[100010];
memset(f, 0, sizeof(f));
f[0] = true;
for (int i = 1; i <= n; i++)
    for (int j = 1; j <= c[i]; j++)
        for (int k = m; k >= a[i]; k--)
            f[k] |= f[k - a[i]];
int ans = 0;
for (int i = 1; i <= m; i++)
    ans += f[i];


// 例题：POJ1742 Coins (2) ==========================================

int used[100010];
for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++) used[j] = 0;
    for (int j = a[i]; j <= m; j++)
        if (!f[j] && f[j - a[i]] && used[j - a[i]] < c[i])
            f[j] = true, used[j] = used[j - a[i]] + 1;
}


// 分组背包 ==========================================

memset(f, 0xcf, sizeof(f));
f[0] = 0;
for (int i = 1; i <= n; i++)
    for (int j = m; j >= 0; j--)
        for (int k = 1; k <= c[i]; k++)
            if (j >= v[i][k])
                f[j] = max(f[j], f[j - v[i][k]] + w[i][k]);

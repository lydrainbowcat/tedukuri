// 例题：石子合并
memset(f, 0x3f, sizeof(f)); // INF
for (int i = 1; i <= n; i++) {
    f[i][i] = 0;
    sum[i] = sum[i-1] + a[i]; // 前缀和
}
for (int len = 2; len <= n; len++) // 阶段
    for (int l = 1; l <= n - len + 1; l++) { // 状态：左端点
        int r = l + len - 1; // 状态：右端点
        for (int k = l; k < r; k++) // 决策
            f[l][r] = min(f[l][r], f[l][k] + f[k+1][r]);
        f[l][r] += sum[r] - sum[l-1];
    }


// 例题：金字塔
const int MOD = 1000000000; // 对MOD取模
int f[310][310];

int solve(int l, int r) {
    if (l > r) return 0; // 递归边界
    if (l == r) return 1; // 递归边界
    if (f[l][r] != -1) return f[l][r]; // 记忆化
    f[l][r] = 0;
    for (int k = l + 2; k <= r; k++)
        f[l][r] = (f[l][r] + (long long)solve(l+1, k-1) * solve(k, r)) % MOD;
    return f[l][r];
}

memset(f, -1, sizeof(f)); // -1表示没有被计算过
solve(1, n);

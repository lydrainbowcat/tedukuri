// 例题：LCIS，O(N^3)
for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
        if (a[i] == b[j]) {
            for (int k = 0; k < j; k++)
                if (b[k] < a[i])
                    f[i][j] = max(f[i][j], f[i - 1][k] + 1);
        }
        else f[i][j] = f[i - 1][j];


// 例题：LCIS，O(N^2)
for (int i = 1; i <= n; i++) {
    // val是决策集合S(i,j)中f[i-1][k]的最大值
    int val = 0;
    // j=1时，0可以作为k的取值
    if (b[0] < a[i]) val = f[i - 1][0];
    for (int j = 1; j <= m; j++) {
        if (a[i] == b[j]) f[i][j] = val + 1;
        else f[i][j] = f[i - 1][j];
        // j即将增大为j+1，检查j能否进入新的决策集合
        if (b[j] < a[i]) val = max(val, f[i - 1][j]);
    }
}

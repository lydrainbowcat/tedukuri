#include<bits/stdc++.h>
using namespace std;
long long f[9][9][9][9][16]; // 均方差等式两边平方，然后同时乘n^3，避免分数
int n, a[9][9], sum[9][9];

inline long long sqr(long long x) {
    return x * x;
}

inline int rect_sum(int u, int d, int l, int r) { // 二维子矩阵和
    return sum[d][r] - sum[d][l - 1] - sum[u - 1][r] + sum[u - 1][l - 1];
}

int main() {
    cin >> n;
    for (int i = 1; i <= 8; i++)
        for (int j = 1; j <= 8; j++) {
            scanf("%d", &a[i][j]);
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
        }
    memset(f, 0x3f, sizeof(f));
    for (int len_row = 1; len_row <= 8; len_row++)
        for (int len_col = 1; len_col <= 8; len_col++)
            for (int u = 1; u <= 8 - len_row + 1; u++) // up
                for (int l = 1; l <= 8 - len_col + 1; l++) { // left
                    int d = u + len_row - 1; // down
                    int r = l + len_col - 1; // right
                    f[u][d][l][r][1] = sqr(n * rect_sum(u, d, l, r) - sum[8][8]);
                    for (int cnt = 2; cnt <= n; cnt++) { // 分成几块
                        for (int mid = u; mid < d; mid++) { // 横着切
                            f[u][d][l][r][cnt] = min(min(
                                f[u][mid][l][r][1] + f[mid + 1][d][l][r][cnt - 1], // 切掉上面一半
                                f[u][mid][l][r][cnt - 1] + f[mid + 1][d][l][r][1] // 切掉下面一半
                            ), f[u][d][l][r][cnt]);
                        }
                        for (int mid = l; mid < r; mid++) { // 竖着切
                            f[u][d][l][r][cnt] = min(min(
                                f[u][d][l][mid][1] + f[u][d][mid + 1][r][cnt - 1], // 切掉左边一半
                                f[u][d][l][mid][cnt - 1] + f[u][d][mid + 1][r][1]
                            ), f[u][d][l][r][cnt]);
                        }
                    }
                }
    cout << setprecision(3) << fixed << sqrt(f[1][8][1][8][n] * 1.0 / (n * n * n)) << endl;
}
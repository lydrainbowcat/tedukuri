#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
double a[20][20], b[20], c[20][20];
int n;
 
int main() {
    cin >> n;
    for (int i = 1; i <= n + 1; i++)
        for (int j = 1; j <= n; j++) scanf("%lf", &a[i][j]);
    // c: 系数矩阵，b: 常数，二者一起构成增广矩阵
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            c[i][j] = 2 * (a[i][j] - a[i + 1][j]);
            b[i] += a[i][j] * a[i][j] - a[i + 1][j] * a[i + 1][j];
        }
    // 高斯消元（数据保证有唯一解）
    for (int i = 1; i <= n; i++) {
        // 找到x[i]的系数不为0的一个方程
        for (int j = i; j <= n; j++) {
            if (fabs(c[j][i]) > 1e-8) {
                for (int k = 1; k <= n; k++) swap(c[i][k], c[j][k]);
                swap(b[i], b[j]);
            }
        }
        // 消去其它方程的x[i]的系数
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            double rate = c[j][i] / c[i][i];
            for (int k = i; k <= n; k++) c[j][k] -= c[i][k] * rate;
            b[j] -= b[i] * rate;
        }
    }
    for (int i = 1; i < n; i++) printf("%.3f ", b[i] / c[i][i]);
    printf("%.3f\n", b[n] / c[n][n]);
}

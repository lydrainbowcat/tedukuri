#include<bits/stdc++.h>
using namespace std;
const int T = 10000; // 平移避免负数
int a[105], n, t;
// f: 前i个数能否凑成j；g/s: true减号，false加号 
bool f[105][20005], g[105][20005], s[105];

inline bool valid(int x) { return x >= -T && x <= T;}

void sign(int i, int j) {
    if (i == 2) { s[1] = false, s[2] = true; return; }
    s[i] = g[i][j + T];
    if (s[i]) sign(i - 1, j + a[i]);
    else sign(i - 1, j - a[i]);
}

int main() {
    cin >> n >> t;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    f[2][a[1] - a[2] + T] = true;
    for (int i = 2; i < n; i++)
        for (int j = -T; j <= T; j++)
            if (f[i][j + T]) {
                if (valid(j - a[i + 1])) { // i + 1前面是负号
                    f[i + 1][j - a[i + 1] + T] = true;
                    g[i + 1][j - a[i + 1] + T] = true;
                }
                if (valid(j + a[i + 1])) { // i + 1前面是正号
                    f[i + 1][j + a[i + 1] + T] = true;
                    g[i + 1][j + a[i + 1] + T] = false;
                }
            }
    sign(n, t);
    // for (int i = 1; i <= n; i++) printf("%c", s[i] ? '-' : '+');
    // puts("");
    int merged = 0;
    // 先合并连续的加号
    // 例如 1-2-3+4+5+6-7 变成 1-2-(3-4-5-6)-7，3456合并起来
    for (int i = 2; i <= n; i++)
        if (!s[i]) printf("%d\n", i - 1 - merged), merged++;
    // 从左到右不断执行减号即可
    for (int i = 2; i <= n; i++)
        if (s[i]) puts("1");
}
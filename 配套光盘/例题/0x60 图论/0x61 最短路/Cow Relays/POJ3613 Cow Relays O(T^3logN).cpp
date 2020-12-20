// O(T^3logN)
#include<bits/stdc++.h>
using namespace std;
int n, t, s, e, len[105], a[105], b[105];
int vals[205], m, p; // p: 离散化之后的总点数
int ver[205], nxt[205], edge[205], head[205], tot;
int d[205][205], ans[205][205];

void mul(int a[205][205], int b[205][205]) {
    int c[205][205];
    memset(c, 0x3f, sizeof(c));
    for (int i = 1; i <= p; i++)
        for (int j = 1; j <= p; j++)
            for (int k = 1; k <= p; k++)
                c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
    memcpy(a, c, sizeof(c));
}

int main() {
    cin >> n >> t >> s >> e;
    // 离散化
    vals[++m] = s;
    vals[++m] = s;
    for (int i = 1; i <= t; i++) {
        scanf("%d%d%d", &len[i], &a[i], &b[i]);
        vals[++m] = a[i];
        vals[++m] = b[i];
    }
    sort(vals + 1, vals + m + 1);
    p = unique(vals + 1, vals + m + 1) - (vals + 1);
    s = lower_bound(vals + 1, vals + p + 1, s) - vals;
    e = lower_bound(vals + 1, vals + p + 1, e) - vals;
    memset(d, 0x3f, sizeof(d)); // 经过1条边的最短路
    for (int i = 1; i <= t; i++) {
        a[i] = lower_bound(vals + 1, vals + p + 1, a[i]) - vals;
        b[i] = lower_bound(vals + 1, vals + p + 1, b[i]) - vals;
        d[a[i]][b[i]] = min(d[a[i]][b[i]], len[i]);
        d[b[i]][a[i]] = min(d[b[i]][a[i]], len[i]);
    }

    memset(ans, 0x3f, sizeof(ans));
    ans[s][s] = 0; // 初值：经过0条边的最短路
    while (n) {
        if (n & 1) mul(ans, d);
        mul(d, d);
        n >>= 1;
    }
    cout << ans[s][e] << endl;
}
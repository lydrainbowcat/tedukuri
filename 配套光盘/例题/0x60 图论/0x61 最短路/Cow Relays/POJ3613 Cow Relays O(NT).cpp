// O(NT)
#include<bits/stdc++.h>
using namespace std;
int n, t, s, e, len[105], a[105], b[105];
int vals[205], m, p; // p: 离散化之后的总点数
int ver[205], nxt[205], edge[205], head[205], tot;
int f[205], d[205];
/*
void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, nxt[tot] = head[x], head[x] = tot;
}
*/
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
    for (int i = 1; i <= t; i++) {
        a[i] = lower_bound(vals + 1, vals + p + 1, a[i]) - vals;
        b[i] = lower_bound(vals + 1, vals + p + 1, b[i]) - vals;
        // add(a[i], b[i], len[i]);
        // add(b[i], a[i], len[i]);
    }

    memset(d, 0x3f, sizeof(d));
    d[s] = 0;
    for (int i = 1; i <= n; i++) { // 实际上是Bellman-Ford
        memcpy(f, d, sizeof(f));
        memset(d, 0x3f, sizeof(d));
        /*for (int j = 1; j <= p; j++) {
            for (int k = head[j]; k; k = nxt[k])
                if (d[j] > f[ver[k]] + edge[k]) d[j] = f[ver[k]] + edge[k];
        }*/
        for (int i = 1; i <= t; i++) {
            if (d[b[i]] > f[a[i]] + len[i]) d[b[i]] = f[a[i]] + len[i];
            if (d[a[i]] > f[b[i]] + len[i]) d[a[i]] = f[b[i]] + len[i];
        }
    }
    cout << d[e] << endl;
}
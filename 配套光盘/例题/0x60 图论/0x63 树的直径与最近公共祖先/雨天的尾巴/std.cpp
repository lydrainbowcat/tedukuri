#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
const int SIZE = 100010;
struct SegmentTree {
    int lc, rc, dat, pos;
} tr[SIZE * 20 * 4];
int f[SIZE][20], d[SIZE], root[SIZE], ans[SIZE];
int ver[2 * SIZE], Next[2 * SIZE], head[SIZE];
int X[SIZE], Y[SIZE], Z[SIZE], val[SIZE];
int T, n, m, tot, t, num, cnt;
queue<int> q;

inline char gc() {
    static char buf[1 << 16], *S, *T;
    if (T == S) { T = (S = buf) + fread(buf, 1, 1 << 16, stdin); if (T == S) return EOF; }
    return *S++;
}
inline int read() {
    int x = 0, f = 1; char ch = gc();
    while (ch<'0' || ch>'9') { if (ch == '-') f = -1; ch = gc(); }
    while (ch >= '0'&&ch <= '9') x = x * 10 + ch - '0', ch = gc();
    return x * f;
}

void add(int x, int y) {
    ver[++tot] = y; Next[tot] = head[x]; head[x] = tot;
}

void bfs() {
    q.push(1); d[1] = 1;
    while (q.size()) {
        int x = q.front(); q.pop();
        for (int i = head[x]; i; i = Next[i]) {
            int y = ver[i];
            if (d[y]) continue;
            d[y] = d[x] + 1;
            f[y][0] = x;
            for (int j = 1; j <= t; j++)
                f[y][j] = f[f[y][j - 1]][j - 1];
            q.push(y);
        }
    }
}

int lca(int x, int y) {
    if (d[x] > d[y]) swap(x, y);
    for (int i = t; i >= 0; i--)
        if (d[f[y][i]] >= d[x]) y = f[y][i];
    if (x == y) return x;
    for (int i = t; i >= 0; i--)
        if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    return f[x][0];
}

void insert(int p, int l, int r, int val, int delta) {
    if (l == r) {
        tr[p].dat += delta;
        tr[p].pos = tr[p].dat ? l : 0;
        return;
    }
    int mid = (l + r) >> 1;
    if (val <= mid) {
        if (!tr[p].lc) tr[p].lc = ++num;
        insert(tr[p].lc, l, mid, val, delta);
    }
    else {
        if (!tr[p].rc) tr[p].rc = ++num;
        insert(tr[p].rc, mid + 1, r, val, delta);
    }
    tr[p].dat = max(tr[tr[p].lc].dat, tr[tr[p].rc].dat);
    tr[p].pos = tr[tr[p].lc].dat >= tr[tr[p].rc].dat ? tr[tr[p].lc].pos : tr[tr[p].rc].pos;
}

int merge(int p, int q, int l, int r) {
    if (!p) return q;
    if (!q) return p;
    if (l == r) {
        tr[p].dat += tr[q].dat;
        tr[p].pos = tr[p].dat ? l : 0;
        return p;
    }
    int mid = (l + r) >> 1;
    tr[p].lc = merge(tr[p].lc, tr[q].lc, l, mid);
    tr[p].rc = merge(tr[p].rc, tr[q].rc, mid + 1, r);
    tr[p].dat = max(tr[tr[p].lc].dat, tr[tr[p].rc].dat);
    tr[p].pos = tr[tr[p].lc].dat >= tr[tr[p].rc].dat ? tr[tr[p].lc].pos : tr[tr[p].rc].pos;
    return p;
}

void dfs(int x) {
    for (int i = head[x]; i; i = Next[i]) {
        int y = ver[i];
        if (d[y] <= d[x]) continue;
        dfs(y);
        root[x] = merge(root[x], root[y], 1, cnt);
    }
    ans[x] = tr[root[x]].pos;
}

int main() {
    n = read(), m = read();
    t = (int)(log(n) / log(2)) + 1;
    for (int i = 1; i < n; i++) {
        int x = read(), y = read();
        add(x, y), add(y, x);
    }
    bfs();
    for (int i = 1; i <= n; i++) root[i] = ++num;
    for (int i = 1; i <= m; i++) {
        X[i] = read(), Y[i] = read(), Z[i] = read();
        val[i] = Z[i];
    }
    sort(val + 1, val + m + 1);
    cnt = unique(val + 1, val + m + 1) - val - 1;
    for (int i = 1; i <= m; i++) {
        int x = X[i], y = Y[i];
        int z = lower_bound(val + 1, val + cnt + 1, Z[i]) - val;
        int p = lca(x, y);
        insert(root[x], 1, cnt, z, 1);
        insert(root[y], 1, cnt, z, 1);
        insert(root[p], 1, cnt, z, -1);
        if (f[p][0]) insert(root[f[p][0]], 1, cnt, z, -1);
    }
    dfs(1);
    for (int i = 1; i <= n; i++) printf("%d\n", val[ans[i]]);
}
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
using namespace std;
const int SIZE = 300010;
int ver[SIZE * 2], Next[SIZE * 2], head[SIZE], tot;
int f[SIZE][20], d[SIZE], w[SIZE], v[SIZE];
int c1[SIZE * 2], c2[SIZE * 2], ans[SIZE];
int n, m, t;
queue<int> q;
vector<int> a1[SIZE], b1[SIZE], a2[SIZE], b2[SIZE];

void add(int x, int y) {
    ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void bfs() {
    t = log(n) / log(2);
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

void dfs(int x) {
    int val1 = c1[d[x] + w[x]], val2 = c2[w[x] - d[x] + n];
    v[x] = 1;
    for (int i = head[x]; i; i = Next[i]) {
        int y = ver[i];
        if (v[y]) continue;
        dfs(y);
    }
    for (int i = 0; i < a1[x].size(); i++) c1[a1[x][i]]++;
    for (int i = 0; i < b1[x].size(); i++) c1[b1[x][i]]--;
    for (int i = 0; i < a2[x].size(); i++) c2[a2[x][i] + n]++;
    for (int i = 0; i < b2[x].size(); i++) c2[b2[x][i] + n]--;
    ans[x] += c1[d[x] + w[x]] - val1 + c2[w[x] - d[x] + n] - val2;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int x, y; scanf("%d%d", &x, &y);
        add(x, y), add(y, x);
    }
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    bfs();
    for (int i = 1; i <= m; i++) {
        int x, y; scanf("%d%d", &x, &y);
        int z = lca(x, y);
        a1[x].push_back(d[x]);
        b1[f[z][0]].push_back(d[x]);
        a2[y].push_back(d[x] - 2 * d[z]);
        b2[z].push_back(d[x] - 2 * d[z]);
    }
    dfs(1);
    for (int i = 1; i < n; i++) printf("%d ", ans[i]);
    printf("%d\n", ans[n]);
}
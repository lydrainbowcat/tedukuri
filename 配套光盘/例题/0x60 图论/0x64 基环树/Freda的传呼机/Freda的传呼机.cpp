#include<bits/stdc++.h>
using namespace std;
const int MAXN = 12005;
int ver[4*MAXN], nxt[4*MAXN], edge[4*MAXN], head[MAXN], tot;
int d[MAXN], dist[MAXN], f[MAXN][20], dfn[MAXN], fa[MAXN], sum[MAXN], in[MAXN], len_cycle[MAXN];
bool broken[4*MAXN], v[MAXN];
int n, m, t, num, cnt;
queue<int> q;

void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, nxt[tot] = head[x], head[x] = tot;
}

void spfa() {
    memset(dist, 0x7f, sizeof(dist));
    dist[1] = 0;
    q.push(1); v[1] = true;
    while (!q.empty()) {
        int x = q.front();
        q.pop(); v[x] = false;
        for (int i = head[x]; i; i = nxt[i]) {
            int y = ver[i], z = edge[i];
            if (dist[y] > dist[x] + z) {
                dist[y] = dist[x] + z;
                if (!v[y]) { q.push(y); v[y] = true; }
            }
        }
    }
}

// s1, s2, ..., sp即为环上点
void get_cycle(int x, int y, int i) {
    cnt++; // 环的数量+1
    sum[y] = edge[i];
    broken[i] = broken[i ^ 1] = true;
    while (y != x) {
        in[y] = cnt;
        int next_y = ver[fa[y] ^ 1];
        sum[next_y] = sum[y] + edge[fa[y]];
        broken[fa[y]] = broken[fa[y] ^ 1] = true;
        add(x, y, dist[y] - dist[x]), add(y, x, dist[y] - dist[x]);
        y = next_y;
    }
    in[x] = cnt;
    len_cycle[cnt] = sum[x]; // 环总长度
}

void dfs(int x) {
    dfn[x] = ++num;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (!dfn[y]) {
            fa[y] = i;
            dfs(y);
        } else if ((i ^ 1) != fa[x] && dfn[y] >= dfn[x])
            get_cycle(x, y, i);
    }
}

void bfs() {
    d[1] = 1;
    q.push(1);
    while (q.size()) {
        int x = q.front(); q.pop();
        for (int i=head[x]; i; i=nxt[i]) {
            int y = ver[i];
            if (!d[y] && !broken[i]) {
                q.push(y);
                d[y] = d[x] + 1;
                f[y][0] = x;
                for (int k = 1; k <= 19; k++)
                    f[y][k] = f[f[y][k-1]][k-1];
            }
        }
    }
}

int calc(int x, int y) {
    if (d[x] < d[y]) swap(x, y);
    int ox = x, oy = y;
    for (int i = 19; i >= 0; i--)
        if (d[f[x][i]] >= d[y]) x = f[x][i];
    if (x == y) return dist[ox] - dist[oy];
    for (int i = 19; i >= 0; i--)
        if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    if (!in[x] || in[x] != in[y])
        return dist[ox] + dist[oy] - 2 * dist[f[x][0]];
    int l = abs(sum[y] - sum[x]); // 环上某个方向的距离
    return dist[ox] - dist[x] + dist[oy] - dist[y] + min(l, len_cycle[in[x]] - l);
}

int main() {
    cin >> n >> m >> t;
    tot = 1;
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
        add(y, x, z);
    }
    spfa();
    dfs(1);
    bfs();
    for (int i = 1; i <= t; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", calc(x, y));
    }
}
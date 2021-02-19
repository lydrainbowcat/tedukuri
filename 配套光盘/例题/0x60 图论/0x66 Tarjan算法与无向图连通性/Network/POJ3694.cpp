#include<bits/stdc++.h>
using namespace std;
const int N = 100005, M = 200005;
int ver[M*2], nxt[M*2], head[N], tot;
int vc[M*2], nc[M*2], hc[N], tc;
int dfn[N], low[N], c[N], n, m, q, num, dcc, ans, T;
int fa[N]/*并查集中的父节点*/, d[N], go[N]/*缩点之后的树上的父节点*/;
bool bridge[M*2];

void add(int x, int y) {
    ver[++tot] = y, nxt[tot] = head[x], head[x] = tot;
}
void add_c(int x, int y) {
    vc[++tc] = y, nc[tc] = hc[x], hc[x] = tc;
}

void tarjan(int x, int in_edge) {
    dfn[x] = low[x] = ++num;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (!dfn[y]) { // 树边
            tarjan(y, i);
            low[x] = min(low[x], low[y]);
            if (dfn[x] < low[y]) bridge[i] = bridge[i ^ 1] = true;
        }
        else if (i != (in_edge ^ 1))
            low[x] = min(low[x], dfn[y]);
    }
}

void dfs(int x) {
    c[x] = dcc;
    for (int i = head[x]; i; i = nxt[i])
        if (!bridge[i] && !c[ver[i]]) dfs(ver[i]);
}

void dfs_c(int x) {
    for (int i = hc[x]; i; i = nc[i]) {
        int y = vc[i];
        if (!d[y]) {
            d[y] = d[x] + 1;
            go[y] = x;
            dfs_c(y);
        }
    }
}

int get(int x) {
    return x == fa[x] ? x : (fa[x] = get(fa[x]));
}

void calc(int x, int y) {
    x = get(x), y = get(y);
    while (x != y) {
        if (d[x] < d[y]) swap(x, y);
        if (x == 1) break;
        // x到go[x]的边从桥边变为非桥边
        fa[x] = get(go[x]);
        ans--;
        x = get(x);
    }
}

int main() {
    while (cin >> n >> m && n) {
        memset(head, 0, sizeof(head));
        memset(dfn, 0, sizeof(dfn));
        memset(bridge, 0, sizeof(bridge));
        memset(c, 0, sizeof(c));
        memset(hc, 0, sizeof(hc));
        memset(d, 0, sizeof(d));
        tot = tc = 1;
        dcc = 0;
        for (int i = 1; i <= m; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            add(x, y), add(y, x);
        }
        tarjan(1, 0);
        for (int i = 1; i <= n; i++)
            if (!c[i]) {
                ++dcc;
                dfs(i);
            }
        for (int i = 2; i <= tot; i++) {
            int x = ver[i ^ 1], y = ver[i];
            if (c[x] == c[y]) continue;
            add_c(c[x], c[y]), add_c(c[y], c[x]);
        }
        ans = dcc - 1;
        d[1] = 1;
        dfs_c(1);
        for (int i = 1; i <= dcc; i++) fa[i] = i;
        printf("Case %d:\n", ++T);
        cin >> q;
        for (int i = 1; i <= q; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            x = c[x], y = c[y];
            if (x != y) calc(x, y);
            printf("%d\n", ans);
        }
        puts("");
    }
}
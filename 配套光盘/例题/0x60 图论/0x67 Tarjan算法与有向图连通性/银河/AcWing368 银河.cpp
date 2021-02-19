#include<bits/stdc++.h>
using namespace std;
const int N = 100005, M = 300005;
int head[N], edge[M], ver[M], nxt[M], tot;
int hc[N], ec[M], vc[M], nc[M], tc;
int dfn[N], low[N], c[N], s[N], n, m, num, top, cnt;
int in[N], d[N];
bool ins[N];
queue<int> q;

void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, nxt[tot] = head[x], head[x] = tot;
}

void add_c(int x, int y, int z) {
    vc[++tc] = y, ec[tc] = z, nc[tc] = hc[x], hc[x] = tc;
    in[y]++;
}

void tarjan(int x) {
    low[x] = dfn[x] = ++num;
    s[++top] = x; ins[x] = true;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        }
        else if (ins[y])
            low[x] = min(low[x], dfn[y]);
    }
    if (dfn[x] == low[x]) {
        cnt++; // 找到了一个SCC
        int y;
        do {
            y = s[top--];
            ins[y] = false;
            c[y] = cnt;
            // scc[cnt].push_back(y);
        } while (x != y);
    }
}

void topsort() {
    q.push(c[0]);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int i = hc[x]; i; i = nc[i]) {
            int y = vc[i];
            d[y] = max(d[y], d[x] + ec[i]);
            if (--in[y] == 0) q.push(y);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int z, x, y;
        scanf("%d%d%d", &z, &x, &y);
        if (z == 1) add(x, y, 0), add(y, x, 0);
        else if (z == 2) add(x, y, 1);
        else if (z == 3) add(y, x, 0);
        else if (z == 4) add(y, x, 1);
        else add(x, y, 0);
    }
    for (int i = 1; i <= n; i++) add(0, i, 1);
    for (int i = 0; i <= n; i++)
        if (!dfn[i]) tarjan(i);
    for (int x = 0; x <= n; x++)
        for (int i = head[x]; i; i = nxt[i]) {
            int y = ver[i];
            if (c[x] == c[y]) {
                if (edge[i] == 1) {
                    puts("-1");
                    return 0;
                }
                continue;
            }
            // 缩点后从c[x]到c[y]的有向边
            add_c(c[x], c[y], edge[i]);
        }
    topsort();
    long long ans = 0;
    for (int i = 1; i <= n; i++) ans += d[c[i]];
    cout << ans << endl;
}
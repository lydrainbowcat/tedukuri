#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 25005, MAX_M = 150005;
int head[MAX_N], ver[MAX_M], edge[MAX_M], mark[MAX_M], nxt[MAX_M], tot;
int n, m, p, s, c[MAX_N], cnt, deg[MAX_N], d[MAX_N];
bool v[MAX_N];
queue<int> q; // 存的是块号
vector<int> a[MAX_N]; // 每个“道路”连通块中的点
priority_queue<pair<int, int>> heap;

void add(int x, int y, int z, int k) { // k==0双向, k==1单向
    ver[++tot] = y, edge[tot] = z, mark[tot] = k;
    nxt[tot] = head[x], head[x] = tot;
}

void dfs(int x) {
    c[x] = cnt;
    a[cnt].push_back(x);
    for (int i = head[x]; i; i = nxt[i]) {
        if (mark[i] == 1) continue;
        int y = ver[i];
        if (!c[y]) dfs(y);
    }
}

void dijkstra(int k) { // 算k这一块的最短路
    for (int j = 0; j < a[k].size(); j++) { // for (auto x : a[k]) {
        int x = a[k][j]; // x是点号，k这块里面的所有点
        heap.push(make_pair(-d[x], x));
    }
    while (!heap.empty()) {
        int x = heap.top().second;
        heap.pop();
        if (v[x]) continue;
        v[x] = 1;
        for (int i = head[x]; i; i = nxt[i]) {
            int y = ver[i];
            if (mark[i] == 0) { // 正常的dijkstra模板
                if (d[y] > d[x] + edge[i]) {
                    d[y] = d[x] + edge[i];
                    heap.push(make_pair(-d[y], y));
                }
            } else {
                d[y] = min(d[y], d[x] + edge[i]);
                if (--deg[c[y]] == 0) q.push(c[y]); // 拓扑排序的更新
            }
        }
    }
}

int main() {
    cin >> n >> m >> p >> s;
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z, 0);
        add(y, x, z, 0);
    }
    for (int i = 1; i <= p; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z, 1);
    }
    for (int i = 1; i <= n; i++)
        if (c[i] == 0) {
            cnt++;
            dfs(i);
        }
    // 统计每块的总入度，只看航线
    for (int x = 1; x <= n; x++)
        for (int i = head[x]; i; i = nxt[i]) {
            if (mark[i] == 0) continue;
            // 这是一条从块c[x]到块c[ver[i]]的航线
            deg[c[ver[i]]]++;
        }
    // 对块拓扑排序
    for (int i = 1; i <= cnt; i++)
        if (!deg[i]) q.push(i);
    memset(d, 0x3f, sizeof(d));
    d[s] = 0;
    while (!q.empty()) {
        int k = q.front(); // k是块号
        q.pop();
        dijkstra(k);
    }
    for (int i = 1; i <= n; i++)
        if (d[i] > n * 10000) puts("NO PATH"); else printf("%d\n", d[i]);
}
#include<bits/stdc++.h>
using namespace std;
const int MAX_N = 100005, MAX_M = 1000005;
int head[MAX_N], ver[MAX_M], edge[MAX_M], nxt[MAX_M], tot;
int n, m, a[MAX_N], d[MAX_N]/*前缀min*/, f[MAX_N]/*后缀max*/;
bool v[MAX_N]; // 点是否在队列中
queue<int> q;

void add(int x, int y, int z) {
    tot++;
    ver[tot] = y;
    edge[tot] = z; // 1表示只能正着走，-1表示只能倒着走，2表示正反都可以
    nxt[tot] = head[x];
    head[x] = tot;
}

// 求d数组，从st出发，只有标记为z和2的边可以用
void spfa(int* d, int st, int z) {
    d[st] = a[st];
    q.push(st); v[st] = true;
    while (!q.empty()) {
        int x = q.front();
        q.pop(); v[x] = false;
        for (int i = head[x]; i; i = nxt[i])
            if (edge[i] == z || edge[i] == 2) {
                int y = ver[i];
                int val = z == 1 ? min(d[x], a[y]) : max(d[x], a[y]);
                if (z == 1 && d[y] > val || z == -1 && d[y] < val) {
                    d[y] = val;
                    if (!v[y]) { q.push(y); v[y] = true; }
                }
            }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
        add(y, x, z == 1 ? -1 : z);
    }
    memset(d, 0x3f, sizeof(d));
    spfa(d, 1, 1); // 从1出发求前缀min（d），只有1和2的边可以用
    memset(f, 0xcf, sizeof(f));
    spfa(f, n, -1); // 从n出发倒着求后缀max（d），只有-1和2的边可以用
    int ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, f[i] - d[i]);
    cout << ans << endl;
}
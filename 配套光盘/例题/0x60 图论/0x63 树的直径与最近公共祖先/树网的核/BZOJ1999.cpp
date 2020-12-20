#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
int ver[2*MAXN], nxt[2*MAXN], edge[2*MAXN], head[MAXN], tot;
int n, s, t;
queue<int> q;
int d[MAXN], pre[MAXN], a[MAXN], b[MAXN], f[MAXN], sum[MAXN];
bool v[MAXN];

void add(int x, int y, int z) {
    ver[++tot]=y, edge[tot]=z, nxt[tot]=head[x], head[x]=tot;
}

int bfs(int s) {
    memset(d, -1, sizeof(d));
    q.push(s); d[s] = 0;
    while (!q.empty()) {
        int x=q.front();
        q.pop();
        for (int i=head[x];i;i=nxt[i]) {
            int y=ver[i];
            if (d[y]==-1) {
                d[y]=d[x]+edge[i];
                pre[y]=i;
                q.push(y);
            }
        }
    }
    int p=s;
    for(int i=1;i<=n;i++)
        if(d[i]>d[p]) p=i;
    return p;
}

void dfs(int x) {
    v[x] = true;
    for (int i=head[x];i;i=nxt[i]) {
        int y=ver[i];
        if (v[y]) continue;
        dfs(y);
        f[x] = max(f[x], f[y] + edge[i]);
    }
}

int main() {
    cin >> n >> s;
    tot = 1;
    for (int i = 1; i < n; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
        add(y, x, z);
    }
    int p = bfs(1);
    int q = bfs(p);
    while (q!=p) {
        a[++t] = q;
        b[t+1] = edge[pre[q]];
        q = ver[pre[q]^1];
    }
    a[++t] = p;
    for (int i = 1; i <= t; i++) v[a[i]] = true;
    int maxf = 0;
    for (int i = 1; i <= t; i++) {
        dfs(a[i]);
        maxf = max(maxf, f[a[i]]);
        sum[i] = sum[i-1] + b[i];
    }
    int ans = 1 << 30;
    for (int i = 1, j = 1; i <= t; i++) {
        while (j < t && sum[j+1]-sum[i] <= s) j++;
        ans = min(ans, max(maxf, max(sum[i], sum[t] - sum[j])));
    }
    cout << ans << endl;
}
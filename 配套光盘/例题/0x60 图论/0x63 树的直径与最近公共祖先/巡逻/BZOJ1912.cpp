#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
int ver[2*MAXN], nxt[2*MAXN], edge[2*MAXN], head[MAXN], tot;
int n, k;
queue<int> q;
int d[MAXN], pre[MAXN], L2;

void add(int x, int y) {
    ver[++tot]=y, edge[tot]=1, nxt[tot]=head[x], head[x]=tot;
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
                d[y]=d[x]+1;
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

void update(int q, int p) {
    while (q!=p) {
        edge[pre[q]] = -1;
        edge[pre[q]^1] = -1;
        q = ver[pre[q]^1];
    }
}

void dp(int x, int fa) {
    for (int i=head[x];i;i=nxt[i]) {
        int y=ver[i];
        if (y == fa) continue;
        dp(y, x);
        L2 = max(L2, d[y] + edge[i] + d[x]);
        d[x] = max(d[x], d[y] + edge[i]);
    }
}

int main() {
    cin >> n >> k;
    tot = 1;
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    int p = bfs(1);
    int q = bfs(p);
    int ans = 2 * (n - 1) - d[q] + 1;
    if (k == 1) {
        cout << ans << endl;
        return 0;
    }
    update(q, p);
    memset(d, 0, sizeof(d));
    dp(1, 0);
    cout << ans - L2 + 1 << endl;
}
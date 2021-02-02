#include<bits/stdc++.h>
using namespace std;
const int N = 1000005;
int ver[N * 2], edge[N * 2], nxt[N * 2], head[N], tot;
int n, p, num, dfn[N], fa[N], s[N * 2], q[N * 2];
long long d[N], sum[2 * N], ans, ans_tot;
bool v[N];

void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, nxt[tot] = head[x], head[x] = tot;
}

// s1, s2, ..., sp即为环上点
void get_cycle(int x, int y, int z) {
    sum[1] = z;
    while (y != x) {
        s[++p] = y;
        sum[p + 1] = edge[fa[y]];
        y = ver[fa[y] ^ 1];
    }
    s[++p] = x;
    // 环断开，复制一遍
    for (int i = 1; i <= p; i++) {
        v[s[i]] = true;
        s[p + i] = s[i];
        sum[p + i] = sum[i];
    }
    for (int i = 1; i <= 2 * p; i++) sum[i] += sum[i - 1];
}

void dfs(int x) {
    dfn[x] = ++num;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (!dfn[y]) {
            fa[y] = i;
            dfs(y);
        } else if ((i ^ 1) != fa[x] && dfn[y] > dfn[x])
            get_cycle(x, y, edge[i]);
    }
}

void dp(int x) {
    v[x] = true;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (!v[y]) {
            dp(y);
            ans = max(ans, d[x] + d[y] + edge[i]);
            d[x] = max(d[x], d[y] + edge[i]);
        }
    }
}

int main() {
    cin >> n;
    tot = 1; // 成对存储
    for (int i = 1; i <= n; i++) {
        int y, z;
        scanf("%d%d", &y, &z);
        add(i, y, z), add(y, i, z);
    }
    for (int u = 1; u <= n; u++)
        if (!dfn[u]) {
            p = 0; ans = 0;
            dfs(u);
            for (int i = 1; i <= p; i++) dp(s[i]);
            int l = 1, r = 0;
            for (int i = 1; i <= 2 * p; i++) {
                while (l <= r && q[l] <= i - p) l++;
                if (l <= r) ans = max(ans, d[s[i]] + d[s[q[l]]] + sum[i] - sum[q[l]]);
                while (l <= r && d[s[q[r]]] - sum[q[r]] <= d[s[i]] - sum[i]) r--;
                q[++r] = i;
            }
            ans_tot += ans;
        }
    cout << ans_tot << endl;
}
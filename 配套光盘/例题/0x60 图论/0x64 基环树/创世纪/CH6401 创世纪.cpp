#include<bits/stdc++.h>
using namespace std;
const int N = 1000005;
int ver[N * 2], nxt[N * 2], head[N], tot;
int n, p, num, dfn[N], fa[N], a[N], ans_tot;
int f[N][2], root, broken;
bool v[N];

void add(int x, int y) {
    ver[++tot] = y, nxt[tot] = head[x], head[x] = tot;
}

void get_cycle(int x, int y, int i) {
    if (a[x] == y) root = x; // x-->y
    else root = y; // y-->x
    broken = i;
}

void dfs(int x) {
    dfn[x] = ++num;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (!dfn[y]) {
            fa[y] = i;
            dfs(y);
        } else if ((i ^ 1) != fa[x] && dfn[y] >= dfn[x]) // 加上等于号处理自环
            get_cycle(x, y, i);
    }
}

void dp(int x, int times) {
    f[x][0] = f[x][1] = 0;
    v[x] = true;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (!v[y] && i != broken && (i ^ 1) != broken) {
            dp(y, times);
            f[x][0] += max(f[y][0], f[y][1]);
        }
    }
    if (times == 2 && x == a[root]) {
        f[x][1] = f[x][0] + 1;
    } else {
        for (int i = head[x]; i; i = nxt[i]) {
            int y = ver[i];
            if (!v[y] && i != broken && (i ^ 1) != broken) {
                f[x][1] = max(f[x][1], f[y][0] + f[x][0] - max(f[y][0], f[y][1]) + 1);
            }
        }
    }
    v[x] = false;
}

int main() {
    cin >> n;
    tot = 1; // 成对存储
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        add(i, a[i]), add(a[i], i);
    }
    for (int u = 1; u <= n; u++)
        if (!dfn[u]) {
            dfs(u);
            dp(root, 1);
            int ans = max(f[root][0], f[root][1]);
            dp(root, 2);
            ans = max(ans, f[root][0]);
            ans_tot += ans;
        }
    cout << ans_tot << endl;
}
#include<bits/stdc++.h>
using namespace std;
int n, m, s, deg, ans;
int a[32][32], d[32], conn[32];
bool v[32], c[32];
int tree[32][32];
int ver[32], p;
int f[32], fx[32], fy[32]; // (fx[i], fy[i])就是1~i路径上的最大边，边权是f[i]

void read() {
    map<string, int> h;
    cin >> m;
    h["Park"] = 1; n = 1;
    memset(a, 0x3f, sizeof(a)); // 原图对应的邻接矩阵
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        char sx[12], sy[12];
        scanf("%s%s%d", sx, sy, &z);
        if (!h[sx]) h[sx] = ++n;
        if (!h[sy]) h[sy] = ++n;
        x = h[sx], y = h[sy];
        a[x][y] = min(a[x][y], z);
        a[y][x] = min(a[y][x], z);
    }
    cin >> s;
}

void prim(int root) { // 对ver中的p个点求最小生成树
    d[root] = 0;
    for (int i = 1; i <= p; i++) {
        int x = 0;
        for (int j = 1; j <= p; j++)
            if (!v[ver[j]] && (x == 0 || d[ver[j]] < d[x])) x = ver[j];
        v[x] = true; // 进入已选集合
        for (int j = 1; j <= p; j++) {
            int y = ver[j];
            if (!v[y] && d[y] > a[x][y])
                d[y] = a[x][y], conn[y] = x;
        }
    }
    // 连通块内部的最小生成树，连边
    int closest = root;
    for (int i = 1; i <= p; i++) {
        int x = ver[i];
        if (root == x) continue;
        ans += d[x];
        tree[conn[x]][x] = tree[x][conn[x]] = d[x];
        if (a[1][x] < a[1][closest]) closest = x;
    }
    // 每个连通块跟1号点连1条边
    deg++;
    ans += a[1][closest];
    tree[1][closest] = tree[closest][1] = a[1][closest];
}

void dfs(int x) { // 找连通块
    ver[++p] = x;
    c[x] = true;
    for (int y = 1; y <= n; y++)
        if (a[x][y] != 0x3f3f3f3f && !c[y]) dfs(y);
}

void prim_for_all_comp() {
    memset(d, 0x3f, sizeof(d));
    memset(v, 0, sizeof(v));
    memset(tree, 0x3f, sizeof(tree)); // 最小生成树对应的邻接矩阵
    c[1] = true;
    for (int i = 2; i <= n; i++)
        if (!c[i]) {
            p = 0;
            dfs(i);
            // ver中保存了连通块里面的点
            prim(i);
        }
}

void dp(int x) {
    v[x] = true;
    for (int y = 2; y <= n; y++)
        if (tree[x][y] != 0x3f3f3f3f && !v[y]) {
            if (f[x] > tree[x][y]) {
                f[y] = f[x];
                fx[y] = fx[x], fy[y] = fy[x];
            } else {
                f[y] = tree[x][y];
                fx[y] = x, fy[y] = y;
            }
            dp(y);
        }
    v[x] = false;
}

bool solve() {
    int min_val = 1 << 30, mini;
    for (int i = 2; i <= n; i++) { // 枚举从1出发的非树边(1, i)，看加哪一条
        if (tree[1][i] != 0x3f3f3f3f || a[1][i] == 0x3f3f3f3f) continue;
        // 加入非树边(1, i)，删去树边(fx[i], fy[i])
        if (a[1][i] - tree[fx[i]][fy[i]] < min_val) {
            min_val = a[1][i] - tree[fx[i]][fy[i]];
            mini = i;
        }
    }
    if (min_val >= 0) return false;
    ans += min_val;
    tree[1][mini] = tree[mini][1] = a[1][mini];
    tree[fx[mini]][fy[mini]] = tree[fy[mini]][fx[mini]] = 0x3f3f3f3f;
    // 重新计算以mini为根的子树的dp状态
    f[mini] = a[1][mini];
    fx[mini] = 1, fy[mini] = mini;
    v[1] = true;
    dp(mini);
    return true;
}

int main() {
    read();
    // 删掉1号点，找出每个连通块，各自求Prim
    prim_for_all_comp();
    memset(v, 0, sizeof(v));
    dp(1);
    while (deg < s) {
        if (!solve()) break;
        deg++;
    }
    printf("Total miles driven: ");
    cout << ans << endl;
}
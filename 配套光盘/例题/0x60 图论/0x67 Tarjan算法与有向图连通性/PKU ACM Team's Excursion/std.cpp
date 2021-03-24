#include<bits/stdc++.h>
using namespace std;
const int N = 100005, M = 200005, mod = 1000000007;
int ver[M*2], edge[M*2], nxt[M*2], head[N], tot;
int f[2][N], deg[2][N], d[N], pre[N], n, m, s, t, bus;
bool bridge[M*2];
int a[N], b[N], cnt; // 长度、是不是桥
int sum[N], sum_bri[N], ds[N], dt[N], ds_min[N];
int occur[N], first_occur[N];
queue<int> q;

void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, nxt[tot] = head[x], head[x] = tot;
}

void topsort(int s, int bit) {
    if (bit == 0) { // 只有正图需要求最短路
        memset(d, 0x3f, sizeof(d));
        d[s] = 0;
    }
    f[bit][s] = 1;
    for (int i = 1; i <= n; i++)
        if (deg[bit][i] == 0) q.push(i);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int i = head[x]; i; i = nxt[i])
            if ((i & 1) == bit) {
                int y = ver[i];
                f[bit][y] = (f[bit][y] + f[bit][x]) % mod; // 路径条数
                if (bit == 0 && d[y] > d[x] + edge[i]) {  // 最短路
                    d[y] = d[x] + edge[i];
                    pre[y] = i;
                }
                if (--deg[bit][y] == 0) q.push(y);
            }
    }
}

int main() {
    int C; cin >> C;
    while (C--) {
        memset(head, 0, sizeof(head));
        memset(deg, 0, sizeof(deg));
        memset(f, 0, sizeof(f));
        memset(bridge, 0, sizeof(bridge));
        memset(occur, 0, sizeof(occur));
        tot = 1; cnt = 0;
        cin >> n >> m >> s >> t >> bus;
        s++; t++;
        for (int i = 1; i <= m; i++) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            x++, y++;
            add(x, y, z); // 偶数边是正边（邻接表2, 4, 6,...位置）
            add(y, x, z); // 奇数边是反边
            deg[0][y]++; // 入度
            deg[1][x]++; // 出度
        }
        topsort(s, 0);
        if (f[0][t] == 0) { puts("-1"); continue; }
        topsort(t, 1);
        for (int i = 2; i <= tot; i += 2) {
            int x = ver[i ^ 1], y = ver[i];
            if ((long long)f[0][x] * f[1][y] % mod == f[0][t]) {
                bridge[i] = true;
            }
        }
        // O(M)判重边，用map可能超时
        for (int x = 1; x <= n; x++) {
            for (int i = head[x]; i; i = nxt[i]) {
                if (i & 1) continue; // 只考虑正边
                int y = ver[i];
                if (occur[y] == x) {
                    bridge[i] = false;
                    bridge[first_occur[y]] = false;
                } else {
                    occur[y] = x;
                    first_occur[y] = i;
                }
            }
        }
        while (t != s) {
            a[++cnt] = edge[pre[t]];
            b[cnt] = bridge[pre[t]];
            t = ver[pre[t] ^ 1];
        }
        // reverse(a + 1, a + cnt + 1); 不反过来也可以
        // reverse(b + 1, b + cnt + 1);
        for (int i = 1; i <= cnt; i++) {
            sum[i] = sum[i - 1] + a[i]; // 以i这条边为结尾（包含i）的前缀总长度
            sum_bri[i] = sum_bri[i - 1] + (b[i] ? a[i] : 0);
        }
        ds_min[0] = 1 << 30;
        for (int i = 1, j = 0; i <= cnt; i++) { // 恰好在i这条边的结尾处下车，前面的最小危险程度：ds[i]
            // 双指针扫描，让j+1~i这些边乘车，j这条边有可能部分乘车
            while (sum[i] - sum[j] > bus) j++;
            ds[i] = sum_bri[j];
            if (j > 0 && b[j]) ds[i] -= min(a[j], bus - (sum[i] - sum[j]));
            ds_min[i] = min(ds[i], ds_min[i - 1] + (b[i] ? a[i] : 0)); // i之前搭一次车：ds_min[i]，即书上的"ds[i]"
        }
        for (int i = cnt, j = cnt + 1; i; i--) { // 恰好在i这条边的开头处上车，后面的最小危险程度：ds[i]
            // 双指针扫描，让i~j-1这些边乘车，j这条边有可能部分乘车
            while (sum[j - 1] - sum[i - 1] > bus) j--;
            dt[i] = sum_bri[cnt] - sum_bri[j - 1];
            if (j <= cnt && b[j]) dt[i] -= min(a[j], bus - (sum[j - 1] - sum[i - 1]));
        }
        // 两段乘车分开的情况
        int ans = 1 << 30;
        for (int i = 1; i <= cnt; i++)
            ans = min(ans, dt[i] + ds_min[i - 1]);
        // 两段乘车接在一起，2*bus覆盖一次的情况
        for (int i = 1, j = 0; i <= cnt; i++) {
            while (sum[i] - sum[j] > 2 * bus) j++;
            int temp = sum_bri[j];
            if (j > 0 && b[j]) temp -= min(a[j], 2 * bus - (sum[i] - sum[j]));
            ans = min(ans, temp + sum_bri[cnt] - sum_bri[i]);
        }
        cout << ans << endl;
    }
}
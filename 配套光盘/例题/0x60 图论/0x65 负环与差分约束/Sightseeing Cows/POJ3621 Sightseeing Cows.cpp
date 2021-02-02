#include<bits/stdc++.h>
using namespace std;
const int MAX_N = 1005, MAX_M = 5005;
int fun[MAX_N];
struct {int x, y, time;} a[MAX_M];
int head[MAX_N], ver[MAX_M], nxt[MAX_M], cnt[MAX_N], tot;
double edge[MAX_M], d[MAX_N];
int n, m;
bool v[MAX_N]; // 点是否在队列中
queue<int> q;

// 插入一条从x到y长度z的有向边
void add(int x, int y, double z) {
    tot++;
    ver[tot] = y;
    edge[tot] = z;
    nxt[tot] = head[x]; // 在head[x]这条链的开头插入新点
    head[x] = tot;
}

// 判断有没有负环
bool spfa_neg_cycle() {
    while (!q.empty()) q.pop();
    for (int i = 1; i <= n; i++) {
        d[i] = 0; cnt[i] = 0;
        q.push(i);
        v[i] = true;
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop(); v[x] = false;
        for (int i = head[x]; i; i = nxt[i]) {
            int y = ver[i];
            double z = edge[i];
            if (d[y] > d[x] + z) {
                d[y] = d[x] + z;
                cnt[y] = cnt[x] + 1;
                if (cnt[y] >= n) return true;
                if (!v[y]) { q.push(y); v[y] = true; }
            }
        }
    }
    return false;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) scanf("%d", &fun[i]);
    for (int i = 1; i <= m; i++) scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].time);
    double l = 0, r = 1e6;
    while (r - l > 1e-4) {
        double mid = (l + r) / 2;
        memset(head, 0, sizeof(head));
        tot = 0;
        for (int i = 1; i <= m; i++) add(a[i].x, a[i].y, mid * a[i].time - fun[a[i].x]);
        if (spfa_neg_cycle()) l = mid; else r = mid;
    }
    printf("%.2f\n", r);
}
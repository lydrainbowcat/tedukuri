// 解法二：二分答案+双端队列BFS
#include<bits/stdc++.h>
using namespace std;
const int MAX_N = 1005, MAX_M = 20005;
int head[MAX_N], ver[MAX_M], edge[MAX_M], nxt[MAX_M], tot;
int n, m, k, d[MAX_N];
deque<int> q;

// 插入一条从x到y长度z的有向边
void add(int x, int y, int z) {
    tot++;
    ver[tot] = y;
    edge[tot] = z;
    nxt[tot] = head[x]; // 在head[x]这条链的开头插入新点
    head[x] = tot;
}

bool solve(int t) {
    memset(d, 0x7f, sizeof(d));
    d[1] = 0;
    q.push_back(1);
    while (!q.empty()) {
        int x = q.front();
        q.pop_front();
        for (int i = head[x]; i; i = nxt[i]) {
            int y = ver[i], z = edge[i] > t ? 1 : 0;
            if (d[y] > d[x] + z) {
                d[y] = d[x] + z;
                if (z == 0) q.push_front(y); else q.push_back(y);
            }
        }
    }
    return d[n] <= k;
}

int main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
        add(y, x, z);
    }
    int L = 0, R = 1000001;
    while (L < R) {
        int mid = (L + R) >> 1;
        if (solve(mid)) R = mid; else L = mid + 1;
    }
    if (L == 1000001) puts("-1"); else cout << L << endl;
}
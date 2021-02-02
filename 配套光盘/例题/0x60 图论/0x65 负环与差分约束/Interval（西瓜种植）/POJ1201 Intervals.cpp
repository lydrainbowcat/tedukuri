#include<bits/stdc++.h>
using namespace std;
const int MAX_N = 50005;
int head[MAX_N], ver[3 * MAX_N], edge[3 * MAX_N], nxt[3 * MAX_N], tot;
int n, d[MAX_N], cnt[MAX_N];
bool v[MAX_N];
queue<int> q;

void add(int x, int y, int z) {
    tot++;
    ver[tot] = y;
    edge[tot] = z;
    nxt[tot] = head[x];
    head[x] = tot;
}

inline int num(int x) {
    return x == -1 ? 50001 : x;
}

bool spfa() {
    memset(d, 0xcc, sizeof(d));
    d[num(-1)] = 0;
    q.push(num(-1)); v[num(-1)] = true;
    while (!q.empty()) {
        int x = q.front();
        q.pop(); v[x] = false;
        for (int i = head[x]; i; i = nxt[i]) {
            int y = ver[i], z = edge[i];
            if (d[y] < d[x] + z) {
                d[y] = d[x] + z;
                cnt[y] = cnt[x] + 1;
                if (cnt[y] >= 50002) return true;
                if (!v[y]) { q.push(y); v[y] = true; }
            }
        }
    }
    return false;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(num(x - 1), num(y), z);
    }
    for (int i = 0; i <= 50000; i++) {
        add(num(i - 1), num(i), 0);
        add(num(i), num(i - 1), -1);
    }
    spfa();
    cout << d[50000] << endl;
}
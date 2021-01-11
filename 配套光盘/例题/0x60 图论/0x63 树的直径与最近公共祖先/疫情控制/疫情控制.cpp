#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50005;
int ver[2*MAXN], edge[2*MAXN], nxt[2*MAXN], head[MAXN], tot;
int d[MAXN], f[MAXN][18], son[MAXN], army[MAXN];
long long dist[MAXN];
int n, m, cnt, p;
queue<int> q;
long long l, r;
pair<long long, int> a[MAXN]; // <rest, s>
bool has[MAXN], cover[MAXN], used[MAXN];

void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, nxt[tot] = head[x], head[x] = tot;
}

void bfs() {
    d[1] = 1;
    q.push(1);
    while (q.size()) {
        int x = q.front(); q.pop();
        for (int i=head[x]; i; i=nxt[i]) {
            int y = ver[i];
            if (!d[y]) {
                q.push(y);
                d[y] = d[x] + 1;
                dist[y] = dist[x] + edge[i];
                f[y][0] = x;
                for (int k = 1; k <= 17; k++)
                    f[y][k] = f[f[y][k-1]][k-1];
            }
        }
    }
}

pair<long long, int> go(int x, long long mid) {
    for (int i = 17; i >= 0; i--)
        if (f[x][i] > 1 && dist[x] - dist[f[x][i]] <= mid) {
            mid -= dist[x] - dist[f[x][i]];
            x = f[x][i];
        }
    return make_pair(mid, x);
}

void dfs(int x) {
    bool all_child_covered = true;
    bool is_leaf = true;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (d[y] <= d[x]) continue;
        dfs(y);
        all_child_covered &= cover[y];
        is_leaf = false;
        if (x == 1 && !cover[y]) son[++p] = y;
    }
    cover[x] = has[x] || (!is_leaf && all_child_covered);
}

bool cmp(int x, int y) {
    return dist[x] < dist[y];
}

bool solve(long long mid) {
    memset(has, 0, sizeof(has));
    memset(cover, 0, sizeof(cover));
    memset(used, 0, sizeof(used));
    cnt = p = 0;
    for (int i = 1; i <= m; i++) {
        pair<long long, int> pr = go(army[i], mid);
        long long rest = pr.first;
        int pos = pr.second;
        if (rest <= dist[pos]) has[pos] = true; // 一类军队
        else a[++cnt] = make_pair(rest - dist[pos], pos); // 二类军队（减去到根的时间）
    }
    dfs(1);
    sort(a + 1, a + cnt + 1);
    for (int i = 1; i <= cnt; i++) {
        long long rest = a[i].first;
        int s = a[i].second;
        if (!cover[s] && rest < dist[s])
            cover[s] = used[i] = true; // 上去就下不来了，就不要上去
    }
    sort(son + 1, son + p + 1, cmp);
    for (int i = 1, j = 1; i <= p; i++) {
        int s = son[i];
        if (cover[s]) continue;
        while (j <= cnt && (used[j] || a[j].first < dist[s])) j++;
        if (j > cnt) return false;
        j++; // 用j管辖s
    }
    return true;
}

int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
        add(y, x, z);
        r += z;
    }
    bfs();
    cin >> m;
    for (int i = 1; i <= m; i++) scanf("%d", &army[i]);
    while (l < r) {
        long long mid = (l + r) >> 1;
        if (solve(mid)) r = mid; else l = mid + 1;
    }
    cout << l << endl;
}
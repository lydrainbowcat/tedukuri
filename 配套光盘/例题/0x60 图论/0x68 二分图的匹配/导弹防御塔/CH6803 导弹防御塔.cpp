#include<bits/stdc++.h>
using namespace std;
const int N = 55;
const double eps = 1e-10;
int v[N*N], match[N*N], n, m;
double T1, T2, V;
struct {int x, y;} a[N], b[N];
double dist[N][N];
vector<int> ver[N];

bool dfs(int x) {
    for (int i = 0; i < ver[x].size(); i++) {
        int y = ver[x][i];
        if (v[y]) continue;
        v[y] = 1;
        if (!match[y] || dfs(match[y])) {
            match[y] = x;
            return true;
        }
    }
    return false;
}

int main() {
    cin >> n >> m >> T1 >> T2 >> V;
    T1 /= 60;
    for (int i = 1; i <= m; i++) scanf("%d%d", &a[i].x, &a[i].y);
    for (int i = 1; i <= n; i++) scanf("%d%d", &b[i].x, &b[i].y);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            dist[i][j] = sqrt((a[i].x - b[j].x) * (a[i].x - b[j].x) + (a[i].y - b[j].y) * (a[i].y - b[j].y)) / V;
    double l = 0, r = 1e8;
    while (r - l > 1e-8) {
        double mid = (l + r) / 2;
        int p = (mid+T2) / (T1+T2) + eps;
        p = min(p, m);
        for (int i = 1; i <= m; i++) {
            ver[i].clear();
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= p; k++) {
                    // i -> (j - 1) * p + k 连边？
                    if (k * T1 + (k - 1) * T2 + dist[i][j] < mid - eps) // <=
                        ver[i].push_back((j - 1) * p + k);
                }
        }
        memset(match, 0, sizeof(match));
        bool flag = true;
        for (int i = 1; i <= m; i++) {
            memset(v, 0, sizeof(v));
            if (!dfs(i)) { flag = false; break; }
        }
        if (flag) r = mid; else l = mid;
    }
    printf("%.6f\n", r);
}
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
const int N = 105;
const double eps = 1e-10;
double w[N][N]; // 边权
double la[N], lb[N], upd[N]; // 左、右部点的顶标
bool va[N], vb[N]; // 访问标记：是否在交错树中
int match[N]; // 右部点匹配了哪一个左部点
int last[N]; // 右部点在交错树中的上一个右部点，用于倒推得到交错路
int n;
struct {int x, y;} a[N], b[N];

bool dfs(int x, int fa) {
    va[x] = 1;
    for (int y = 1; y <= n; y++)
        if (!vb[y])
            if (fabs(la[x] + lb[y] - w[x][y]) < eps) { // 相等子图
                vb[y] = 1; last[y] = fa;
                if (!match[y] || dfs(match[y], y)) {
                    match[y] = x;
                    return true;
                }
            }
            else if (upd[y] > la[x] + lb[y] - w[x][y] + eps) {
                upd[y] = la[x] + lb[y] - w[x][y];
                last[y] = fa;
            }
            return false;
}

void KM() {
    for (int i = 1; i <= n; i++) {
        la[i] = -1e100;
        lb[i] = 0;
        for (int j = 1; j <= n; j++)
            la[i] = max(la[i], w[i][j]);
    }
    for (int i = 1; i <= n; i++) {
        memset(va, 0, sizeof(va));
        memset(vb, 0, sizeof(vb));
        for (int j = 1; j <= n; j++) upd[j] = 1e10;
        // 从右部点st匹配的左部点match[st]开始dfs，一开始假设有一条0-i的匹配
        int st = 0; match[0] = i;
        while (match[st]) { // 当到达一个非匹配点st时停止
            double delta = 1e10;
            if (dfs(match[st], st)) break;
            for (int j = 1; j <= n; j++)
                if (!vb[j] && delta > upd[j]) {
                    delta = upd[j];
                    st = j; // 下一次直接从最小边开始DFS
                }
            for (int j = 1; j <= n; j++) { // 修改顶标
                if (va[j]) la[j] -= delta;
                if (vb[j]) lb[j] += delta; else upd[j] -= delta;
            }
            vb[st] = true;
        }
        while (st) { // 倒推更新增广路
            match[st] = match[last[st]];
            st = last[st];
        }
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) scanf("%d%d", &b[i].x, &b[i].y);
    for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            w[i][j] = -sqrt((a[i].x - b[j].x) * (a[i].x - b[j].x) + (a[i].y - b[j].y) * (a[i].y - b[j].y));
    KM();
    for (int i = 1; i <= n; i++) printf("%d\n", match[i]);
}
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 100010, INF = 1e9;
struct rec {int op, x, y, z;} q[2 * N], lq[2 * N], rq[2 * N];
int n, m, t, c[N], ans[N];

int ask(int x) {
    int y = 0;
    for (; x; x -= x & -x) y += c[x];
    return y;
}

void change(int x, int y) {
    for (; x <= n; x += x & -x) c[x] += y;
}

void solve(int lval, int rval, int st, int ed) {
    if (st > ed) return;
    if (lval == rval) {
        for (int i = st; i <= ed; i++)
            if (q[i].op > 0) ans[q[i].op] = lval;
        return;
    }
    int mid = (lval + rval) >> 1;
    int lt = 0, rt = 0;
    for (int i = st; i <= ed; i++) {
        if (q[i].op == 0) { // 是一次赋值操作
            if (q[i].y <= mid) change(q[i].x, 1), lq[++lt] = q[i];
            else rq[++rt] = q[i];
        } else { // 是一次询问
            int cnt = ask(q[i].y) - ask(q[i].x - 1);
            if (cnt >= q[i].z) lq[++lt] = q[i];
            else q[i].z -= cnt, rq[++rt] = q[i];
        }
    }
    for (int i = ed; i >= st; i--) { // 还原树状数组
        if (q[i].op == 0 && q[i].y <= mid) change(q[i].x, -1);
    }
    for (int i = 1; i <= lt; i++) q[st + i - 1] = lq[i];
    for (int i = 1; i <= rt; i++) q[st + lt + i - 1] = rq[i];
    solve(lval, mid, st, st + lt - 1);
    solve(mid + 1, rval, st + lt, ed);
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int val; scanf("%d", &val);
        // a[i]=val等价于一次把第i个数赋值为val的操作
        q[++t].op = 0, q[t].x = i, q[t].y = val;
    }
    for (int i = 1; i <= m; i++) {
        int l, r, k; scanf("%d%d%d", &l, &r, &k);
        // 记录一次询问
        q[++t].op = i, q[t].x = l, q[t].y = r, q[t].z = k;
    }
    // 基于值域对t=n+m个操作进行整体分治
    solve(-INF, INF, 1, t);
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
}

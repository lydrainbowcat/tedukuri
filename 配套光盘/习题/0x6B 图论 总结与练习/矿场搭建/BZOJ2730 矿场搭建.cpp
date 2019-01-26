//Author:XuHt
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ull unsigned long long
using namespace std;
const int N = 1006;
int n, m, num, anscnt, data;
int v[N], w[N], dfn[N], low[N];
vector<int> e[N];
ull ans;

void tarjan(int x) {
    dfn[x] = low[x] = ++num;
    v[x] = 1;
    for (unsigned int i = 0; i < e[x].size(); i++) {
        int y = e[x][i];
        if (!v[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
            if (dfn[x] <= low[y]) ++v[x];
        } else low[x] = min(low[x], dfn[y]);
    }
    if ((x == 1 && v[x] > 2) || (x > 1 && v[x] > 1)) v[x] = 2;
    else v[x] = 1;
}

void dfs(int x, int &flag, int &cnt) {
    v[x] = 3;
    ++cnt;
    for (unsigned int i = 0; i < e[x].size(); i++) {
        int y = e[x][i];
        if (v[y] == 1) dfs(y, flag, cnt);
        else if (v[y] == 2 && w[y] != num) {
            ++flag;
            w[y] = num;
        }
    }
}

inline void work() {
    for (int i = 0; i < N; i++) e[i].clear();
    anscnt = n = num = 0;
    memset(v, -1, sizeof(v));
    memset(w, 0, sizeof(w));
    ans = 1;
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        n = max(n, max(x, y));
        v[x] = v[y] = 0;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    for (int i = 1; i <= n; i++)
        if (!v[i]) tarjan(i);
    num = 0;
    for (int i = 1; i <= n; i++)
        if (v[i] == 1) {
            ++num;
            int flag = 0, cnt = 0;
            dfs(i, flag, cnt);
            if (flag == 1) {
                ++anscnt;
                ans *= cnt;
            }
        }
    if (!anscnt) {
        anscnt = 2;
        ans = n * (n - 1) / 2;
    }
    printf("Case %d: %d %lld\n", ++data, anscnt, ans);
}

int main() {
    while (cin >> m && m) work();
    return 0;
}

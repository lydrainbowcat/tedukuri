//Author:XuHt
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 106;
int n, dfn[N], low[N], num = 0;
int st[N], top = 0, tot = 0, c[N], ru[N], chu[N];
bool v[N];
vector<int> e[N], scc[N], sc[N];

void tarjan(int x) {
    dfn[x] = low[x] = ++num;
    st[++top] = x;
    v[x] = 1;
    for (unsigned int i = 0; i < e[x].size(); i++) {
        int y = e[x][i];
        if (!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if (v[y]) low[x] = min(low[x], dfn[y]);
    }
    if (dfn[x] == low[x]) {
        v[x] = 0;
        scc[++tot].push_back(x);
        c[x] = tot;
        int y;
        while (x != (y = st[top--])) {
            scc[tot].push_back(y);
            v[y] = 0;
            c[y] = tot;
        }
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
		int x;
        while (scanf("%d", &x) && x) e[i].push_back(x);
	}
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);
    for (int x = 1; x <= n; x++)
        for (unsigned int i = 0; i < e[x].size(); i++) {
            int y = e[x][i];
            if (c[x] == c[y]) continue;
            sc[c[x]].push_back(c[y]);
            ru[c[y]]++;
            chu[c[x]]++;
        }
    int ansa = 0, ansb = 0;
    for (int i = 1; i <= tot; i++) {
        if (!ru[i]) ansa++;
        if (!chu[i]) ansb++;
    }
    cout << ansa << endl;
    int ans = max(ansa, ansb);
    if (tot == 1) puts("0");
    else cout << ans << endl;
    return 0;
}

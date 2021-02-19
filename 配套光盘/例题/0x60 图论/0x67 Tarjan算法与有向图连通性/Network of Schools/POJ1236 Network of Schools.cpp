#include<bits/stdc++.h>
using namespace std;
const int N = 105, M = 10005;
int head[N], ver[M], nxt[M], tot;
int dfn[N], low[N], c[N], s[N], n, num, top, cnt;
int in[N], out[N];
bool ins[N];

void add(int x, int y) {
    ver[++tot] = y, nxt[tot] = head[x], head[x] = tot;
}

void tarjan(int x) {
    low[x] = dfn[x] = ++num;
    s[++top] = x; ins[x] = true;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        }
        else if (ins[y])
            low[x] = min(low[x], dfn[y]);
    }
    if (dfn[x] == low[x]) {
        cnt++; // 找到了一个SCC
        int y;
        do {
            y = s[top--];
            ins[y] = false;
            c[y] = cnt;
            // scc[cnt].push_back(y);
        } while (x != y);
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int j;
        while (scanf("%d", &j), j) add(i, j);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);
    for (int x = 1; x <= n; x++)
        for (int i = head[x]; i; i = nxt[i]) {
            int y = ver[i];
            if (c[x] == c[y]) continue;
            // 缩点后从c[x]到c[y]的有向边
            in[c[y]]++, out[c[x]]++;
        }
    int zero_in = 0;
    int zero_out = 0;
    for (int i = 1; i <= cnt; i++) {
        if (!in[i]) zero_in++;
        if (!out[i]) zero_out++;
    }
    cout << zero_in << endl;
    cout << (cnt == 1 ? 0 : max(zero_in, zero_out)) << endl;
}
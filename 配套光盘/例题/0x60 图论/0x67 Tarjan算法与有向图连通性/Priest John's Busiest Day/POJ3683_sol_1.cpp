#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int u = 2010, w = 3000010;
int ver[w], Next[w], head[u], dfn[u], low[u], c[u], s[u], ins[u];
int ver2[w], Next2[w], head2[u], val[u], deg[u], opp[u];
int S[u], T[u], D[u], ex[w], ey[w];
int n, m, tot, tot2, num, t, p, e;
queue<int> q;

// 原图加边
void add(int x, int y) {
	ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
    ex[++e] = x, ey[e] = y;
}

// 缩点后的图加边
void add2(int x, int y) {
    ver2[++tot2] = y, Next2[tot2] = head2[x], head2[x] = tot2;
}

void tarjan(int x) {
	dfn[x] = low[x] = ++num;
	s[++p] = x, ins[x] = 1;
	for (int i = head[x]; i; i = Next[i])
		if (!dfn[ver[i]]) {
			tarjan(ver[i]);
			low[x] = min(low[x], low[ver[i]]);
		}
		else if (ins[ver[i]])
			low[x] = min(low[x], low[ver[i]]);
	if (dfn[x] == low[x]) {
		t++; int y;
		do { y = s[p--], ins[y] = 0; c[y] = t; } while (x != y);
	}
}

void topsort() {
    memset(val, -1, sizeof(val));
    // 缩点，建反图
	for (int i = 1; i <= e; i++)
		if (c[ex[i]] != c[ey[i]])
			add2(c[ey[i]], c[ex[i]]), deg[c[ex[i]]]++;
    // 零入度点入队
	for (int i = 1; i <= t; i++)
		if (!deg[i]) q.push(i);
    // 拓扑排序
	while (q.size()) {
		int k = q.front(); q.pop();
        // 赋值标记
		if (val[k] == -1) val[k] = 0, val[opp[k]] = 1;
		for (int i = head2[k]; i; i = Next2[i])
			if (--deg[ver2[i]] == 0) q.push(ver2[i]);
	}
    // 输出最终结果
	for (int i = 1; i <= n; i++)
		if (val[c[i]] == 0) printf("%02d:%02d %02d:%02d\n",
			S[i] / 60, S[i] % 60,
			(S[i] + D[i]) / 60, (S[i] + D[i]) % 60);
		else printf("%02d:%02d %02d:%02d\n",
			(T[i] - D[i]) / 60, (T[i] - D[i]) % 60,
			T[i] / 60, T[i] % 60);
}

bool overlap(int a, int b, int c, int d) {
	if (a >= c&&a<d || b>c&&b <= d || a <= c&&b >= d) return 1;
	return 0;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) 	{
        int sh, sm, th, tm;
		scanf("%d:%d %d:%d %d", &sh, &sm, &th, &tm, &D[i]);
		S[i] = sh * 60 + sm; T[i] = th * 60 + tm;
	}
	for (int i = 1; i < n; i++)
		for (int j = i + 1; j <= n; j++) {
            if (overlap(S[i], S[i] + D[i], S[j], S[j] + D[j]))
				add(i, n + j), add(j, n + i);
            if (overlap(S[i], S[i] + D[i], T[j] - D[j], T[j]))
				add(i, j), add(n + j, n + i);
            if (overlap(T[i] - D[i], T[i], S[j], S[j] + D[j]))
				add(n + i, n + j), add(j, i);
            if (overlap(T[i] - D[i], T[i], T[j] - D[j], T[j]))
				add(n + i, j), add(n + j, i);
        }
	for (int i = 1; i <= 2 * n; i++)
		if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; i++) 	{
		if (c[i] == c[n + i]) { puts("NO"); return 0; }
		opp[c[i]] = c[n + i], opp[c[n + i]] = c[i];
	}
    puts("YES");
	topsort();
	return 0;
}

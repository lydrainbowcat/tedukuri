// 二分图最大匹配：匈牙利算法
bool dfs(int x) {
	for (int i = head[x], y; i; i = next[i])
		if (!visit[y = ver[i]]) {
			visit[y] = 1;
			if (!match[y] || dfs(match[y])) {
                match[y]=x;
                return true;
            }
		}
	return false;
}

for (int i = 1; i <= n; i++) {
	memset(visit, 0, sizeof(visit));
    if (dfs(i)) ans++;
}

// 二分图带权最大匹配：KM算法
// 递归版，O(n^2*m)
const int N = 105;
int w[N][N]; // 边权
int la[N], lb[N]; // 左、右部点的顶标
bool va[N], vb[N]; // 访问标记：是否在交错树中
int match[N]; // 右部点匹配了哪一个左部点
int n, delta, upd[N];

bool dfs(int x) {
	va[x] = 1; // 访问标记：x在交错树中
	for (int y = 1; y <= n; y++)
		if (!vb[y])
			if (la[x] + lb[y] - w[x][y] == 0) { // 相等子图
				vb[y] = 1; // 访问标记：y在交错树中
				if (!match[y] || dfs(match[y])) {
					match[y] = x;
					return true;
				}
			}
			else upd[y] = min(upd[y], la[x] + lb[y] - w[x][y]);
	return false;
}

int KM() {
	for (int i = 1; i <= n; i++) {
		la[i] = -(1 << 30); // -inf
		lb[i] = 0;
		for (int j = 1; j <= n; j++)
			la[i] = max(la[i], w[i][j]);
	}
	for (int i = 1; i <= n; i++)
		while (true) { // 直到左部点找到匹配
			memset(va, 0, sizeof(va));
			memset(vb, 0, sizeof(vb));
			delta = 1 << 30; // inf
			for (int j = 1; j <= n; j++) upd[j] = 1 << 30; 
			if (dfs(i)) break;
			for (int j = 1; j <= n; j++)
				if (!vb[j]) delta = min(delta, upd[j]);
			for (int j = 1; j <= n; j++) { // 修改顶标
				if (va[j]) la[j] -= delta;
				if (vb[j]) lb[j] += delta;
			}
		}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans += w[match[i]][i];
	return ans;
}


// 递归版，O(n^3)，UOJ80 https://uoj.ac/problem/80
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
const int N = 405;
int w[N][N]; // 边权
long long la[N], lb[N], upd[N]; // 左、右部点的顶标
bool va[N], vb[N]; // 访问标记：是否在交错树中
int match[N]; // 右部点匹配了哪一个左部点
int last[N]; // 右部点在交错树中的上一个右部点，用于倒推得到交错路
int n, nl, nr, m, boy[N];

bool dfs(int x, int fa) {
	va[x] = 1;
	for (int y = 1; y <= n; y++)
		if (!vb[y])
			if (la[x] + lb[y] - w[x][y] == 0) { // 相等子图
				vb[y] = 1; last[y] = fa;
				if (!match[y] || dfs(match[y], y)) {
					match[y] = x;
					return true;
				}
			}
			else if (upd[y] > la[x] + lb[y] - w[x][y]) {
				upd[y] = la[x] + lb[y] - w[x][y];
				last[y] = fa;
			}
	return false;
}

long long KM() {
	for (int i = 1; i <= n; i++) {
		la[i] = -(1 << 30); // -inf
		lb[i] = 0;
		for (int j = 1; j <= n; j++)
			la[i] = max(la[i], 1ll * w[i][j]);
	}
	for (int i = 1; i <= n; i++) {
		memset(va, 0, sizeof(va));
		memset(vb, 0, sizeof(vb));
		memset(last, 0, sizeof(last));
		memset(upd, 0x7f, sizeof(upd));
		// 从右部点st匹配的左部点match[st]开始dfs，一开始假设有一条0-i的匹配
		int st = 0; match[0] = i;
		while (match[st]) { // 当到达一个非匹配点st时停止
			long long delta = 1ll << 60;
			if (dfs(match[st], st)) break;
			for (int j = 1; j <= n; j++)
				if (!vb[j] && upd[j] < delta) {
					delta = upd[j];
					st = j; // 下一次直接从最小边开始DFS
				}
			for (int j = 1; j <= n; j++) { // 修改顶标
				if (va[j]) la[j] -= delta;
				if (vb[j]) lb[j] += delta; else upd[j] -= delta;
			}
			vb[st] = 1;
		}
		while (st) { // 倒推更新增广路
			match[st] = match[last[st]];
			st = last[st];
		}
	}
	long long ans = 0;
	for (int i = 1; i <= n; i++) ans += w[match[i]][i];
	return ans;
}

int main() {
	cin >> nl >> nr >> m;
	n = max(nl, nr);
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		w[x][y] = z;
	}
	cout << KM() << endl;
	for (int i = 1; i <= nr; i++)
		if (match[i] && w[match[i]][i]) boy[match[i]] = i;
	for (int i = 1; i <= nl; i++) printf("%d ", boy[i]);
	puts("");
}


// 非递归版，O(n^3)，UOJ80 https://uoj.ac/problem/80
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
const int N = 405;
int w[N][N]; // 边权
long long la[N], lb[N], upd[N]; // 左、右部点的顶标
bool va[N], vb[N]; // 访问标记：是否在交错树中
int match[N], last[N]; // 右部点匹配了哪一个左部点
int n, nl, nr, m, boy[N];

void search(int x) {
	memset(va, 0, sizeof(va));
	memset(vb, 0, sizeof(vb));
	memset(last, 0, sizeof(last));
	for (int j = 1; j <= n; j++) upd[j] = 1ll << 60;
	int y = 0;
	match[0] = x;
	do {
		va[x] = true;
		long long delta = 1ll << 60; // inf
		int next_y = 0;
		for (int j = 1; j <= n; j++)
			if (!vb[j]) {
				if (upd[j] > la[x] + lb[j] - w[x][j]) {
					upd[j] = la[x] + lb[j] - w[x][j];
					last[j] = y;
				}
				if (upd[j] < delta) {
					delta = upd[j];
					next_y = j;
				}
			}
		// 当delta=0时，相当于沿着相等子图向下搜索一层
		// 当delta>0时，相当于直接回到最小边（新加入相等子图的边）处开始搜索
		if (delta) {
			for (int j = 1; j <= n; j++) { // 修改顶标
				if (va[j]) la[j] -= delta;
				if (vb[j]) lb[j] += delta; else upd[j] -= delta;
			}
		}
		vb[y = next_y] = true;
	} while (x = match[y]); // 直到找到增广路
	while (y) {
		match[y] = match[last[y]];
		y = last[y];
	}
}

long long KM() {
	for (int i = 1; i <= n; i++) {
		la[i] = -(1 << 30); // -inf
		lb[i] = 0;
		for (int j = 1; j <= n; j++)
			la[i] = max(la[i], 1ll * w[i][j]);
	}
	for (int i = 1; i <= n; i++) search(i);
	long long ans = 0;
	for (int i = 1; i <= n; i++)
		ans += w[match[i]][i];
	return ans;
}

int main() {
	cin >> nl >> nr >> m;
	n = max(nl, nr);
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		w[x][y] = z;
	}
	cout << KM() << endl;
	for (int i = 1; i <= nr; i++)
		if (match[i] && w[match[i]][i]) boy[match[i]] = i;
	for (int i = 1; i <= nl; i++) printf("%d ", boy[i]);
	puts("");
}

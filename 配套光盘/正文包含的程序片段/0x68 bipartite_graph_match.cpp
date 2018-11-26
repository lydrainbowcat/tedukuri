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

// 深度优先遍历框架
void dfs(int x) {
	v[x] = 1;
	for (int i = head[x]; i; i = next[i]) {
		int y = ver[i];
		if (v[y]) continue;
		dfs(y);
	}
}

// DFS序
void dfs(int x) {
	a[++m] = x;
	v[x] = 1;
	for (int i = head[x]; i; i = next[i]) {
		int y = ver[i];
		if (v[y]) continue;
		dfs(y);
	}
	a[++m] = x;
}

// 求树中各点的深度
void dfs(int x) {
	v[x] = 1;
	for (int i = head[x]; i; i = next[i]) {
		int y = ver[i];
		if (v[y]) continue; // 点y已经被访问过了
		d[y] = d[x] + 1;
		dfs(y);
	}
}

// 求树的重心
void dfs(int x) {
	v[x] = 1; size[x] = 1; // 子树x的大小
	int max_part = 0; // 删掉x后分成的最大子树的大小
	for (int i = head[x]; i; i = next[i]) {
		int y = ver[i];
		if (v[y]) continue; // 点y已经被访问过了
		dfs(y);
		size[x] += size[y];
		max_part = max(max_part, size[y]);
	}
	max_part = max(max_part, n - size[x]);
	if (max_part < ans) {
		ans = max_part;
		pos = x;
	}
}

// 划分图的连通块
void dfs(int x) {
	v[x] = cnt;
	for (int i = head[x]; i; i = next[i]) {
		int y = ver[i];
		if (v[y]) continue;
		dfs(y);
	}
}
for (int i = 1; i <= n; i++)
	if (!v[i]) {
		cnt++;
		dfs(i);
	}

// 广度优先遍历框架
void bfs() {
	memset(d, 0, sizeof(d));
	queue<int> q;
	q.push(1); d[1] = 1;
	while (q.size()) {
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = next[i]) {
			int y = ver[i];
			if (d[y]) continue;
			d[y] = d[x] + 1;
			q.push(y);
		}
	}
}

// 拓扑排序
void add(int x, int y) { // 在邻接表中添加一条有向边
	ver[++tot] = y, next[tot] = head[x], head[x] = tot;
	deg[y]++;
}
void topsort() {
	queue<int> q;
	for (int i = 1; i <= n; i++)
		if (deg[i] == 0) q.push(i);
	while (q.size()) {
		int x = q.front(); q.pop();
		a[++cnt] = x;
		for (int i = head[x]; i; i = next[i]) {
			int y = ver[i];
			if (--deg[y] == 0) q.push(y);
		}
	}
}
int main() {
	cin >> n >> m; // 点数、边数
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	topsort();
	for (int i = 1; i <= cnt; i++)
		printf("%d ", a[i]);
	cout << endl;
}
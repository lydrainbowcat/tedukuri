// 并查集
int fa[SIZE];

for (int i = 0; i <= n; i++) fa[i] = i;

int get(int x) {
	if (x == fa[x]) return x;
	return fa[x] = get(fa[x]);
}

void merge(int x, int y) {
	fa[get(x)] = get(y);
}

// 边带权的并查集
int get(int x) {
	if (x == fa[x]) return x;
	int root = get(fa[x]);  // 递归计算集合代表
	d[x] += d[fa[x]];       // 维护d数组——对边权求和
	return fa[x] = root;    // 路径压缩 
}

void merge(int x, int y) {
	x = get(x), y = get(y);
	fa[x] = y, d[x] = size[y];
	size[y] += size[x];
}

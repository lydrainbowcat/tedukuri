// 区间最值问题的ST算法
void ST_prework() {
	for (int i = 1; i <= n; i++) f[i][0] = a[i];
	int t = log(n) / log(2) + 1;
	for (int j = 1; j < t; j++)
		for (int i = 1; i <= n - (1<<j) + 1; i++)
			f[i][j] = max(f[i][j-1], f[i + (1<<(j-1))][j-1]);
}

int ST_query(int l, int r) {
	int k = log(r - l + 1) / log(2);
	return max(f[l][k], f[r - (1<<k) + 1][k]);
}

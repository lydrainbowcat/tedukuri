#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
long long a[100010], sum[100010], add[100010];
int L[100010], R[100010]; // 每段左右端点
int pos[100010]; // 每个位置属于哪一段
int n, m, t;

void change(int l, int r, long long d) {
	int p = pos[l], q = pos[r];
	if (p == q) {
		for (int i = l; i <= r; i++) a[i] += d;
		sum[p] += d*(r - l + 1);
	}
	else {
		for (int i = p + 1; i <= q - 1; i++) add[i] += d;
		for (int i = l; i <= R[p]; i++) a[i] += d;
		sum[p] += d*(R[p] - l + 1);
		for (int i = L[q]; i <= r; i++) a[i] += d;
		sum[q] += d*(r - L[q] + 1);
	}
}

long long ask(int l, int r) {
	int p = pos[l], q = pos[r];
	long long ans = 0;
	if (p == q) {
		for (int i = l; i <= r; i++) ans += a[i];
		ans += add[p] * (r - l + 1);
	}
	else {
		for (int i = p + 1; i <= q - 1; i++)
			ans += sum[i] + add[i] * (R[i] - L[i] + 1);
		for (int i = l; i <= R[p]; i++) ans += a[i];
		ans += add[p] * (R[p] - l + 1);
		for (int i = L[q]; i <= r; i++) ans += a[i];
		ans += add[q] * (r - L[q] + 1);
	}
	return ans;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	// 分块
	t = sqrt(n*1.0);
	for (int i = 1; i <= t; i++) {
		L[i] = (i - 1)*sqrt(n*1.0) + 1;
		R[i] = i*sqrt(n*1.0);
	}
	if (R[t] < n) t++, L[t] = R[t - 1] + 1, R[t] = n;
	// 预处理
	for (int i = 1; i <= t; i++)
		for (int j = L[i]; j <= R[i]; j++) {
			pos[j] = i;
			sum[i] += a[j];
		}
	// 指令
	while (m--) {
		char op[3];
		int l, r, d;
		scanf("%s%d%d", op, &l, &r);
		if (op[0] == 'C') {
			scanf("%d", &d);
			change(l, r, d);
		}
		else printf("%lld\n", ask(l, r));
	}
}
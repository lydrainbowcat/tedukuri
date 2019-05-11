//Author:XuHt
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
const int N = 1000006;
int n, a, b, c, q[N];
ll s[N], f[N];

double h(int x, int y) {
	return (double)(f[y] - f[x] + a * s[y] * s[y] - a * s[x] * s[x] - b * s[y] + b * s[x]) / (a * (s[y] - s[x]) << 1);
}

int main() {
	cin >> n >> a >> b >> c;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &s[i]);
		s[i] += s[i-1];
	}
	int l = 0, r = 0;
	for (int i = 1; i <= n; i++) {
		while (l < r && h(q[l], q[l+1]) < s[i]) ++l;
		f[i] = f[q[l]] + a * (s[i] - s[q[l]]) * (s[i] - s[q[l]]) + b * (s[i] - s[q[l]]) + c;
		while (l < r && h(q[r-1], q[r]) > h(q[r], i)) --r;
		q[++r] = i;
	}
	cout << f[n] << endl;
	return 0;
}

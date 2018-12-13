//Author:XuHt
#include <cstring>
#include <iostream>
using namespace std;
const int N = 36;
struct M {
	int a[N][N];
};
int n, k, m;

M add(M x, M y) {
	M ans;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			ans.a[i][j] = (x.a[i][j] + y.a[i][j]) % m;
	return ans;
}

M mul(M x, M y) {
	M ans;
	memset(ans.a, 0, sizeof(ans.a));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				ans.a[i][j] = (x.a[i][k] * y.a[k][j] % m + ans.a[i][j]) % m;
	return ans;
}

M ksm(M x, int k) {
	M ans;
	memset(ans.a, 0, sizeof(ans.a));
	for (int i = 0; i < n; i++) ans.a[i][i] = 1;
	while (k) {
		if (k & 1) ans = mul(ans, x);
		x = mul(x, x);
		k >>= 1;
	}
	return ans;
}

M get(M x, int k) {
	if (k == 1) return x;
	M y = ksm(x, (k + 1) >> 1);
	M z = get(x, k >> 1);
	return k & 1 ? add(x, mul(add(x, y), z)) : mul(add(ksm(x, 0), y), z);
}

int main() {
	M x;
	cin >> n >> k >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> x.a[i][j];
	x = get(x, k);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << x.a[i][j] << " ";
		cout << endl;
	}
	return 0;
}

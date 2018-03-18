#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a, b, m, ans = 1, mod = 9901;
int p[20], c[20];

void divide(int n) {
    m = 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            p[++m] = i, c[m] = 0;
            while (n % i == 0) n /= i, c[m]++;
        }
    }
    if (n > 1)
        p[++m] = n, c[m] = 1;
}

int power(int a, long long b) {
	int c = 1;
	for (; b; b >>= 1) {
		if (b & 1) c = (long long)c * a % mod;
		a = (long long) a * a % mod;
	}
	return c;
}

int main() {
	cin >> a >> b;
	divide(a); // 分解质因数 
	for (int i = 1; i <= m; i++) {
		if ((p[i] - 1) % mod == 0) { // 没有逆元时，特判 
			ans = ((long long)b * c[i] + 1) % mod * ans % mod;
			continue;
		}
		int x = power(p[i], (long long)b * c[i] + 1); // 分子
		x = (x - 1 + mod) % mod;
		int y = p[i] - 1; // 分母 
		y = power(y, mod - 2); // 根据费马小定理求乘法逆元
		ans = (long long)ans * x % mod * y % mod;
	}
	cout << ans <<endl;
}
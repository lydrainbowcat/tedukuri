#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int v[1010], prime[1010], phi[1010], sum[1010], m, t, n;

void euler(int n) {
	memset(v, 0, sizeof(v)); // 最小质因子
	m = 0; // 质数数量
	for (int i = 2; i <= n; i++) {
		if (v[i] == 0) { // i是质数
			v[i] = i, prime[++m] = i;
			phi[i] = i - 1;
		}
		// 给当前的数i乘上一个质因子
		for (int j = 1; j <= m; j++) {
			// i有比prime[j]更小的质因子，或者超出n的范围
			if (prime[j] > v[i] || prime[j] > n / i) break;
			// prime[j]是合数i*prime[j]的最小质因子
			v[i*prime[j]] = prime[j];
			phi[i*prime[j]] = phi[i] * (i%prime[j] ? prime[j]-1 : prime[j]);
		}
	}
}

int main() {
	euler(1000);
	for (int i = 2; i <= 1000; i++)
		sum[i] = sum[i - 1] + phi[i];
	cin >> t;
	for (int i = 1; i <= t; i++)
	{
		scanf("%d", &n);
		printf("%d %d %d\n", i, n, sum[n] * 2 + 3);
	}
}
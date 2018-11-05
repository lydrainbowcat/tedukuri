// 试除法判断n是否为质数
bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0) return false;
    return true;
}

// Eratosthenes筛法
void primes(int n) {
    memset(v, 0, sizeof(v)); // 合数标记
    for (int i = 2; i <= n; i++) {
        if (v[i]) continue;
        cout << i << endl; // i是质数
        for (int j = i; j <= n/i; j++) v[i*j] = 1;
    }
}

// 线性筛法
int v[MAX_N], prime[MAX_N];
void primes(int n) {
	memset(v, 0, sizeof(v)); // 最小质因子
	m = 0; // 质数数量
	for (int i = 2; i <= n; i++) {
		if (v[i] == 0) { // i是质数
			v[i] = i;
			prime[++m] = i;
		}
		// 给当前的数i乘上一个质因子
		for (int j = 1; j <= m; j++) {
			// i有比prime[j]更小的质因子，或者超出n的范围
			if (prime[j] > v[i] || prime[j] > n/i) break;
			// prime[j]是合数i*prime[j]的最小质因子
			v[i*prime[j]] = prime[j];
		}
	}
	for (int i = 1; i <= m; i++)
		cout << prime[i] << endl;
}

// 试除法分解质因数
void divide(int n) {
    m = 0;
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) { // i是质数
            p[++m] = i, c[m] = 0;
            while (n % i == 0) n /= i, c[m]++; // 除掉所有的i
        }
    }
    if (n > 1) // n是质数
        p[++m] = n, c[m] = 1;
    for (int i = 1; i <= m; i++)
        cout << p[i] << '^' << c[i] <<endl;
}
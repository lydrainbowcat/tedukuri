// 试除法求N的约数集合
int factor[1600], m = 0;
for (int i = 1; i*i <= n; i++) {
    if (n % i == 0) {
        factor[++m] = i;
        if (i != n/i) factor[++m] = n/i;
    }
}
for (int i = 1; i <= m; i++)
    cout << factor[i] <<endl;

// 倍数法求1~N每个数的约数集合
vector<int> factor[500010];
for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n/i; j++)
        factor[i*j].push_back(i);
for (int i = 1; i <= n; i++) {
    for (int j = 0; j < factor[i].size(); j++)
        printf("%d ", factor[i][j]);
    puts("");
}


// 欧几里得算法求最大公约数
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

// 计算欧拉函数
int phi(int n) {
    int ans = n;
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) { // i是质数
            ans = ans / i * (i-1);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) // n是质数
        ans = ans / n * (n-1);
    return ans;
}

// 欧拉函数快速递推：Eratosthenes筛法
void euler(int n) {
	for (int i = 2; i <= n; i++) phi[i] = i;
	for (int i = 2; i <= n; i++)
		if (phi[i] == i)
			for (int j = i; j <= n; j += i)
				phi[j] = phi[j] / i * (i - 1);
}

// 欧拉函数快速递推：线形筛法
int v[MAX_N], prime[MAX_N], phi[MAX_N];
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
	for (int i = 2; i <= n; i++)
		cout << i << ' ' << phi[i] << endl;
}

// 扩展欧几里得算法
int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) { x = 1, y = 0; return a; }
    int d = exgcd(b, a%b, x, y);
    int z = x; x = y; y = z - y * (a / b);
    return d;
}


// Baby Step, Giant Step
// 同余方程 a^x mod p = b，求x的最小非负整数解，无解返回-1
int baby_step_giant_step(int a, int b, int p) {
	map<int, int> hash;
	hash.clear();
    b %= p;
    int t = (int)sqrt(p) + 1;
    for (int j = 0; j < t; j++) {
    	int val = (long long)b * power(a, j, p) % p; // b*a^j
		hash[val] = j;
	}
    a = power(a, t, p); // a^t
    if (a == 0) return b == 0 ? 1 : -1;
    for (int i = 0; i <= t; i++) {
    	int val = power(a, i, p); // (a^t)^i
        int j = hash.find(val) == hash.end() ? -1 : hash[val];
        if (j >= 0 && i * t - j >= 0) return i * t - j;
    }
    return -1;
}

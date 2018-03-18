// Mobius函数
for (int i = 1; i <= n; i++) miu[i] = 1, v[i] = 0;
for (int i = 2; i <= n; i++) {
	if (v[i]) continue;
	miu[i] = -1;
	for (int j = 2 * i; j <= n; j += i) {
		v[j] = 1;
		if ((j / i) % i == 0) miu[j] = 0;
		else miu[j] *= -1;
	}
}

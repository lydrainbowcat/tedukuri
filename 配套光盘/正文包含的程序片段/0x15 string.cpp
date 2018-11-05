// KMP
next[1] = 0;
for (int i = 2, j = 0; i <= n; i++) {
	while (j > 0 && a[i] != a[j+1]) j = next[j];
	if (a[i] == a[j+1]) j++;
	next[i] = j;
}

for (int i = 1, j = 0; i <= m; i++) {
	while (j > 0 && (j == n || b[i] != a[j+1])) j = next[j];
	if (b[i] == a[j+1]) j++;
	f[i] = j;
	// if (f[i] == n)，此时就是A在B中的某一次出现
}


// 最小表示法
int n = strlen(s + 1);
for (int i = 1; i <= n; i++) s[n+i] = s[i];
int i = 1, j = 2, k;
while (i <= n && j <= n) {
	for (k = 0; k < n && s[i+k] == s[j+k]; k++);
	if (k == n) break; // s likes "aaaaa"
	if (s[i+k] > s[j+k]) {
		i = i + k + 1;
		if (i == j) i++;
	} else {
		j = j + k + 1;
		if (i == j) j++;
	}
}
ans = min(i, j);

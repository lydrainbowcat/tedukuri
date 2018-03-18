#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<string>
using namespace std;
long long f[300010], sumt[300010], sumc[300010];
int q[300010], n, s;
int main() {
	cin >> n >> s;
	for (int i = 1; i <= n; i++) {
		int t, c;
		scanf("%d%d", &t, &c);
		sumt[i] = sumt[i - 1] + t;
		sumc[i] = sumc[i - 1] + c;
	}
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	int l = 1, r = 1;
	q[1] = 0;
	for (int i = 1; i <= n; i++) {
		while (l < r && (f[q[l + 1]] - f[q[l]]) 
			<= (s + sumt[i]) * (sumc[q[l + 1]] - sumc[q[l]])) l++;
		f[i] = f[q[l]] - (s + sumt[i]) * sumc[q[l]]
			+ sumt[i] * sumc[i] + s * sumc[n];
		while (l < r && (f[q[r]] - f[q[r - 1]]) * (sumc[i] - sumc[q[r]])
			>= (f[i] - f[q[r]]) * (sumc[q[r]] - sumc[q[r - 1]])) r--;
		q[++r] = i;
	}
	cout << f[n] << endl;
}

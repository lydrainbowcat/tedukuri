#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<string>
using namespace std;
long long f[5010], sumt[5010], sumc[5010];
int n, s;
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
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < i; j++)
			f[i] = min(f[i], f[j] + sumt[i] * (sumc[i] - sumc[j]) + s*(sumc[n] - sumc[j]));
	cout << f[n] << endl;
}
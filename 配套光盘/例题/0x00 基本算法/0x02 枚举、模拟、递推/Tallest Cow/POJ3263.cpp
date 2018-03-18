#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
map<pair<int, int>, bool> existed;
int c[10010], d[10010];
int main()
{
	int n, p, h, m;
	cin >> n >> p >> h >> m;
	for (int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		if (a > b) swap(a, b);
		if (existed[make_pair(a, b)]) continue;
		d[a + 1]--, d[b]++;
		existed[make_pair(a, b)] = true;
	}
	for (int i = 1; i <= n; i++) {
		c[i] = c[i - 1] + d[i];
		printf("%d\n", h + c[i]);
	}
	cout << endl;
}
//Author:XuHt
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 15;
ll d[N], f[N];

int main() {
	int n = 12;
	memset(f, 0x3f, sizeof(f));
	d[1] = f[1] = 1;
	for (int i = 2; i <= n; i++) d[i] = 2 * d[i-1] + 1;
	for (int i = 2; i <= n; i++)
		for (int j = 1; j < i; j++)
			f[i] = min(f[i], 2 * f[j] + d[i-j]);
	for (int i = 1; i <= n; i++) cout << f[i] << endl;
	return 0;
}

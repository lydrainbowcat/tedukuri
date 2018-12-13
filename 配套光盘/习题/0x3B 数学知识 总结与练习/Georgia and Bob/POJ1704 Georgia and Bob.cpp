//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1006;
int a[N];

void Georgia_and_Bob() {
	int n, x = 0;
	cin >> n;
	a[0] = 0;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	for (int i = n; i > 0; i -= 2) x ^= a[i] - a[i-1] - 1;
	puts(x ? "Georgia will win" : "Bob will win");
}

int main() {
	int t;
	cin >> t;
	while (t--) Georgia_and_Bob();
	return 0;
}

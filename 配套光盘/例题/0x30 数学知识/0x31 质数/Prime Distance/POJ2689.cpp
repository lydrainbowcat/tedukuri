#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[100001], b[1000001];
bool v[1000001];
int n, m, i, j, t1, t2, x1, x2, y1, y2, l, r;

void prime()
{
	memset(v, 1, sizeof(v));
	for (i = 2; i <= 46340; i++)
		if (v[i])
		{
			a[++n] = i;
			for (j = 2; j <= 46340 / i; j++) v[i*j] = false;
		}
}

int main()
{
	prime();
	while (cin >> l >> r)
	{
		memset(v, 1, sizeof(v));
		if (l == 1) v[0] = false;
		for (i = 1; i <= n; i++)
			for (j = l / a[i]; j <= r / a[i]; j++)
				if (j>1) v[a[i] * j - l] = false;
		m = 0;
		for (i = l; i <= r; i++)
		{
			if (v[i - l]) b[++m] = i;
			if (i == r) break;
		}
		t1 = 2147483647; t2 = 0;
		for (i = 1; i<m; i++)
		{
			j = b[i + 1] - b[i];
			if (j<t1) { t1 = j; x1 = b[i]; y1 = b[i + 1]; }
			if (j>t2) { t2 = j; x2 = b[i]; y2 = b[i + 1]; }
		}
		if (!t2) cout << "There are no adjacent primes.\n";
		else cout << x1 << ',' << y1 << " are closest, " << x2 << ',' << y2 << " are most distant.\n";
	}
	return 0;
}
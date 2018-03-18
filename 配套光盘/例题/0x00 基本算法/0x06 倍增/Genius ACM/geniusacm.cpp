#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<set>
#include<queue>
#include<vector>
#include<string>
#include<cassert>
using namespace std;
int T, n, m, p, q, a[500010], b[500010], c[500010];
__int64 t;

template<typename T> inline void R(T &x) {
	char ch = getchar(); x = 0;
	for (; ch<'0'; ch = getchar());
	for (; ch >= '0'; ch = getchar()) x = x * 10 + ch - '0';
}
bool cmp(int x, int y) { return a[x] < a[y]; }

__int64 calc(int ed)
{
	__int64 ans = 0;
	for (int l = 1, r = p, i = m; l < r && i && ans <= t; i--, l++, r--)
	{
		while (l <= p && b[l] >= ed) l++;
		while (r && b[r] >= ed) r--;
		if (l < r) ans += (__int64)(a[b[r]] - a[b[l]])*(a[b[r]] - a[b[l]]);
	}
	return ans;
}

int batch(int st)
{
	b[p = q = 1] = st;
	int l = 1, r = 2;
	for (; st + l <= n; l = r, r = l << 1)
	{
		for (int i = st + l; i < min(st + r, n + 1); i++) b[++q] = i;
		sort(b + p + 1, b + q + 1, cmp);
		for (int i = 1, j = p + 1, k = 1; k <= q; k++)
			c[k] = b[j > q || i <= p && a[b[i]] < a[b[j]] ? i++ : j++];
		memcpy(b + 1, c + 1, q * 4);
		if (calc(st + (p = q)) > t) break;
	}
	if (st + l > n) return n + 1;
	r = min(r, p);
	while (l < r)
	{
		int mid = (l + r + 1) / 2;
		if (calc(st + mid) > t) r = mid - 1; else l = mid;
	}
	return st + l;
}

int main()
{
	freopen("geniusacm.in", "r", stdin);
	freopen("geniusacm.out", "w", stdout);
	cin >> T;
	while (T--)
	{
		R(n), R(m), R(t);
		for (int i = 1; i <= n; i++)
		{
			R(a[i]);
			assert(a[i] >= 0 && a[i] <= 1 << 20);
		}
		int ans = 0;
		for (int i = 1; i <= n; i = batch(i), ans++);
		cout << ans << endl;
	}
}

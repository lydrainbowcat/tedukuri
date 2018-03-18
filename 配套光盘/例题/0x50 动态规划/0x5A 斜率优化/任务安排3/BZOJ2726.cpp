#include<iostream>
#include<cstdio>
using namespace std;
long long sumt[300010], sumc[300010], f[300010];
int q[300010], n, s, l, r;

int binary_search(int i, int k)
{
	if (l == r) return q[l];
	int L = l, R = r;
	while (L < R)
	{
		int mid = (L + R) >> 1;
		if (f[q[mid + 1]] - f[q[mid]] <= k *
			(sumc[q[mid + 1]] - sumc[q[mid]])) L = mid + 1; 
		else R = mid;
	}
	return q[L];
}

int main()
{
	cin >> n >> s;
	for (int i = 1; i <= n; i++)
	{
		int t, c;
		scanf("%d%d", &t, &c);
		sumt[i] = sumt[i - 1] + t, sumc[i] = sumc[i - 1] + c;
	}
	l = r = 1, q[1] = 0;
	for (int i = 1; i <= n; i++)
	{
		int p = binary_search(i, s + sumt[i]);
		f[i] = f[p] - (s + sumt[i]) * sumc[p]
			+ sumt[i] * sumc[i] + s * sumc[n];
		while (l < r && (f[q[r]] - f[q[r - 1]]) * (sumc[i] - sumc[q[r]])
			>= (f[i] - f[q[r]]) * (sumc[q[r]] - sumc[q[r - 1]])) r--;
		q[++r] = i;
	}
	cout << f[n] << endl;
}
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int n;
long long ans;
vector<int> a[2];
int c[250010];

void merge(int k, int l, int mid, int r)
{
	int x = l, y = mid + 1;
	for (int i = l; i <= r; i++)
	{
		if (y>r || x <= mid&&a[k][x]<a[k][y])
			c[i] = a[k][x++];
		else ans += mid - x + 1, c[i] = a[k][y++];
	}
	for (int i = l; i <= r; i++) a[k][i] = c[i];
}

void mergesort(int k, int l, int r)
{
	if (l == r) return;
	int mid = (l + r) / 2;
	mergesort(k, l, mid);
	mergesort(k, mid + 1, r);
	merge(k, l, mid, r);
}

long long calc(int k)
{
	ans = 0;
	mergesort(k, 0, n*n - 1);
	return ans;
}

int main()
{
	while (cin >> n)
	{
		a[0].clear();
		a[1].clear();
		for (int i = 1; i <= n; i++)for (int j = 1; j <= n; j++)
		{
			int x; scanf("%d", &x); if (x) a[0].push_back(x);
		}
		for (int i = 1; i <= n; i++)for (int j = 1; j <= n; j++)
		{
			int x; scanf("%d", &x); if (x) a[1].push_back(x);
		}
		puts(a[0].size()&&(calc(1) - calc(0) & 1) ? "NIE" : "TAK");
	}
}

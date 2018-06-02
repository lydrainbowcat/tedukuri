#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<string>
using namespace std;
int f[31][5001], a[31][5001], b[31][5001], g[31], c[31], s[31], ans[31];

bool cmp(int a, int b)
{
	return g[a] > g[b];
}

void print(int n, int m)
{
	if (n == 0) return;
	print(a[n][m], b[n][m]);
	if (a[n][m] == n)
	{
		for (int i = 1; i <= n; i++) ans[c[i]]++;
	}
	else{
		for (int i = a[n][m] + 1; i <= n; i++) ans[c[i]] = 1;
	}
}

int main()
{
	//freopen("cookies.in", "r", stdin);
	//freopen("cookies.out", "w", stdout);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) scanf("%d", &g[i]), c[i] = i;
	sort(c + 1, c + n + 1, cmp);
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for (int i = 1; i <= n; i++)
	{
		s[i] = s[i - 1] + g[c[i]];
		for (int j = i; j <= m; j++)
		{
			f[i][j] = f[i][j - i];
			a[i][j] = i;
			b[i][j] = j - i;
			for (int k = 0; k < i; k++)
			{
				if (f[i][j] > f[k][j - (i - k)] + (s[i] - s[k])*k)
				{
					f[i][j] = f[k][j - (i - k)] + (s[i] - s[k])*k;
					a[i][j] = k;
					b[i][j] = j - (i - k);
				}
			}
		}
	}
	cout << f[n][m] << endl;
	print(n, m);
	for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
	cout << endl;
}

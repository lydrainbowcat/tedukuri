#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int SIZE = 200010;
int f[SIZE], next[SIZE], cnt[SIZE];
char a[SIZE], b[SIZE];
int n, m, q;

int main()
{
	cin >> n >> m >> q;
	scanf("%s", a + 1); // A[1..n]保存A串
	scanf("%s", b + 1); // B[1..n]保存B串

	for (int i = 2, j = 0; i <= m; i++) // 对B串自匹配，求next数组
	{
		while (j>0 && b[j + 1] != b[i]) j = next[j];
		if (b[j + 1] == b[i]) j++;
		next[i] = j;
	}

	for (int i = 1, j = 0; i <= n; i++) // A串与B串进行模式匹配
	{
		while (j>0 && (j == m || a[i] != b[j + 1])) j = next[j];
		if (a[i] == b[j + 1]) j++;
		f[i] = j;
	}

	for (int i = 1; i <= n; i++) cnt[f[i]]++;
	for (int i = n; i; i--) cnt[next[i]] += cnt[i];

	// 此时cnt[x]保存的是匹配长度>=x的位置个数

	for (int i = 1; i <= q; i++)
	{
		int x;
		scanf("%d", &x);
		printf("%d\n", cnt[x] - cnt[x + 1]);
	}
}

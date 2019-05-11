/*
	Author: Yuanhao Li, Peking University
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAX_N = 13;

int f[1 << MAX_N][MAX_N][MAX_N]; // f[i][j][k]: Current state i, Just passed l, j, k (1, 2, ..., l, j, k)
long long cnt[1 << MAX_N][MAX_N][MAX_N];

void DP(bool graph[MAX_N][MAX_N], int value[MAX_N], int n)
{
	if (n == 1)
	{
		printf("%d %d\n", value[0], 1);
		return;
	}

	memset(f, 0, sizeof(f));
	memset(cnt, 0, sizeof(cnt));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (graph[i][j] && i != j)
			{
				f[(1 << i) + (1 << j)][i][j] = value[i] + value[j] + value[i] * value[j];
				cnt[(1 << i) + (1 << j)][i][j] = 1;
			}
		}
	}

	for (int i = 1; i < 1 << n; i++)
	{
		for (int j = 0; j < n; j++) if (i >> j & 1)
			for (int k = 0; k < n; k++) if ((i >> k & 1) && graph[j][k])
				for (int l = 0; l < n; l++) if ((i >> l & 1) && graph[l][j] && (f[i ^ (1 << k)][l][j] > 0))
				{
					int newVal = f[i ^ (1 << k)][l][j] +
						value[k] +
						value[j] * value[k] +
						(int)(graph[l][k]) * value[l] * value[j] * value[k];
					if (newVal > f[i][j][k])
					{
						f[i][j][k] = newVal;
						cnt[i][j][k] = cnt[i ^ (1 << k)][l][j];
					}
					else if (newVal == f[i][j][k])
					{
						cnt[i][j][k] += cnt[i ^ (1 << k)][l][j];
					}
				}
	}

	int result = 0;
	long long duplicate = 0;
	for (int j = 0; j < n; j++)
		for (int k = 0; k < n; k++)
		{
			if (f[(1 << n) - 1][j][k] > result)
			{
				result = f[(1 << n) - 1][j][k];
				duplicate = cnt[(1 << n) - 1][j][k];
			}
			else if (f[(1 << n) - 1][j][k] == result)
			{
				duplicate += cnt[(1 << n) - 1][j][k];
			}
		}

	printf("%d %lld\n", result, duplicate / 2);
}

int main()
{
	int q;
	cin >> q;
	while (q--)
	{
		int n, m;
		cin >> n >> m;
		int value[MAX_N];
		bool graph[MAX_N][MAX_N];
		memset(value, 0, sizeof(value));
		memset(graph, false, sizeof(bool) * MAX_N * MAX_N);

		for (int i = 0; i < n; i++)
		{
			scanf("%d", &value[i]);
		}
		for (int i = 0; i < m; i++)
		{
			int a, b;
			scanf("%d %d", &a, &b);
			graph[a - 1][b - 1] = true;
			graph[b - 1][a - 1] = true;
		}

		DP(graph, value, n);
	}

	return 0;
}

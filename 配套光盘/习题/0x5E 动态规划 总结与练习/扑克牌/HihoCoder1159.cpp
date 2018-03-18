#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<iomanip>
#include<cmath>
using namespace std;
int T, n;
int a[20], c[5];
unsigned long long f[15][15][15][15][5];

void prework()
{
	f[0][0][0][0][1] = 1;
	for (int l = 0; l <= 13; l++)
	{
		for (int k = 0; k <= 13 - l; k++)
		{
			for (int j = 0; j <= 13 - k - l; j++)
			{
				for (int i = 0; i <= 13 - j - k - l; i++)
				{
					for (int p = 1; p <= 4; p++)
					{
						if (f[i][j][k][l][p] == 0) continue;
						if (p == 1)
						{
							f[i + 1][j][k][l][0] += f[i][j][k][l][p] * (i + 1);
							f[i + 1][j][k][l][1] += f[i][j][k][l][p] * (i + 1);
							f[i + 1][j][k][l][2] += f[i][j][k][l][p] * i;
							f[i + 1][j][k][l][3] += f[i][j][k][l][p] * (i + 1);
							f[i + 1][j][k][l][4] += f[i][j][k][l][p] * (i + 1);;
						}
						if (p == 2 && i > 0)
						{
							f[i - 1][j + 1][k][l][0] += f[i][j][k][l][p] * (j + 1) * 2;
							f[i - 1][j + 1][k][l][1] += f[i][j][k][l][p] * (j + 1) * 2;
							f[i - 1][j + 1][k][l][2] += f[i][j][k][l][p] * (j + 1) * 2;
							f[i - 1][j + 1][k][l][3] += f[i][j][k][l][p] * j * 2;
							f[i - 1][j + 1][k][l][4] += f[i][j][k][l][p] * (j + 1) * 2;
						}
						if (p == 3 && j > 0)
						{
							f[i][j - 1][k + 1][l][0] += f[i][j][k][l][p] * (k + 1) * 3;
							f[i][j - 1][k + 1][l][1] += f[i][j][k][l][p] * (k + 1) * 3;
							f[i][j - 1][k + 1][l][2] += f[i][j][k][l][p] * (k + 1) * 3;
							f[i][j - 1][k + 1][l][3] += f[i][j][k][l][p] * (k + 1) * 3;
							f[i][j - 1][k + 1][l][4] += f[i][j][k][l][p] * k * 3;
						}
						if (p == 4 && k > 0)
						{
							f[i][j][k - 1][l + 1][0] += f[i][j][k][l][p] * (l + 1) * 4;
							f[i][j][k - 1][l + 1][1] += f[i][j][k][l][p] * (l + 1) * 4;
							f[i][j][k - 1][l + 1][2] += f[i][j][k][l][p] * (l + 1) * 4;
							f[i][j][k - 1][l + 1][3] += f[i][j][k][l][p] * (l + 1) * 4;
							f[i][j][k - 1][l + 1][4] += f[i][j][k][l][p] * (l + 1) * 4;
						}
					}
				}
			}
		}
	}
}

int main()
{
	cin >> T;
	prework();
	for (int t = 1; t <= T; t++)
	{
		scanf("%d", &n);
		memset(a, 0, sizeof(a));
		for (int i = 1; i <= n; i++)
		{
			char s[5], val;
			scanf("%s", s);
			if (s[0] == 'T') val = 10;
			else if (s[0] == 'A') val = 1;
			else if (s[0] == 'J') val = 11;
			else if (s[0] == 'Q') val = 12;
			else if (s[0] == 'K') val = 13;
			else val = s[0] - '0';
			a[val]++;
		}
		memset(c, 0, sizeof(c));
		for (int i = 1; i <= 13; i++) c[a[i]]++;
		unsigned long long ans = 0;
		//cout << c[1] << ' ' << c[2] << ' ' << c[3] << ' ' << c[4] << endl;
		printf("Case #%d: %llu\n", t, f[c[1]][c[2]][c[3]][c[4]][0]);
	}
}
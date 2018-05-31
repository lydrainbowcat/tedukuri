#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int SIZE = 300010, INF = 1 << 30;
int a[SIZE], sa[SIZE], rk[SIZE], fir[SIZE], sec[SIZE], c[SIZE], h[SIZE];
char str[SIZE];
int n, p;

bool comp(int i, int j, int k)
{
	return sec[i] == sec[j] && sec[i + k] == sec[j + k];
}

void sufarr(int n)
{
	int i, p, l, m = 200;
	for (i = 0;i < m;i++) c[i] = 0;
	for (i = 0;i < n;i++) c[rk[i] = a[i]]++;
	for (i = 1;i < m;i++) c[i] += c[i - 1];
	for (i = n - 1;i >= 0;i--) sa[--c[a[i]]] = i;
	for (l = p = 1;p < n;l *= 2, m = p)
	{
		for (p = 0, i = n - l;i < n;i++) sec[p++] = i;
		for (i = 0;i < n;i++)
			if (sa[i] >= l) sec[p++] = sa[i] - l;
		for (i = 0;i < n;i++) fir[i] = rk[sec[i]];
		for (i = 0;i < m;i++) c[i] = 0;
		for (i = 0;i < n;i++) c[fir[i]]++;
		for (i = 1;i < m;i++) c[i] += c[i - 1];
		for (i = n - 1;i >= 0;i--) sa[--c[fir[i]]] = sec[i];
		memcpy(sec, rk, sizeof(rk));
		rk[sa[0]] = 0;
		for (i = p = 1;i < n;i++)
			rk[sa[i]] = comp(sa[i], sa[i - 1], l) ? p - 1 : p++;
	}
}

void calh()
{
	int i, j, k = 0;
	for (i = 1;i <= n;i++) rk[sa[i]] = i;
	for (i = 0;i < n;h[rk[i++]] = k)
		for (k ? k-- : 0, j = sa[rk[i] - 1];a[i + k] == a[j + k];k++);
}

int main()
{
	//freopen("savour.in", "r", stdin);
	//freopen("savour.out", "w", stdout);
	scanf("%s", str);
	n = strlen(str);
	for (int i = 0;i < n;i++) a[i] = str[i];
	a[n] = 0;
	sufarr(n + 1);
	calh();
	for(int i = 1; i <= n; i++) printf("%d ", sa[i]); puts("");
	for(int i = 1; i <= n; i++) printf("%d ", h[i]); puts("");
	//fclose(stdin);
	//fclose(stdout);
}

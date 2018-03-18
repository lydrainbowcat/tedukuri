#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
using namespace std;
int n;
int p[30010], dis[30010], size[30010];
int find(int k)
{
	if (p[k] != k)
	{
		int f = find(p[k]);
		dis[k] += dis[p[k]];
		p[k] = f;
	}
	return p[k];
}
int main()
{
	for (int i = 1; i <= 30000; i++)
	{
		size[i] = 1;
		p[i] = i;
	}
	scanf("%d", &n);
	while (n--)
	{
		char s[2];
		int x, y;
		scanf("%s", s);
		scanf("%d%d", &x, &y);
		int fi = find(x), fj = find(y);
		if (s[0] == 'M')
		{
			p[fi] = fj;
			dis[fi] = size[fj];
			size[fj] += size[fi];
		}
		else
		{
			if (fi != fj)  printf("-1\n");
			else printf("%d\n", abs(dis[x] - dis[y]) - 1);
		}
	}
	return 0;
}
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n, m, t;
const int size = 300010;
int a[size + 1];
int i, j, k, sa[size + 1], rk[size + 1], height[size + 1], l, p[size + 1], mid, tmp;
char str[size];

void sort_str(int l, int r)  //对字符串进行排序，这里用的是快速排序，最好用基数排序
{
	int i, j;
	i = l; j = r;
	mid = sa[(l + r) >> 1];
	while (i <= j)
	{
		while (p[sa[i]]<p[mid]) i++;
		while (p[sa[j]]>p[mid]) j--;
		if (i <= j)
		{
			tmp = sa[i]; sa[i] = sa[j]; sa[j] = tmp;
			i++; j--;
		}
	}
	if (i<r) sort_str(i, r);
	if (l<j) sort_str(l, j);
}
void calc1(int i, int j)  //计算rk信息
{
	sort_str(i, j - 1);
	rk[sa[i]] = i;
	for (i++; i<j; i++)
	if (p[sa[i]] == p[sa[i - 1]]) rk[sa[i]] = rk[sa[i - 1]];
	else rk[sa[i]] = i;
}
void calc()
{
	for (i = 0; i < n; i++)
	{
		sa[i] = i;
		p[i] = a[i];
	} //初始化
	calc1(0, n);//第一次排序
	l = 1;//l为倍增长度
	while (l < n)
	{
		for (i = 0; i + l < n; i++) p[i] = rk[i + l];  //更新pl
		for (i; i < n; i++) p[i] = -1;
		for (i = 0; i < n; i = j)//根据l进行排序
		{
			j = i;
			while (rk[sa[i]] == rk[sa[j]] && j<n) j++;
			calc1(i, j);
		}
		l += l; //倍增l
	}
	//求height数组
	for (i = 0; i < n; i++)
	if (j = rk[i])
	{
		if (i) l = height[rk[i - 1]] - 1;
		else l = 0;
		if (l < 0) l = 0;  //l为下界
		while (a[i + l] == a[sa[j - 1] + l]) l++;
		height[j] = l;  //更新height数组
	}
	else height[0] = 0;
}

int main()
{
	scanf("%s", str);
	n = strlen(str);
	for (int i = 0; i < n; i++)
	{
		a[i] = str[i] - 'a' + 1;
		m = max(m, a[i]);
	}
	m++;
	calc();
	for(int i = 0; i < n; i++) printf("%d ", sa[i]); puts("");
	for(int i = 0; i < n; i++) printf("%d ", height[i]); puts("");
	return 0;
}

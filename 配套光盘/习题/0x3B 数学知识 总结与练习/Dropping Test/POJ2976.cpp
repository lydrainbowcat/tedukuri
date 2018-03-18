/*
    Author: wccy
    本程序仅供参考
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;
double a[1010],b[1010],c[1010];
int n,k;
inline double check(double mid)
{
	for(int i = 1; i <= n; i++)
		c[i] = a[i] - mid*b[i];
	sort(c+1,c+n+1);
	double res(0);
	for(int i = n;i > k; i--)
		res += c[i];
	return res;
}
int main()
{
	while(scanf("%d%d",&n,&k),n+k)
	{
		for(int i = 1; i <= n; i++)
			scanf("%lf",&a[i]);
		for(int i = 1; i <= n; i++)
			scanf("%lf",&b[i]);
		double l = 0,r = 1;
		while(l + 1e-8 < r)
		{
			double mid = (l+r)/2.0;
			if(check(mid) > 0) l = mid;
			else r = mid;
		}
		printf("%.0f\n",100*r);
	}
	return 0;
}
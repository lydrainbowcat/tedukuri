/*
	Author: wccy
	本程序仅供参考 
*/
#include <stdio.h>
int a[500010],b[500010],n;
long long ans(0);
inline void merge(int l1, int r1,int l2,int r2)
{
	int tot(0);
	while(l1 <= r1 && l2 <= r2)
	{
		if(a[l2] < a[l1]) b[++tot] = a[l2++],ans += r1 - l1 + 1;
		else b[++tot] = a[l1++];
	}
	while(l1 <= r1) b[++tot] = a[l1++];
	while(l2 <= r2) b[++tot] = a[l2++];
	for(int i = tot,j = r2;i  >= 1; i--, j--)
	a[j] = b[i];
}
inline void mergesort(int l, int r)
{
	if(l < r)
	{
		int mid = (l+r)>>1;
		mergesort(l,mid);
		mergesort(mid+1,r);
		merge(l,mid,mid+1,r); 
	}
}
int main() 
{
	while(scanf("%d",&n),n)
	{
		ans = 0;
		for(int i = 1; i <= n; i++) 
			scanf("%d",a+i);
		mergesort(1,n);
		printf("%lld\n",ans);
	}
	return 0;
}

// Author: SJZEZ wccy
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

const int T = 1000003;

int n,k,q[T],h,t,a[T],aa[T],bb[T];

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	h=1,t=2;
	for(int i=1;i<=n;i++)
	{
		while(h<=t && q[h]<i-k+1)	h++;
		while(h<=t && a[q[t]]>a[i])	t--;
		q[++t]=i;
		aa[i]=a[q[h]];
	}
	memset(q,0,sizeof(q)),h=1,t=2;
	for(int i=1;i<=n;i++)
	{
		while(h<=t && q[h]<i-k+1)	h++;
		while(h<=t && a[q[t]]<a[i])	t--;
		q[++t]=i;
		bb[i]=a[q[h]];
	}
	for(int i=k;i<=n;i++)
		printf("%d ",aa[i]);
	printf("\n");
	for(int i=k;i<=n;i++)
		printf("%d ",bb[i]);
	return 0;
}
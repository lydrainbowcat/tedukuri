#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;
int a[1000010];

int main()
{
	freopen("data.in","w",stdout);
	srand(time(0));
	for(int i=1;i<=10;i++)
	{
		int n=i*50-1;
		cout<<n<<endl;
		for(int i=0;i<n*n;i++) a[i]=i;
		random_shuffle(a,a+n*n);
		for(int i=0;i<n*n;i++)
		{
			printf("%d ",a[i]);
			if(i%n==n-1) puts("");
		}
		random_shuffle(a,a+n*n);
		for(int i=0;i<n*n;i++)
		{
			printf("%d ",a[i]);
			if(i%n==n-1) puts("");
		}
	}
}

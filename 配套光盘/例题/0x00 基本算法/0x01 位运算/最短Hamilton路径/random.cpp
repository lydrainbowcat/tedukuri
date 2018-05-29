#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;
int a[20][20];
int main() {
	freopen("ham.in","w",stdout);
	int n=20;
	cout<<n<<endl;
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			a[i][j]=a[j][i]=rand()+1;
	for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
	for(int i=0;i<n;i++) {
		for(int j=0;j<n-1;j++) printf("%d ", a[i][j]);
		printf("%d\n",a[i][n-1]);
	}
}


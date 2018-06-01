#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;
int n,m,a[30010];
int main() {
	srand((unsigned)time(0));
	cin>>n>>m;
	cout<<n<<' '<<n<<endl;
	for(int i=1;i<=n;i++) a[i]=i;
	random_shuffle(a+1,a+n+1);
	for(int i=1;i<n;i++) {
		printf("%d %d\n", a[i], a[i+1]);
	}
	cout<<a[1]<<' '<<a[n]<<endl;
}

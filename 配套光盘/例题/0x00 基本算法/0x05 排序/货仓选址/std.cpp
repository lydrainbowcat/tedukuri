#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int n, a[100010];
long long ans;
int main() {
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) ans+=abs(a[n/2+1]-a[i]);
	cout<<ans<<endl;
}

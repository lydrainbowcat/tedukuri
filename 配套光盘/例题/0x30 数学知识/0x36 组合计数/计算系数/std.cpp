#include<bits/stdc++.h>
using namespace std;
const int N=1010,mod=10007;
typedef long long ll;
int c[N][N];
int main() {
	int a,b,k,n,m;
	scanf("%d%d%d%d%d",&a,&b,&k,&n,&m);
	c[0][0]=1;
	for(int i=1;i<=k;i++) for(int j=0;j<=i;j++) {
		c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
	ll ans=1;
	for(int i=1;i<=n;i++) ans=(ans*ll(a))%mod;
	for(int i=1;i<=m;i++) ans=(ans*ll(b))%mod;
	printf("%lld\n",(ans*ll(c[k][n]))%mod);
	return 0;
}
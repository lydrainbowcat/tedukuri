//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 1000006;
int n;
ll a[N], k = 0;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
    	scanf("%lld", &a[i]);
        k += a[i];
    }
    k /= n;
    a[0] = 0;
    for (int i = 1; i <= n; i++) a[i] = a[i] - k + a[i-1];
    sort(a + 1, a + n + 1);
    ll ans = 0;
    for (int i = 1; i <= n / 2; i++) ans += a[n+1-i] - a[i];
    cout << ans << endl;
    return 0;
}

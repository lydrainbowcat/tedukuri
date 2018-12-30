#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAX_M = 10000;
int f[MAX_M+1];
int n, m, a[MAX_M+1];
int main() {
	cin >> n >> m;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    memset(f, 0, sizeof(f));
    f[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= a[i]; j--)
            f[j] += f[j - a[i]];
    cout << f[m] <<endl;
}
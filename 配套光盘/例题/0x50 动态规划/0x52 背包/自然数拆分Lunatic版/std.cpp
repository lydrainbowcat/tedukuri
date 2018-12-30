#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAX_N = 10000;
unsigned int f[MAX_N + 1], n;
int main() {
    cin >> n;
    memset(f, 0, sizeof(f));
    f[0] = 1;
	for (int i = 1; i <= n; i++)
	    for (int j = i; j <= n; j++)
	        f[j] = (f[j] + f[j - i]) % 2147483648u;
	cout << (f[n] > 0 ? f[n] - 1 : 2147483647) <<endl;
}
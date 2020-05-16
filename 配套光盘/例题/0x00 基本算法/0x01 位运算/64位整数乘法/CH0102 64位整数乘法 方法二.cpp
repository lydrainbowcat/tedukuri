#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long a, b, p;

typedef unsigned long long ull;
ull mul(ull a, ull b, ull p) {
	a %= p, b %= p;  // 当a,b一定在0~p之间时，此行不必要
	ull c = (long double)a * b / p;
	ull x = a * b, y = c * p;
	long long ans = (long long)(x % p) - (long long)(y % p);
	if (ans < 0) ans += p;
	return ans;
}

int main() {
	cin >> a >> b >> p;
	cout << mul(a, b, p) << endl;
}
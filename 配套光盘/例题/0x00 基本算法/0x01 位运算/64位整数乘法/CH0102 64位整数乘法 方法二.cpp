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
	ull ans1 = a * b, ans2 = c * p;
	if (ans1 < ans2) return ans2 - ans1;
	return ans1 - ans2;
}

int main() {
	cin >> a >> b >> p;
	cout << mul(a, b, p) << endl;
}
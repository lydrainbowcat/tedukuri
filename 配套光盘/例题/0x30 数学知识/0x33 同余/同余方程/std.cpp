#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long a, b, x, y;
long long exgcd(long long a, long long b, long long &x, long long &y) {
	if (!b) { x=1, y=0; return a; }
	long long d = exgcd(b, a%b, x, y);
	long long z = x; x = y; y = z - y*(a/b);
    return d;
}
int main() {
	cin >> a >> b;
	exgcd(a, b, x, y);
	cout << (x % b + b) % b << endl;
}
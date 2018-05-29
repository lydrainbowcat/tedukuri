#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a, b, p;

int power(int a, int b, int p) { // calculate (a ^ b) mod p
	int ans = 1 % p;
	for (; b; b >>= 1) {
		if (b & 1) ans = (long long)ans * a % p;
		a = (long long)a * a % p;
	}
	return ans;
}

int main() {
	cin >> a >> b >> p;
	cout << power(a, b, p) << endl;
}

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a, b, p;

int power(int a, int b, int p) { // calculate (a ^ b) mod p
	int ans = 1 % p;	//因为p可能为1，此时ans==0，其实我认为直接用“if(p==1) return 0;”更好，不用计算下面的
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

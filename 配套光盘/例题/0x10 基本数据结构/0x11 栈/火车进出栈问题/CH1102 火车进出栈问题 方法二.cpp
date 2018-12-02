//Author:XuHt
#include <iostream>
#define ll long long
using namespace std;
const int N = 60006;
int n;
ll s[N];

int main() {
	cin >> n;
	s[0] = s[1] = 1;
	for (int i = 2; i <= n; i++) {
		s[i] = 0;
		for (int j = 1; j <= i; j++)
			s[i] += s[j-1] * s[i-j];
	}
	cout << s[n] << endl;
	return 0;
}

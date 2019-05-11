//Author:XuHt
#include <iostream>
using namespace std;

int gcd(int i, int j) {
	return j ? gcd(j, i % j) : i;
}

bool pd(int i, int j) {
	return gcd(i, j) == 1;
}

int main() {
	int n;
	cin >> n;
	while (n--) {
		int a0, a1, b0, b1;
		cin >> a0 >> a1 >> b0 >> b1;
		if (b1 % a1) {
			cout << "0" << endl;
			continue;
		}
		int ans = 0, k = b1 / a1;
		for (int i = 1; i * i <= k; i++)
			if (k % i == 0) {
				if (pd(i, a0 / a1) && pd(k / i, b1 / b0)) ans++;
				if (i * i != k && pd(k / i, a0 / a1) && pd(i, b1 / b0)) ans++;
			}
		cout << ans << endl;
	}
	return 0;
}

//Author:XuHt
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;
const int N = 100006, P = 99991;
int n, a[6], b[6];
struct S {
	int s[6];
};
vector<S> snow[N];

int H() {
	int s = 0, k = 1;
	for (int i = 0; i < 6; i++) {
		(s += a[i]) %= P;
		k = (ll)k * a[i] % P;
	}
	return (s + k) % P;
}

bool pd() {
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++) {
			bool v = 1;
			for (int k = 0; k < 6; k++)
				if (a[(i+k)%6] != b[(j+k%6)]) {
					v = 0;
					break;
				}
			if (v) return 1;
			v = 1;
			for (int k = 0; k < 6; k++)
				if (a[(i+k)%6] != b[(j-k+6)%6]) {
					v = 0;
					break;
				}
			if (v) return 1;

		}
	return 0;
}

bool insert() {
	int h = H();
	for (unsigned int i = 0; i < snow[h].size(); i++) {
		memcpy(b, snow[h][i].s, sizeof(b));
		if (pd()) return 1;
	}
	S s;
	memcpy(s.s, a, sizeof(s.s));
	snow[h].push_back(s);
	return 0;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 6; j++) scanf("%d", &a[j]);
		if (insert()) {
			cout << "Twin snowflakes found." << endl;
			return 0;
		}
	}
	cout << "No two snowflakes are alike." << endl;
	return 0;
}

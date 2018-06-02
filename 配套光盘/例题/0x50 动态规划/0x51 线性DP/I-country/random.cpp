#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;
int n, m, k;
int main() {
	srand((unsigned)time(0));
	cin >> n >> m >> k;
	cout << n << ' ' << m << ' ' << k << endl;
	for (int i = 1; i <= n; i++) {
		for (int j =1; j <= m; j++)
			printf("%d ", rand() % 1001);
		puts("");
	}
}

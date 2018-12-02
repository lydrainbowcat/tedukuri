//Author:XuHt
#include <iostream>
#define ll long long
using namespace std;
const int N = 1006;
ll f[N][N];

int main() {
	int n;
	cin >> n;
	f[0][0] = 1;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n - i; j++)
			if (i || j) f[i][j] = (i ? f[i-1][j+1] : 0) + (j ? f[i][j-1] : 0);
	cout << f[n][0] << endl;
	return 0;
}

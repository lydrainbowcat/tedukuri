#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;
int n, m, t;
bool a[210][210];
int main() {
	srand((unsigned)time(0));
	n = rand()%100 + 101;
	m = rand()%100 + 101;
	for (int i = 1; i <= (n + m); i++) a[rand()%n+1][rand()%m+1] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (!a[i][j]) t++;
	cout << n << ' ' << m << ' ' << t << endl;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (!a[i][j])
				printf("%d %d\n", i, j);
}

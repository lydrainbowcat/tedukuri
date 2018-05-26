#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<set>
#include<queue>
#include<vector>
#include<cstdlib>
#include<ctime>
using namespace std;
int main()
{
	freopen("geniusacm.in","w",stdout);
	srand(time(0));
	int T = 12;
	cout << T << endl;
	while (T--)
	{
		int n = 100000, m = rand() * rand() % n + 1;
		cout << n << ' ' << m << ' ' << rand() * rand() << endl;
		while (n--) printf("%d ", rand());
		cout << endl;
	}
}

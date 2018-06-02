#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;
int n;
int main() {
	srand((unsigned)time(0));
	cin >> n;
	cout << n << endl;
	for (int i = 1; i <= n; i++) printf("%d ", rand()*rand()%(6*n)+1);
}

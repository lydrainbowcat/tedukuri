#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<string>
#include<ctime>
using namespace std;
string a[60];
int t, p[60];

int main() {
	srand((unsigned)time(0));
	for(int i = 1; i <= 13; i++) {
		char ch = '0' + i;
		if (i == 1) ch = 'A';
		if (i == 10) ch = 'T';
		if (i == 11) ch = 'J';
		if (i == 12) ch = 'Q';
		if (i == 13) ch = 'K';
		string s = "";
		s += ch;
		a[++t] = s + 'S';
		a[++t] = s + 'H';
		a[++t] = s + 'D';
		a[++t] = s + 'C';
	}
	cout << 20000 << endl;
	for(int T = 1; T <= 20000; T++) {
		int n = rand() % 52 + 1;
		cout << n;
		for (int i = 1; i <= t; i++) p[i] = i;
		random_shuffle(p + 1, p + t + 1);
		for (int i = 1; i <= n; i++) cout << " " << a[p[i]];
		cout << endl;
	}
}

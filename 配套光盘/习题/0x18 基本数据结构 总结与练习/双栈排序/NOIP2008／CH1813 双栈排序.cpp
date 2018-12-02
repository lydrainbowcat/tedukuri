//Author:XuHt
#include <stack>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1006, INF = 0x7fffffff;
bool v[N][N];
int clr[N], a[N], s[N], n;
bool flag;

void get(int i, int c) {
	clr[i] = c;
	for (int j = 0; j < n; j++)
		if (v[i][j]) {
			if (clr[j] == c) flag = 0;
			if (!clr[j]) get(j, 3-c);
		}
}

void szpx() {
	cin >> n;
	flag = 1;
	memset(clr, 0, sizeof(clr));
	memset(a, 0, sizeof(a));
	memset(s, 0, sizeof(s));
	memset(v, 0, sizeof(v));
	for (int i = 0; i < n; i++) cin >> a[i];
	s[n] = INF;
	for (int i = n - 1; i >= 0; i--) {
		s[i] = a[i];
		if (s[i+1] < s[i]) s[i] = s[i+1];
	}
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (a[i] < a[j] && s[j+1] < a[i])
				v[i][j] = v[j][i] = 1;
	for (int i = 0; i < n; i++) if (!clr[i]) get(i, 1);
	if (!flag) {
		cout << "0" << endl;
		return;
	}
	stack<int> st1, st2;
	int cnt = 0, num = 1;
	for (int i = 0; i < n; i++) {
		if (clr[i] == 1) {
			st1.push(a[i]);
			cnt++;
			cout << "a";
			if (cnt < n * 2) cout << " ";
		} else {
			st2.push(a[i]);
			cnt++;
			cout << "c";
			if (cnt < n * 2) cout << " ";
		}
		while ((!st1.empty() && st1.top() == num) || (!st2.empty() && st2.top() == num))
			if (!st1.empty() && st1.top() == num) {
				st1.pop();
				cnt++;
				num++;
				cout << "b";
				if (cnt < n * 2) cout << " ";
			} else {
				st2.pop();
				cnt++;
				num++;
				cout << "d";
				if (cnt < n * 2) cout << " ";
			}
	}
	cout << endl;
}

int main() {
	int t;
	cin >> t;
	while (t--) szpx();
	return 0;
}

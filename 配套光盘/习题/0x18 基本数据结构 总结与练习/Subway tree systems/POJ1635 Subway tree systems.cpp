//Author:XuHt
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
string s1, s2;

string w(string s) {
	vector<string> a;
	string f = "";
	int num = 0, t = 0;
	for (unsigned int i = 0; i < s.size(); i++) {
		if (s[i] == '0') num++;
		else num--;
		if (!num) {
			if (i - 1 > t + 1) a.push_back("0" + w(s.substr(t + 1, i - 1 - t)) + "1");
			else a.push_back("01");
			t = i + 1;
		}
	}
	sort(a.begin(), a.end());
	for (unsigned int i = 0; i < a.size(); i++) f += a[i];
	return f;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		cin >> s1 >> s2;
		cout << (w(s1) == w(s2) ? "same" : "different") << endl;
	}
	return 0;
}

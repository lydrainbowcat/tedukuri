//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 10006, L = 12;
int trie[N*L][10], tot;
bool ed[N*L];
char s[N][L];

bool Phone_List() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) scanf("%s", s[i]);
	memset(trie, 0, sizeof(trie));
	memset(ed, 0, sizeof(ed));
	tot = 1;
	for (int i = 0; i < n; i++) {
		int len = strlen(s[i]), p = 1;
		for (int j = 0; j < len; j++) {
			int a = s[i][j] - '0';
			if (!trie[p][a]) trie[p][a] = ++tot;
			p = trie[p][a];
			if (ed[p]) return 1;
		}
		for (int i = 0; i < 10; i++)
			if (trie[p][i]) return 1;
		ed[p] = 1;
	}
	return 0;
}

int main() {
	int t;
	cin >> t;
	while (t--) cout << (Phone_List() ? "NO" : "YES") << endl;
	return 0;
}

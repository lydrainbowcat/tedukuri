// 假设字符串由小写字母构成
int trie[SIZE][26], tot = 1;

// Trie的插入
void insert(char* str) {
	int len = strlen(str), p = 1;
	for (int k = 0; k < len; k++) {
		int ch = str[k]-'a';
		if (trie[p][ch] == 0) trie[p][ch] = ++tot;
		p = trie[p][ch];
	}
	end[p] = true;
}

// Trie的检索
bool search(char* str) {
	int len = strlen(str), p = 1;
	for (int k = 0; k < len; k++) {
		p = trie[p][str[k]-'a'];
		if (p == 0) return false;
	}
	return end[p];
}

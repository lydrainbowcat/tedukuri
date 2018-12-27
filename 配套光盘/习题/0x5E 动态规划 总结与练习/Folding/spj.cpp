#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
//一些定义
const int ACCEPT = 0;
const int WRONG_ANSWER = 1;
//fstd 标准输出 fout 选手输出 fin 标准输入
FILE *fstd, *fout, *fin;
char a[205], b[205], c[205];
string d;

string unfold(int l, int r) {
	if (l > r) return "";
	string res = "";
	if (b[l] >= 'A' && b[l] <= 'Z') {
		res.push_back(b[l]);
		res.append(unfold(l + 1, r));
		return res;
	}
	if (b[l] >= '0' && b[l] <= '9') {
		int cnt = 0;
		for (; l <= r && b[l] >= '0' && b[l] <= '9'; l++) cnt = cnt * 10 + b[l] - '0';
		if (r - l < 2) exit(WRONG_ANSWER);
		if (cnt < 1) exit(WRONG_ANSWER);
		if (b[l] != '(') exit(WRONG_ANSWER);
		int mid = l + 1, k = 1;
		for (; mid <= r && k; mid++) {
			if (b[mid] == '(') k++;
			if (b[mid] == ')') k--;
		}
		if (mid - l < 3 || k) exit(WRONG_ANSWER);
		string sub = unfold(l + 1, mid - 2);
		while (cnt--) res.append(sub);
		res.append(unfold(mid, r));
		return res;
	}
	exit(WRONG_ANSWER);
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		printf("参数不足 %d", argc);
		return -1;
	}
	if (NULL == (fstd = fopen(argv[1], "r"))) {
		return -1;
	}
	if (NULL == (fout = fopen(argv[2], "r"))) {
		return -1;
	}
	if (NULL == (fin = fopen(argv[3], "r"))) {
		return -1;
	}
	fscanf(fin, "%s", a + 1);
	fscanf(fout, "%s", b + 1);
	fscanf(fstd, "%s", c + 1);
	if (strlen(b + 1) != strlen(c + 1)) return WRONG_ANSWER;
	d = unfold(1, strlen(b + 1));
	if (string(a + 1) != d) return WRONG_ANSWER;
	return ACCEPT;
}
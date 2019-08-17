#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include<iomanip>
#include <cmath>
#include<fstream>
using namespace std;
int a[3][3];
int main() {
	ifstream fout("output");
	ifstream fin("user_output");
	string user_ret;
	string we_ret;
	fin >> user_ret;
	fout >> we_ret;
	if (user_ret.compare(we_ret) == 0) {
		return 0;
	}
	if (user_ret.size() != we_ret.size()) {
		return 1;
	}
	int x,y;
	for (int i = 0; i<3; i++)
		for (int j = 0; j<3; j++) {
			char str[2];
			scanf("%s", str);
			if (str[0] == 'x') a[i][j] = 9,x=i,y=j;
			else a[i][j] = str[0] - '0';
		}
	for (int i = 0; i < user_ret.size(); i++) {
		if (user_ret[i] == 'u') {
			if (x > 0) {
				swap(a[x][y], a[x - 1][y]);
				x--;
			}
			else {
				return 1;
			}
		}
		else if (user_ret[i] == 'd') {
			if (x < 2) {
				swap(a[x][y], a[x + 1][y]);
				x++;
			}
			else {
				return 1;
			}
		}
		else if (user_ret[i] == 'l') {
			if (y > 0) {
				swap(a[x][y], a[x][y - 1]);
				y--;
			}
			else {
				return 1;
			}
		}
		else if (user_ret[i] == 'r') {
			if (y < 2) {
				swap(a[x][y], a[x][y + 1]);
				y++;
			}
			else {
				return 1;
			}
		}
		else {
			return 1;
		}
	}
	for (int i = 0;i<3;i++)
		for (int j = 0; j < 3; j++) {
			if (a[i][j] != i * 3 + j + 1) {
				return 1;
			}
		}
	return 0;
}
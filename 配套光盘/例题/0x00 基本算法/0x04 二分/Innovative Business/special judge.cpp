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
class PrepareForSolution {
public:

	void trimLeftTrailingSpaces(string &input) {
		input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
			return !isspace(ch);
		}));
	}

	void trimRightTrailingSpaces(string &input) {
		input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
			return !isspace(ch);
		}).base(), input.end());
	}

	void trim(string &input) {
		trimLeftTrailingSpaces(input);
		trimRightTrailingSpaces(input);
	}


	int stringToInteger(string input) {
		trim(input);
		return stoi(input);
	}
	vector<int> stringToIntegerArray(string input) {
		vector<int> output;
		trim(input);
		input = input.substr(1, input.length() - 2);
		trim(input);
		stringstream ss(input);
		string item;
		char delim = ',';
		while (getline(ss, item, delim)) {
			output.push_back(stringToInteger(item));
		}
		return output;
	}

	vector<vector <int>> stringTo2dIntegerArray(string input) {
		vector<vector<int>> output;
		trim(input);
		input = input.substr(1, input.length() - 2);
		trim(input);
		size_t i = 0;
		while (i < input.size()) {
			size_t j = i;
			while (j < input.size() && input[j] != ']') j++;
			j++;
			output.push_back(stringToIntegerArray(input.substr(i, j - i)));
			while (j < input.size() && input[j] != ',') j++;
			i = j + 1;
		}
		return output;
	}

};

int main() {
	auto prepare = PrepareForSolution();
	string line;
	getline(cin, line);
	auto nums = prepare.stringTo2dIntegerArray(line);
	int N = nums.size();
	ifstream fin("user_output");
	string user_ret;
	getline(fin, user_ret);
	vector<int> ans = prepare.stringToIntegerArray(user_ret);
	vector<int> ans2 = prepare.stringToIntegerArray(user_ret);
	sort(ans2.begin(), ans2.end());
	if (ans2.size() != N)
		return 1;
	for (int i = 0; i < N; i++) 
		if (ans2[i] != i + 1)
			return 1;
	for (int i = 0; i < N - 1; i++)
		if (!nums[ans[i] - 1][ans[i + 1] - 1])
			return 1;
	return 0;
}

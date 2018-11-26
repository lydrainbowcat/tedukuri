#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
vector<int> chosen;
int stack[100010], top = 0, address = 0, n, m;
void call(int x, int ret_addr) { // 模拟计算机汇编指令call
	int old_top = top;
	stack[++top] = x; // 参数x
	stack[++top] = ret_addr; // 返回地址标号
	stack[++top] = old_top; // 在栈顶记录以前的top值
}
int ret() { // 模拟计算机汇编指令ret
	int ret_addr = stack[top - 1];
	top = stack[top]; // 恢复以前的top值
	return ret_addr;
}

int main() {
	cin >> n >> m;
	call(1, 0); // calc(1)
	while (top) {
		int x = stack[top - 2]; // 获取参数
		switch (address) {
		case 0:
			if (chosen.size()>m || chosen.size()+(n-x+1)<m) {
				address = ret(); // return
				continue;
			}
			if (x == n + 1) {
				for (int i = 0; i < chosen.size(); i++)
					printf("%d ", chosen[i]);
				puts("");
				address = ret(); // return
				continue;
			}
			chosen.push_back(x);
			call(x+1, 1); // 相当于calc(x+1)，返回后会从case 1继续
			address = 0;
			continue; // 回到while循环开头，相当于开始新的递归
		case 1:
			chosen.pop_back();
			call(x+1, 2); // 相当于calc(x+1)，返回后会从case 2继续
			address = 0;
			continue; // 回到while循环开头，相当于开始新的递归
		case 2:
			address = ret(); // 相当于原calc函数结尾，执行return
		}
	}
}


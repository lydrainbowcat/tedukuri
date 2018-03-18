// 递归实现指数型枚举
vector<int> chosen;
void calc(int x) {
	if (x == n + 1) {
		for (int i = 0; i < chosen.size(); i++)
			printf("%d ", chosen[i]);
		puts("");
		return;
	}
	calc(x + 1);
	chosen.push_back(x);
	calc(x + 1);
	chosen.pop_back();
}

// 递归实现组合型枚举
vector<int> chosen; 
void calc(int x) {
	if (chosen.size() > m || chosen.size() + (n - x + 1) < m) return;
	if (x == n + 1) {
		for (int i = 0; i < chosen.size(); i++)
			printf("%d ", chosen[i]);
		puts("");
		return;
	}
	calc(x + 1);
	chosen.push_back(x);
	calc(x + 1);
	chosen.pop_back();
}

// 递归实现排列型枚举
int order[20];
bool chosen[20];
void calc(int k) {
	if (k == n + 1) {
		for (int i = 1; i <= n; i++)
			printf("%d ", order[i]);
		puts("");
		return;
	}
	for (int i = 1; i <= n; i++) {
		if (chosen[i]) continue;
		order[k] = i;
		chosen[i] = 1;
		calc(k + 1);
		chosen[i] = 0;
		order[k] = 0;
	}
}


// 模拟机器实现，把组合型枚举改为非递归
vector<int> chosen;
int stack[100010], top = 0, address = 0;

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
	int n, m;
	cin >> n >> m;
	call(1, 0); // calc(1)
	while (top) {
		int x = stack[top - 2]; // 获取参数
		switch (address) {
		case 0:
			if (chosen.size() > m || chosen.size() + (n - x + 1) < m) {
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
			call(x + 1, 1); // 相当于calc(x + 1)，返回后会从case 1继续执行
			address = 0;
			continue; // 回到while循环开头，相当于开始新的递归
		case 1:
			chosen.push_back(x);
			call(x + 1, 2); // 相当于calc(x + 1)，返回后会从case 2继续执行
			address = 0;
			continue; // 回到while循环开头，相当于开始新的递归
		case 2:
			chosen.pop_back();
			address = ret(); // 相当于原calc函数结尾，执行return
		}
	}
}

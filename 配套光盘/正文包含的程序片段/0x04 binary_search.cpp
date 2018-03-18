// 在单调递增序列a中查找>=x的数中最小的一个（即x或x的后继）
while (l < r) {
	int mid = (l + r) / 2;
	if (a[mid] >= x) r = mid; else l = mid + 1;
}

// 在单调递增序列a中查找<=x的数中最大的一个（即x或x的前驱）
while (l < r) {
	int mid = (l + r + 1) / 2;
	if (a[mid] <= x) l = mid; else r = mid - 1;
}

// 实数域二分，设置eps法
while (l + eps < r) {
	double mid = (l + r) / 2;
	if (calc(mid)) r = mid; else l = mid; 
}

// 实数域二分，规定循环次数法
for (int i = 0; i < 100; i++) {
	double mid = (l + r) / 2;
	if (calc(mid)) r = mid; else l = mid;	
}

// 把n本书分成m组，每组厚度之和<=size，是否可行
bool valid(int size) {
	int group = 1, rest = size;
	for (int i = 1; i <= n; i++) {
		if (rest >= a[i]) rest -= a[i];
		else group++, rest = size - a[i];
	}
	return group <= m;
}

// 二分答案，判定“每组厚度之和不超过二分的值”时能否在m组内把书分完
int l = 0, r = sum_of_Ai;
while (l < r) {
	int mid = (l + r) / 2;
	if (valid(mid)) r = mid; else l = mid + 1;
}
cout << l << endl;

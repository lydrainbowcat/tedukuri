// 二叉堆
int heap[SIZE], n;
void up(int p) {
	while (p > 1) {
		if (heap[p] > heap[p/2]) {
			swap(heap[p], heap[p/2]);
			p/=2;
		}
		else break;
	}	
}
void down(int p) {
	int s = p*2;
	while (s <= n) {
		if (s < n && heap[s] < heap[s+1]) s++;
		if (heap[s] > heap[p]) {
			swap(heap[s], heap[p]);
			p = s, s = p*2;
		}
		else break;
	}
}
void Insert(int val) {
	heap[++n] = val;
	up(n);
}
int GetTop() {
	return heap[1];
}
void Extract() {
	heap[1] = heap[n--];
	down(1);
}
void Remove(int k) {
	heap[k] = heap[n--];
	up(k), down(k);
}
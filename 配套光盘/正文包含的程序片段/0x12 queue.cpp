// 单调队列
int l = 1, r = 1;
q[1] = 0; // save choice j=0
for(int i = 1; i <= n; i++)
{
	while (l <= r && q[l] < i - m) l++;
	ans = max(ans, sum[i] - sum[q[l]]);
	while (l <= r && sum[q[r]] >= sum[i]) r--;
	q[++r] = i;
}

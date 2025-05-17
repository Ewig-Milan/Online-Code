//
// 按删除时间排序 前面后删 后面先删 前面对后面的贡献 跑两遍 一遍倒着降序 看后面 位置在后 数值小（向上查）
//
#include <bits/stdc++.h>
#define ll long long
#define Lb(x) (x & -x)
using namespace std;

const int N = 100100;

int n, k;
int ans[N];
ll ANS[N];

struct Node {
	int a, id, t;
	friend bool operator < (const Node & a, const Node & b) {
		return a.t == b.t ? (a.id == b.id ? a.a < b.a : a.id < b.id) : a.t < b.t;
	}
} Q[N], tmp[N];
int tmp_cnt;

struct Bit_T {
	int sum[N << 1];
	void modify(int x, int delta) {while(x <= n) sum[x] += delta, x += Lb(x);}
	int query(int x) {
		int res = 0;
		while(x) res += sum[x], x -= Lb(x);
		return res;
	}
}t;

void solve(int l, int r) {
	if(l == r) return;
	int mid = l + r >> 1;
	solve(l, mid); solve(mid + 1, r); // 按 位置升序 排好了 
	int i = mid, j = r;
	tmp_cnt = 0;
	while(i >= l && j > mid) //位置在它后面 数值比它小
		if(Q[i].id > Q[j].id) t.modify(Q[i].a, 1), i--;
		else ans[Q[j].t] += t.query(Q[j].a), j--;
	while(i >= l) t.modify(Q[i].a, 1), i--;
	while(j > mid) ans[Q[j].t] += t.query(Q[j].a), j--;
	for(int i = l; i <= mid; i++) t.modify(Q[i].a, -1);

    i = l, j = mid + 1;
    while(i <= mid && j <= r)
		if(Q[i].id < Q[j].id) t.modify(Q[i].a, 1), tmp[++tmp_cnt] = Q[i++];
		else ans[Q[j].t] += t.query(n) - t.query(Q[j].a), tmp[++tmp_cnt] = Q[j++];
	while(i <= mid) t.modify(Q[i].a, 1), tmp[++tmp_cnt] = Q[i++];
	while(j <= r) ans[Q[j].t] += t.query(n) - t.query(Q[j].a), tmp[++tmp_cnt] = Q[j++];
	for(int i = l; i <= mid; i++) t.modify(Q[i].a, -1);

	for(int i = 1; i <= tmp_cnt; i++) Q[i + l - 1] = tmp[i];
}

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++) {
        int a; scanf("%d", &a);
        Q[a].a = a, Q[a].id = i;
    }
    for(int i = 1; i <= k; i++) {
        int a; scanf("%d", &a);
        Q[a].t = n - i + 1;
    }
	sort(Q + 1, Q + n + 1);
	solve(1, n);
    ANS[k + 1] = ans[0];
    for(int i = k; i; i--) ANS[i] = ANS[i + 1] + ans[n - i + 1]; //反着做前缀和
    for(int i = 1; i <= k; i++) printf("%lld\n", ANS[i]);
	return 0;
}
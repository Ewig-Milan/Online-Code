//
// 按删除时间排序 前面后删 后面先删 前面对后面的贡献 跑两遍 一遍倒着降序 看后面 位置在后 数值小（向上查）
//
#include <bits/stdc++.h>
#define Lb(x) (x & -x)
using namespace std;

const int N = 1100;

int n, k, T[N];
int ans[N], ANS[N];

struct Node {
	int a, id, t;
	friend bool operator < (const Node & a, const Node & b) {
		return a.t == b.t ? (a.id == b.id ? a.a < b.a : a.id < b.id) : a.t < b.t;
	}
	// friend bool operator != (const Node & a, const Node & b) {
	// 	return a.a != b.a || a.b != b.b || a.c != b.c;
	// }
} Q[N], tmp[N];
int tmp_cnt;

struct Bit_T {
	int sum[N << 1];
	void modify(int x, int delta) {while(x <= k) sum[x] += delta, x += Lb(x);}
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
	while(i >= l && j > mid) {
		if(Q[i].id > Q[j].id) t.modify(Q[i].a, 1), i--;
		else ans[Q[j].t] += t.query(Q[j].a), j--;
	}
	while(i >= l) t.modify(Q[i].a, -1), i--;
	while(j > mid) ans[Q[j].t] += t.query(Q[j].a), j--;

    i = l, j = mid + 1;
    while(i <= mid && j <= r) {
		if(Q[i].id < Q[j].id) t.modify(Q[i].a, 1), tmp[++tmp_cnt] = Q[i++];
		else ans[Q[j].t] += t.query(n) - t.query(Q[j].a), tmp[++tmp_cnt] = Q[j++];
    }
	while(i <= mid) t.modify(Q[i].a, -1), tmp[++tmp_cnt] = Q[i++];
	while(j <= r) ans[Q[j].t] += t.query(n) - t.query(Q[j].a), tmp[++tmp_cnt] = Q[j++];

	for(int i = 1; i <= tmp_cnt; i++) Q[i + l - 1] = tmp[i];
}

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++) scanf("%d", &Q[i].a), Q[i].id = i;
    for(int i = 1; i <= k; i++) {
        scanf("%d", &T[i]);
        Q[T[i]].t = n - i + 1;
    }
	sort(Q + 1, Q + n + 1);
	solve(1, n);
    for(int i = k; i; i--) ANS[i] += ans[T[i]];
    for(int i = 1; i <= k; i++) printf("%d\n", ANS[i]);
	return 0;
}
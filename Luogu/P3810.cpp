#include <bits/stdc++.h>
#define Lb(x) (x & -x)
using namespace std;

const int N = 100100;

int n, k, Nn;
int ans[N], ANS[N];

struct Node {
	int a, b, c, cnt, id;
	friend bool operator < (const Node & a, const Node & b) {
		return a.a == b.a ? (a.b == b.b ? a.c < b.c : a.b < b.b) : a.a < b.a;
	}
	friend bool operator != (const Node & a, const Node & b) {
		return a.a != b.a || a.b != b.b || a.c != b.c;
	}
}Q[N], tmp[N];
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
	solve(l, mid); solve(mid + 1, r); // 按 b 排好了 
	int i = l, j = mid + 1;
	tmp_cnt = 0;
	while(i <= mid && j <= r) {
		if(Q[i].b <= Q[j].b) t.modify(Q[i].c, Q[i].cnt), tmp[++tmp_cnt] = Q[i++];
		else ans[Q[j].id] += t.query(Q[j].c), tmp[++tmp_cnt] = Q[j++];
	}
	while(i <= mid) t.modify(Q[i].c, Q[i].cnt), tmp[++tmp_cnt] = Q[i++];
	while(j <= r) ans[Q[j].id] += t.query(Q[j].c), tmp[++tmp_cnt] = Q[j++];
	for(int i = l; i <= mid; i++) t.modify(Q[i].c, -Q[i].cnt);
	for(int i = 1; i <= tmp_cnt; i++) Q[i + l - 1] = tmp[i];
}

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++) scanf("%d%d%d", &Q[i].a, &Q[i].b, &Q[i].c);
	sort(Q + 1, Q + n + 1);
	for(int i = 1; i <= n; i++) {
		if(Q[i] != Q[Nn]) Q[++Nn] = Q[i], Q[Nn].id = Nn;
		Q[Nn].cnt++;
	}
	solve(1, Nn);
	for(int i = 1; i <= Nn; i++) ANS[ans[Q[i].id] + Q[i].cnt - 1] += Q[i].cnt;
	for(int i = 0; i < n; i++) printf("%d\n", ANS[i]);
	return 0;
}
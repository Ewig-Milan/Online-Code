//
// l~r 每块木板会在第几个子弹射出后碎掉 单点修改 + 区间查询 
//
#include <bits/stdc++.h>
#define Lb(x) (x & -x)
using namespace std;

const int N = 200100;

int n, m, ans[N], brok[N];
struct Board {int l, r, s;}B[N];
int sht[N];

struct Bit_T {
	int sum[N];
	void modify(int x, int delta) {while(x <= 200000) sum[x] += delta, x += Lb(x);}
	int presum(int x) {
		int res = 0;
		while(x) res += sum[x], x -= Lb(x);
		return res;
	} 
	int query(int l, int r) {return presum(r) - presum(l - 1);}
}t;

void solve(int l, int r, vector<int> & q) {
	if(l == r || q.empty()) {
		for(int i : q) brok[i] = l;
		return;
	}
	int mid = l + r >> 1;
	vector<int> ql, qr;
	for(int i = l; i <= mid; i++)
		t.modify(sht[i], 1);
	for(int i : q) {
		int tmp = t.query(B[i].l, B[i].r);
		if(tmp >= B[i].s) ql.push_back(i);
		else B[i].s -= tmp, qr.push_back(i);
	}
	for(int i = l; i <= mid; i++) t.modify(sht[i], -1);
	solve(l, mid, ql); solve(mid + 1, r, qr);
}

int main() {
	scanf("%d%d", &n, &m);
	vector<int> q;
	for(int i = 1; i <= n; i++) {
		int a, b, c; scanf("%d%d%d", &a, &b, &c);
		B[i] = {a, b, c};
		q.push_back(i);
	}
	for(int i = 1; i <= m; i++) scanf("%d", &sht[i]);
	sht[m + 1] = 200001;
	solve(1, m + 1, q);
	for(int i = 1; i <= n; i++) ans[brok[i]]++;
	for(int i = 1; i <= m; i++) printf("%d\n", ans[i]);
	return 0;
}
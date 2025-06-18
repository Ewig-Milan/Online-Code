#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 200100;

vector<int> dc;

ll ans;
int n, Nn;

struct Node {
	int x, l, r, k;
	friend bool operator < (const Node & a, const Node & b) {return a.x < b.x;}
} Q[N];

struct TR {
	struct Min {
		int mi, mic;
		friend Min operator + (Min a, Min b) {
			if(a.mi > b.mi) swap(a, b);
			return {a.mi, a.mi == b.mi ? a.mic + b.mic : a.mic};
		}
	};
	vector<Min> mi;
	vector<int> ly;
	void cl(int n) {
		n <<= 2;
		mi.resize(0), mi.resize(n);
		ly.resize(0), ly.resize(n);
	}
	void push_up(int rt) {mi[rt] = mi[rt << 1] + mi[rt << 1 | 1];}
	void push_down(int rt) {
		if(!ly[rt]) return;
		ly[rt << 1] += ly[rt], ly[rt << 1 | 1] += ly[rt];
		mi[rt << 1].mi += ly[rt];
		mi[rt << 1 | 1].mi += ly[rt];
		ly[rt] = 0;
	}
	
	void build(int rt, int l, int r) {
		if(l == r) {
			mi[rt].mi = 0, mi[rt].mic = dc[r] - dc[l - 1];
			return;
		}
		int mid = l + r >> 1;
		build(rt << 1, l, mid);
		build(rt << 1 | 1, mid + 1, r);
		push_up(rt);
	}
	void modify(int rt, int l, int r, int ql, int qr, int x) {
		if(ql <= l && qr >= r) {
			mi[rt].mi += x, ly[rt] += x;
			return;
		}
		int mid = l + r >> 1;
		push_down(rt);
		if(ql <= mid) modify(rt << 1, l, mid, ql, qr, x);
		if(qr > mid) modify(rt << 1 | 1, mid + 1, r, ql, qr, x);
		push_up(rt);
	}
}tr;

int main() {
	scanf("%d", &n), n <<= 1;
	for(int i = 1; i <= n; i++) {
		int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);
		Q[i] = {a, b, d, 1}, Q[++i] = {c, b, d, -1};
		dc.push_back(b), dc.push_back(d);
	}
	sort(dc.begin(), dc.end());
	Nn = unique(dc.begin(), dc.end()) - dc.begin();
	dc.resize(Nn);
	Nn--;
	tr.cl(Nn); tr.build(1, 1, Nn);
	
	sort(Q + 1, Q + n + 1);
	for(int i = 1, prex = 0; i <= n; prex = Q[i++].x) {
		int tmp = dc[Nn] - dc[0];
		if(!tr.mi[1].mi) tmp -= tr.mi[1].mic;
		ans += (ll)(Q[i].x - prex) * tmp;
		Q[i].l = lower_bound(dc.begin(), dc.end(), Q[i].l) - dc.begin() + 1;
		Q[i].r = lower_bound(dc.begin(), dc.end(), Q[i].r) - dc.begin();
		tr.modify(1, 1, Nn, Q[i].l, Q[i].r, Q[i].k);
	}
	printf("%lld", ans);
	return 0;
}
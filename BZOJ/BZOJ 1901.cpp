#include <bits/stdc++.h>
#define Lb(x) (x & -x)
using namespace std;

const int N = 20100;

int n, m, ans[N], d[N], Q;
struct Ope {int mode, l, r, k, id;};//1询问 0修改
struct Bit_T {
	vector<int> sum;
	int tot;
	void cl(int n) {
		sum.resize(0);
		sum.resize(n + 100);
		tot = n;
	}
	void modify(int x, int delta) {
		while(x <= tot)	sum[x] += delta, x += Lb(x);
	}
	int presum(int x) {
		int res = 0;
		while(x) res += sum[x], x -= Lb(x);
		return res;
	}
	int query(int l, int r) {return presum(r) - presum(l - 1);}
}t;
void solve(int l, int r, const vector<Ope> & q) {
	if(l == r || q.empty()) {
		for(Ope i : q) if(i.mode) ans[i.id] = l;
		return; 
	}
	int mid = l + r >> 1;
	vector<Ope> ql, qr;
	for(Ope i : q) {
		if(i.mode) {
			int tmp = t.query(i.l, i.r);
			if(tmp >= i.k) ql.push_back(i);
			else i.k -= tmp, qr.push_back(i);
		} else {
			if(i.r <= mid) t.modify(i.l, i.k), ql.push_back(i);
			else qr.push_back(i);
		}
	}
	for(Ope i : ql) if(!i.mode) t.modify(i.l, -i.k);
	solve(l, mid, ql); ql.resize(0);
	solve(mid + 1, r, qr); qr.resize(0);
}
int main() {
	scanf("%d%d", &n, &m);
	t.cl(n);
	vector<Ope> q;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &d[i]);
		q.push_back({0, i, d[i], 1, i});
	}
	for(int i = 1; i <= m; i++) {
        char mode[5]; scanf("%s", mode);
        if(mode[0] == 'Q') {
            int a, b, c; scanf("%d%d%d", &a, &b, &c);
            q.push_back({1, a, b, c, ++Q});
        } else {
            int a, b; scanf("%d%d", &a, &b);
            q.push_back({0, a, d[a], -1, i});
            q.push_back({0, a, b, 1, i});
            d[a] = b;
        }
	}
	solve(-1e9, 1e9, q);
	for(int i = 1; i <= Q; i++) printf("%d\n", ans[i]);
	return 0;
}
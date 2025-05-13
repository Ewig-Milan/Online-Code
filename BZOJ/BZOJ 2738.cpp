#include <bits/stdc++.h>
#define Lb(x) (x & -x)
using namespace std;

const int N = 600;

int n, Q, ans[60100];

struct Ope {bool mode; int x, y, X, Y, k, id;};
struct Bit_T {
	int sum[N][N];
	void modify(int x, int y, int delta) {
		for(int i = x; i <= n; i += Lb(i))
		for(int j = y; j <= n; j += Lb(j))
			sum[i][j] += delta;
	}
	int presum(int x, int y) {
		int res = 0;
		for(int i = x; i; i -= Lb(i))
		for(int j = y; j; j -= Lb(j))
			res += sum[i][j];
		return res;
	}
	int query(int x, int y, int X, int Y) {
		x--, y--;
		return presum(X, Y) - presum(X, y) - presum(x, Y) + presum(x, y);
	}
}t;

void solve(int l, int r, vector<Ope> & q) {
	if(l == r || q.empty()) {
		for(Ope i : q) if(i.mode) ans[i.id] = l;
		return;
	}
	vector<Ope> ql, qr;
	int mid = l + r >> 1;
	for(Ope i : q) {
		if(i.mode) {
			int tmp = t.query(i.x, i.y, i.X, i.Y);
			if(tmp >= i.k) ql.push_back(i);
			else i.k -= tmp, qr.push_back(i);
		} else {
			if(i.Y <= mid) t.modify(i.x, i.y, i.k), ql.push_back(i);
			else qr.push_back(i);
		}
	}
	for(Ope i : ql) if(!i.mode) t.modify(i.x, i.y, -i.k);
	solve(l, mid, ql); solve(mid + 1, r, qr);
}

int main() {
	scanf("%d%d", &n, &Q);
	vector<Ope> q;
	for(int i = 1; i <= n; i++)
	for(int j = 1; j <= n; j++) {
		int a; scanf("%d", &a);
		q.push_back({0, i, j, 0, a, 1, 0});
	}
	for(int i = 1; i <= Q; i++) {
		int a, x, y, X, Y; scanf("%d%d%d%d%d", &x, &y, &X, &Y, &a);
		q.push_back({1, x, y, X, Y, a, i});
	}
	solve(0, 1e9, q);
	for(int i = 1; i <= Q; i++) printf("%d\n", ans[i]);
	return 0;
}
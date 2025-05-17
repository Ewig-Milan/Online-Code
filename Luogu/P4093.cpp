#include <bits/stdc++.h>
#define Lb(x) (x & -x)
using namespace std;

const int N = 100100;

int n, m, ans, f[N];

struct Node {int a, ma, mi, id;} Q[N], tmp[N];
bool cmp_ma(const Node & a, const Node & b) {return a.ma < b.ma;}
bool cmp_a(const Node & a, const Node & b) {return a.a < b.a;}

struct Bit_T {
	int ma[100100];
    void cl(int x) {while(x <= 100000) ma[x] = 0, x += Lb(x);}
	void modify(int x, int a) {while(x <= 100000) ma[x] = max(a, ma[x]), x += Lb(x);}
	int query(int x) {
		int res = 0;
		while(x) res = max(res, ma[x]), x -= Lb(x);
		return res;
	}
}t;

void solve(int l, int r) {
	if(l == r) return;
	int mid = l + r >> 1;
	solve(l, mid);
    // 左边按max, 右边按原值
    for(int i = l; i <= r; i++) tmp[i] = Q[i];
    sort(tmp + l, tmp + mid + 1, cmp_ma); //注意 sort 是左闭右开
    sort(tmp + mid + 1, tmp + r + 1, cmp_a);
	int i = l, j = mid + 1;
    while(i <= mid && j <= r) {
        if(tmp[i].ma <= tmp[j].a) t.modify(tmp[i].a, f[tmp[i].id]), i++;
        else f[tmp[j].id] = max(f[tmp[j].id], t.query(tmp[j].mi) + 1), j++;
    }
	while(j <= r) f[tmp[j].id] = max(f[tmp[j].id], t.query(tmp[j].mi) + 1), j++;
    for(int i = l; i <= mid; i++) t.cl(tmp[i].a);
    solve(mid + 1, r);
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &Q[i].a), Q[i].id = i, Q[i].ma = Q[i].mi = Q[i].a;
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        Q[a].ma = max(Q[a].ma, b);
        Q[a].mi = min(Q[a].mi, b);
    }
    f[1] = 1;
	solve(1, n);
    for(int i = 1; i <= n; i++) ans = max(ans, f[i]);
    printf("%d", ans);
	return 0;
}
#include <bits/stdc++.h>
#define Lb(x) (x & -x)
#define get_id(x) lower_bound(dc.begin(), dc.end(), x) - dc.begin() + 1
using namespace std;

const int N = 1000100, mod = 19921228;

int Nn;
vector<int> dc;

int n, ans[N], ANS;
struct Doll {int c, l, r;}D[N];
bool cmp(const Doll & a, const Doll & b) {return a.c > b.c;}
struct Ques {int p, k;}Q[N];

struct Bit_T {
	int sum[N << 2];
	void modify(int x, int delta) {while(x <= Nn) sum[x] += delta, x += Lb(x);}
	int query(int x) {
		int res = 0;
		while(x) res += sum[x], x -= Lb(x);
		return res;
	}
}t;

void solve(int l, int r, vector<int> & q) {
	if(l == r || q.empty()) {
		for(int i : q) ans[i] = D[l].c % mod;
		return;
	}
	int mid = l + r >> 1;
	vector<int> ql, qr;
	for(int i = l; i <= mid; i++) t.modify(D[i].l, 1), t.modify(D[i].r + 1, -1);
	for(int i : q) {
		int tmp = t.query(Q[i].p);
		if(tmp >= Q[i].k) ql.push_back(i);
		else Q[i].k -= tmp, qr.push_back(i);
	}
	for(int i = l; i <= mid; i++) t.modify(D[i].l, -1), t.modify(D[i].r + 1, 1);
	solve(l, mid, ql); solve(mid + 1, r, qr);
}

int main() {
	vector<int> q;
	scanf("%d", &n);
    
    int Pad, Pf, Pm, Pp, Cad, Cf, Cm, Cp, Lad, Lf, Lm, Lp, Rad, Rf, Rm, Rp;
    scanf("%d%d%d%d%d%d%d%d", &Pad, &Pf, &Pm, &Pp, &Cad, &Cf, &Cm, &Cp);
    scanf("%d%d%d%d%d%d%d%d", &Lad, &Lf, &Lm, &Lp, &Rad, &Rf, &Rm, &Rp);
    int a = Pf % Pm, b = Cf % Cm, c = Lf % Lm, d = Rf % Rm;
	for(int i = 1; i <= n; i++) {
        dc.push_back(a); dc.push_back(c), dc.push_back(d);
        dc.push_back(d + 1);
		if(c > d) D[i] = {b, d, c}; else D[i] = {b, c, d};
        Q[i] = {a, i};
		q.push_back(i);
        a = ((long long)a * Pp + Pad + i + 1) % Pm;
        b = ((long long)b * Cp + Cad + i + 1) % Cm;
        c = ((long long)c * Lp + Lad + i + 1) % Lm;
        d = ((long long)d * Rp + Rad + i + 1) % Rm;
	}

    sort(dc.begin(), dc.end());
    Nn = unique(dc.begin(), dc.end()) - dc.begin();
    dc.resize(Nn);
    for(int i = 1; i <= n; i++)
        D[i].l = get_id(D[i].l), D[i].r = get_id(D[i].r), Q[i].p = get_id(Q[i].p);
	D[n + 1] = {0, 1, Nn};

	sort(D + 1, D + n + 1, cmp);
	solve(1, n + 1, q);
	for(int i = 1; i <= n; i++) ANS += ans[i], ANS %= mod;
	printf("%d", ANS);
	return 0;
}
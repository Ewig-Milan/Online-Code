#include <bits/stdc++.h>
#define int long long
#define Lb(x) (x & -x)
using namespace std;

const int N = 300100;

int n, m, k, ans[N];
struct Ope {int l, r, a;} met[N];
struct Ques {
    vector<int> o;
    int p;
} stn[N];

struct Bit_T {
    int sum[N * 2];
    void modify(int x, int delta) {
        while(x <= (m << 1)) sum[x] += delta, x += Lb(x);
    }
    int query(int x) {
        int res = 0;
        while(x) res += sum[x], x -= Lb(x);
        return res;
    }
}t;

void solve(int l, int r, vector<int> & q) {
    if(l == r || q.empty()) {
        for(int i : q) ans[i] = l;
        return;
    }
    int mid = l + r >> 1;
    vector<int> ql, qr;
    for(int i = l; i <= mid; i++)
        t.modify(met[i].l, met[i].a), t.modify(met[i].r + 1, -met[i].a);
    for(int i : q) {
        int tmp = 0;
        for(int j : stn[i].o) {
			tmp += t.query(j) + t.query(j + m);
        	if(tmp >= stn[i].p) break;
		}
        if(tmp >= stn[i].p) ql.push_back(i);
        else stn[i].p -= tmp, qr.push_back(i);
    }
    for(int i = l; i <= mid; i++)
        t.modify(met[i].l, -met[i].a), t.modify(met[i].r + 1, met[i].a);
    solve(l, mid, ql); solve(mid + 1, r, qr);
}

signed main() {
    scanf("%lld%lld", &n, &m);
    for(int i = 1; i <= m; i++) {
        int a; scanf("%lld", &a);
        stn[a].o.push_back(i);
    }
    vector<int> q;
    for(int i = 1; i <= n; i++) scanf("%lld", &stn[i].p), q.push_back(i);
    scanf("%lld", &k);
    for(int i = 1; i <= k; i++) {
        int a, b, c; scanf("%lld%lld%lld", &a, &b, &c);
        if(b < a) b += m;
        met[i] = {a, b, c};
    }
    solve(1, k + 1, q); // 答案在 l ~ r 中, 当前有哪些ques
    for(int i = 1; i <= n; i++) printf(ans[i] <= k ? "%lld\n" : "NIE\n", ans[i]);
    return 0;
}
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 500100;

int n, m, Nn;
int A[N], B[N];
vector<int> dc;

struct Seg_T {
    vector<ll> ma, ly;
    void cl(int x) {
        ma.resize(0), ma.resize(x << 2);
        ly.resize(0), ly.resize(x << 2);
    }
    void push_up(int rt) {ma[rt] = max(ma[rt << 1], ma[rt << 1 | 1]);}
    void build(int rt, int l, int r) {
        if(l == r) {
            ma[rt] = -(ll)m * dc[l - 1];
            return;
        }
        int mid = l + r >> 1;
        build(rt << 1, l, mid);
        build(rt << 1 | 1, mid + 1, r);
        push_up(rt);
    }
    void push_down(int rt) {
        if(!ly[rt]) return;
        ly[rt << 1] += ly[rt], ly[rt << 1 | 1] += ly[rt];
        ma[rt << 1] += ly[rt], ma[rt << 1 | 1] += ly[rt];
        ly[rt] = 0;
    }
    void modify(int rt, int l, int r, int ql, int qr, ll x) {
        if(ql > qr) return;
        if(ql <= l && qr >= r) {
            ma[rt] += x, ly[rt] += x;
            return;
        }
        push_down(rt);
        int mid = l + r >> 1;
        if(ql <= mid) modify(rt << 1, l, mid, ql, qr, x);
        if(qr > mid) modify(rt << 1 | 1, mid + 1, r, ql, qr, x);
        push_up(rt);
    }
    ll query(int rt, int l, int r, int ql, int qr) {
        if(ql <= l && qr >= r) return ma[rt];
        push_down(rt);
        int mid = l + r >> 1;
        ll ans = -1e15;
        if(ql <= mid) ans = max(ans, query(rt << 1, l, mid, ql, qr));
        if(qr > mid) ans = max(ans, query(rt << 1 | 1, mid + 1, r, ql, qr));
        return ans;
    }
}t1, t2;

void work() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
        scanf("%d%d", &A[i], &B[i]);
        dc.push_back(A[i]), dc.push_back(A[i] - 1);
    }
    dc.push_back(0);
    sort(dc.begin(), dc.end());
    Nn = unique(dc.begin(), dc.end()) - dc.begin();
    dc.resize(Nn), t1.cl(Nn), t2.cl(Nn), t1.build(1, 1, Nn);
    for(int i = 1; i <= n; i++) A[i] = lower_bound(dc.begin(), dc.end(), A[i]) - dc.begin() + 1;
    for(int i = 1; i <= n; i++) {
        ll ma1 = t1.query(1, 1, Nn, A[i], Nn), ma2 = t2.query(1, 1, Nn, 1, A[i] - 1);
        ll fij = t1.query(1, 1, Nn, A[i], A[i]), fij_1 = t1.query(1, 1, Nn, A[i] - 1, A[i] - 1);
        fij = max(fij + B[i], ma2 - (ll)m * dc[A[i] - 1] + B[i]) - fij, fij_1 = max(fij_1, ma1) - fij_1;
        t1.modify(1, 1, Nn, A[i], A[i], fij), t2.modify(1, 1, Nn, A[i] - 1, A[i] - 1, fij_1);
        t2.modify(1, 1, Nn, A[i], A[i], fij), t1.modify(1, 1, Nn, A[i] - 1, A[i] - 1, fij_1);
        t1.modify(1, 1, Nn, A[i] + 1, Nn, B[i]), t2.modify(1, 1, Nn, A[i] + 1, Nn, B[i]);
    }
    printf("%lld\n", t1.ma[1]);
}

int main() {
    int T; scanf("%d", &T);
    while(T--) {
        dc.resize(0);
        work();
    }
    return 0;
}
#include <bits/stdc++.h>
#define ll long long
#define PII pair<int, int> // min / max
#define fi first
#define se second
using namespace std;

const int N = 100100, INF = 1e9 + 10;

int n, m, q;
int A[N], B[N];

struct TR {
    vector<PII> M;
    void cl(int n) {M.resize(n << 2);}

    void push_up(int rt) {
        M[rt].fi = min(M[rt << 1].fi, M[rt << 1 | 1].fi);
        M[rt].se = max(M[rt << 1].se, M[rt << 1 | 1].se);
    }

    PII query(int rt, int l, int r, int ql, int qr) {
        if(ql <= l && qr >= r) return M[rt];
        int mid = l + r >> 1;
        PII res = {INF, -INF};
        if(ql <= mid) res = query(rt << 1, l, mid, ql, qr);
        if(qr > mid) {
            PII tmp = query(rt << 1 | 1, mid + 1, r, ql, qr);
            res.fi = min(res.fi, tmp.fi), res.se = max(res.se, tmp.se);
        }
        return res;
    }
}A_pos, A_neg, B_tr;

void B_build(int rt, int l, int r) {
    if(l == r) {
        B_tr.M[rt] = {B[l], B[l]};
        return;
    }
    int mid = l + r >> 1;
    B_build(rt << 1, l, mid);
    B_build(rt << 1 | 1, mid + 1, r);
    B_tr.push_up(rt);
}

void A_pos_build(int rt, int l, int r) {
    if(l == r) {
        if(A[l] >= 0) A_pos.M[rt] = {A[l], A[l]};
        else A_pos.M[rt] = {INF, -1};
        return;
    }
    int mid = l + r >> 1;
    A_pos_build(rt << 1, l, mid);
    A_pos_build(rt << 1 | 1, mid + 1, r);
    A_pos.push_up(rt);
}

void A_neg_build(int rt, int l, int r) {
    if(l == r) {
        if(A[l] < 0) A_neg.M[rt] = {A[l], A[l]};
        else A_neg.M[rt] = {1, -INF};
        return;
    }
    int mid = l + r >> 1;
    A_neg_build(rt << 1, l, mid);
    A_neg_build(rt << 1 | 1, mid + 1, r);
    A_neg.push_up(rt);
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 1; i <= n; i++) scanf("%d", &A[i]);
    for(int i = 1; i <= m; i++) scanf("%d", &B[i]);
    A_pos.cl(n), A_neg.cl(n), B_tr.cl(m);
    A_pos_build(1, 1, n);
    A_neg_build(1, 1, n);
    B_build(1, 1, m);
    while(q--) {
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        ll ans = -1e18 - 100;
        PII B_ = B_tr.query(1, 1, m, l2, r2);
        PII A_pos_ = A_pos.query(1, 1, n, l1, r1);
        PII A_neg_ = A_neg.query(1, 1, n, l1, r1);
        if(A_pos_.fi != INF) ans = max(ans, min((ll)A_pos_.fi * B_.fi, (ll)A_pos_.fi * B_.se));
        if(A_pos_.se != -1) ans = max(ans, min((ll)A_pos_.se * B_.fi, (ll)A_pos_.se * B_.se));
        if(A_neg_.fi != 1) ans = max(ans, min((ll)A_neg_.fi * B_.fi, (ll)A_neg_.fi * B_.se));
        if(A_neg_.se != -INF) ans = max(ans, min((ll)A_neg_.se * B_.fi, (ll)A_neg_.se * B_.se));
        printf("%lld\n", ans);
    }
    return 0;
}
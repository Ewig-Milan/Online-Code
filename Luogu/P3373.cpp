#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n, m;
ll p;
struct Node {
    ll sum, add = 0, mul = 1;
};
struct TR {
    vector<Node> tr;
    void cl(int n) {tr.resize(n << 2);}
    void push_up(int rt) {tr[rt].sum = tr[rt << 1].sum + tr[rt << 1 | 1].sum;}
    void build(int rt, int l, int r) {
        if(l == r) {
            scanf("%lld", &tr[rt].sum);
            return;
        }
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid);
        build(rt << 1 | 1, mid + 1, r);
        push_up(rt);
    }
    void op(int rt, int l, int r, ll add, ll mul) {
        tr[rt].sum = (tr[rt].sum * mul + (add * (r - l + 1)) % p) % p;
        tr[rt].add = tr[rt].add * mul + add, tr[rt].add %= p;
        tr[rt].mul *= mul, tr[rt].mul %= p;
    }
    void push_down(int rt, int l, int r) {
        if(!tr[rt].add && tr[rt].mul == 1) return;
        int mid = (l + r) >> 1;
        op(rt << 1, l, mid, tr[rt].add, tr[rt].mul);
        op(rt << 1 | 1, mid + 1, r, tr[rt].add, tr[rt].mul);
        tr[rt].add = 0, tr[rt].mul = 1;
    }
    void modify(int rt, int l, int r, int ql, int qr, ll add, ll mul) {
        if(ql <= l && qr >= r) {
            op(rt, l, r, add, mul);
            return;
        }
        push_down(rt, l, r);
        int mid = (l + r) >> 1;
        if(ql <= mid) modify(rt << 1, l, mid, ql, qr, add, mul);
        if(qr > mid) modify(rt << 1 | 1, mid + 1, r, ql, qr, add, mul);
        push_up(rt);
    }
    ll query(int rt, int l, int r, int ql, int qr) {
        if(ql <= l && qr >= r) return tr[rt].sum;
        push_down(rt, l, r);
        int mid = (l + r) >> 1;
        ll ans = 0;
        if(ql <= mid) ans += query(rt << 1, l, mid, ql, qr), ans %= p;
        if(qr > mid) ans += query(rt << 1 | 1, mid + 1, r, ql, qr), ans %= p; 
        return ans;
    }
}d;

int main() {
    scanf("%d%d%lld", &n, &m, &p);
    d.cl(n);
    d.build(1, 1, n);
    while(m--) {
        int mode, l, r; scanf("%d%d%d", &mode, &l, &r);
        ll k;
        if(mode == 3) printf("%lld\n", d.query(1, 1, n, l, r));
        else scanf("%lld", &k);
        if(mode == 1) d.modify(1, 1, n, l, r, 0, k);
        if(mode == 2) d.modify(1, 1, n, l, r, k, 1);
    }
    return 0;
}
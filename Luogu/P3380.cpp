// pbds
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long
using namespace std;
using namespace __gnu_pbds;

ll seed = 114514;
ll rnd() {return (seed = (seed * 2718281 + 20100907) % 100000000) + 1;};

const int N = 200100;

int n, m;
ll A[N];

struct TR {
    tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> t[N << 2];
    void build(int rt, int l, int r) {
        t[rt].clear();
        for(int i = l; i <= r; i++) t[rt].insert(A[i]);
        if(l == r) return; // 注意
        int mid = l + r >> 1;
        build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
    }
    void modify(int rt, int l, int r, int pos, ll a, ll b) {
        t[rt].erase(a), t[rt].insert(b);
        if(l == r) return; // 注意
        int mid = l + r >> 1;
        if(pos <= mid) modify(rt << 1, l, mid, pos, a, b);
        else modify(rt << 1 | 1, mid + 1, r, pos, a, b);
    }
    int query_less(int rt, int l, int r, int ql, int qr, ll x) {
        if(ql <= l && qr >= r) return t[rt].order_of_key(x);
        int mid = l + r >> 1, ans = 0;
        if(ql <= mid) ans += query_less(rt << 1, l, mid, ql, qr, x);
        if(qr > mid) ans += query_less(rt << 1 | 1, mid + 1, r, ql, qr, x);
        return ans;
    }
    ll query_pre(int rt, int l, int r, int ql, int qr, ll x) {
        if(ql <= l && qr >= r) {
            auto tmp = t[rt].lower_bound(x);
            if(tmp == t[rt].begin()) return 0;
            return *(--tmp);
        }
        int mid = l + r >> 1;
        ll ans = 0;
        if(ql <= mid) ans = max(ans, query_pre(rt << 1, l, mid, ql, qr, x));
        if(qr > mid) ans = max(ans, query_pre(rt << 1 | 1, mid + 1, r, ql, qr, x));
        return ans;
    }
    ll query_suf(int rt, int l, int r, int ql, int qr, ll x) {
        if(ql <= l && qr >= r) {
            auto tmp = t[rt].upper_bound(x);
            if(tmp == t[rt].end()) return (1ll << 62);
            else return *tmp;
        }
        int mid = l + r >> 1;
        ll ans = (1ll << 62);
        if(ql <= mid) ans = min(ans, query_suf(rt << 1, l, mid, ql, qr, x));
        if(qr > mid) ans = min(ans, query_suf(rt << 1 | 1, mid + 1, r, ql, qr, x));
        return ans;
    }
}t;

void modify(int a, int b) {
    ll x = A[a], y = ((ll)b << 27) + rnd();
    t.modify(1, 1, n, a, x, y), A[a] = y;
}
int rk(int l, int r, int k) {
    if(!k) return 1;
    ll x = ((ll)k << 27);
    return t.query_less(1, 1, n, l, r, x) + 1;
}
int get_by_rk(int a, int b, int k) {
    int l = 0, r = 1e8;
    while(l < r) {
        int mid = l + r + 1 >> 1;
        if(rk(a, b, mid) <= k) l = mid;
        else r = mid - 1;
    }
    return l;
}
int get_pre(int l, int r, int a) {
    if(!a) return -2147483647;
    ll x = ((ll)a << 27);
    ll ans = t.query_pre(1, 1, n, l, r, x);
    if(!ans) return -2147483647;
    return ans >> 27;
}
int get_suf(int l, int r, int a) {
    ll x = ((a + 1ll) << 27);
    ll ans = t.query_suf(1, 1, n, l, r, x);
    if(ans == (1ll << 62)) return 2147483647;
    return ans >> 27;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
        int a; scanf("%d", &a);
        A[i] = ((ll)a << 27) + rnd();
    }
    t.build(1, 1, n);
    while(m--) {
        int op; scanf("%d", &op);
        if(op == 3) {
            int a, b; scanf("%d%d", &a, &b);
            modify(a, b);
        } else {
            int l, r, k; scanf("%d%d%d", &l, &r, &k);
            if(op == 1) printf("%d\n", rk(l, r, k));
            if(op == 2) printf("%d\n", get_by_rk(l, r, k));
            if(op == 4) printf("%d\n", get_pre(l, r, k));
            if(op == 5) printf("%d\n", get_suf(l, r, k));
        }
    }
    return 0;
}
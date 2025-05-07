#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {return a ? gcd(b % a, a) : b;}

struct TR {
    vector<int> g;
    void cl(int n) {g.resize(0); g.resize(n << 2);}

    void push_up(int rt) {g[rt] = gcd(g[rt << 1], g[rt << 1 | 1]);}

    void build(int rt, int l, int r) {
        if(l == r) {
            scanf("%d", &g[rt]);
            return;
        }
        int mid = l + r >> 1;
        build(rt << 1, l, mid);
        build(rt << 1 | 1, mid + 1, r);
        push_up(rt);
    }
    int query(int rt, int l, int r, int ql, int qr) {
        if(ql <= l && qr >= r) return g[rt];
        int mid = l + r >> 1, ans = 0;
        if(ql <= mid) ans = gcd(ans, query(rt << 1, l, mid, ql, qr));
        if(qr > mid) ans = gcd(ans, query(rt << 1 | 1, mid + 1, r, ql, qr));
        return ans;
    }
}tr;

int n, m;

int main() {
    scanf("%d%d", &n, &m);
    tr.cl(n);
    tr.build(1, 1, n);
    while(m--) {
        int a, b; scanf("%d%d", &a, &b);
        printf("%d\n", tr.query(1, 1, n, a, b));
    }
    return 0;
}
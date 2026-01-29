#include <bits/stdc++.h>
using namespace std;

const int N = 1e7;

int n, q;
map<pair<int, int>, bool> M;

struct Seg_T {
    struct Node {
        int lc, rc, ly;
    }t[N];
    int tot = 0;
    int make() {
        t[++tot] = {0, 0, 0};
        return tot;
    }
    void push_down(int rt) {
        int &lc = t[rt].lc, &rc = t[rt].rc;
        if(!lc) lc = make();
        if(!rc) rc = make();
        if(!t[rt].ly) return;
        t[lc].ly = max(t[lc].ly, t[rt].ly);
        t[rc].ly = max(t[rc].ly, t[rt].ly);
        t[rt].ly = 0;
    }
    void modify(int rt, int l, int r, int ql, int qr, int x) {
        int &lc = t[rt].lc, &rc = t[rt].rc;
        if(ql <= l && qr >= r) {
            t[rt].ly = max(t[rt].ly, x);
            return;
        }
        push_down(rt);
        int mid = l + r >> 1;
        if(ql <= mid) modify(lc, l, mid, ql, qr, x);
        if(qr > mid) modify(rc, mid + 1, r, ql, qr, x);
    }
    int query(int rt, int l, int r, int a) {
        int &lc = t[rt].lc, &rc = t[rt].rc;
        if(l == r) return t[rt].ly;
        push_down(rt);
        int mid = l + r >> 1;
        if(a <= mid) return query(lc, l, mid, a);
        else return query(rc, mid + 1, r, a);
    }
}U, L;

int main() {
    scanf("%d%d", &n, &q);
    U.make(), L.make();
    while(q--) {
        int a, b; char c[5]; scanf("%d%d%s", &a, &b, c);
        if(M[{a, b}]) {
            puts("0");
            continue;
        }
        M[{a, b}] = 1;
        if(c[0] == 'U') {
            int l = U.query(1, 1, n, a) + 1, r = b;
            printf("%d\n", r - l + 1);
            L.modify(1, 1, n, l, r, a);
        } else {
            int l = L.query(1, 1, n, b) + 1, r = a;
            printf("%d\n", r - l + 1);
            U.modify(1, 1, n, l, r, b);
        }
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

const int N = 100100, M = 1e7;

int n, k, q, Nn;
int A[18][N], L2[N];

void init() {
    for(int i = 1; i <= n; i++) scanf("%d", &A[0][i]);
    for(int i = 1; i < 18; i++) for(int j = 1; j <= n; j++)
        A[i][j] = min(A[i - 1][j], A[i - 1][min(n, j + (1 << i - 1))]);
    for(int i = 2; i <= n; i++) L2[i] = L2[i >> 1] + 1;
}
int Q(int l, int r) {
    int tmp = L2[r - l + 1];
    return min(A[tmp][l], A[tmp][r - (1 << tmp) + 1]);
}

struct Seg_T {
    struct Node {
        int mi, ly, lc, rc;
    }t[M];
    int tot = 0;
    int make(int l, int r) {
        tot++;
        if(r - l + 1 >= n) t[tot].mi = Q(1, n);
        else {
            l = (l - 1) % n + 1, r = (r - 1) % n + 1;
            if(l > r) t[tot].mi = min(Q(1, r), Q(l, n));
            else t[tot].mi = Q(l, r);
        }
        t[tot].ly = -1;
        return tot;
    }
    void push_up(int rt) {
        int &lc = t[rt].lc, &rc = t[rt].rc;
        t[rt].mi = min(t[lc].mi, t[rc].mi);
    }
    void push_down(int rt, int l, int r) {
        int &lc = t[rt].lc, &rc = t[rt].rc;
        int mid = l + r >> 1;
        if(!lc) lc = make(l, mid);
        if(!rc) rc = make(mid + 1, r);
        if(t[rt].ly == -1) return;
        t[lc].ly = t[rc].ly = t[rt].ly;
        t[lc].mi = t[rc].mi = t[rt].ly;
        t[rt].ly = -1;
    }
    void modify(int rt, int l, int r, int ql, int qr, int x) {
        int &lc = t[rt].lc, &rc = t[rt].rc;
        if(ql <= l && qr >= r) {
            t[rt].ly = t[rt].mi = x;
            return;
        }
        push_down(rt, l, r);
        int mid = l + r >> 1;
        if(ql <= mid) modify(lc, l, mid, ql, qr, x);
        if(qr > mid) modify(rc, mid + 1, r, ql, qr, x);
        push_up(rt);
    }
    int query(int rt, int l, int r, int ql, int qr) {
        int &lc = t[rt].lc, &rc = t[rt].rc;
        if(ql <= l && qr >= r) return t[rt].mi;
        push_down(rt, l, r);
        int mid = l + r >> 1, ans = 1e9;
        if(ql <= mid) ans = min(ans, query(lc, l, mid, ql, qr));
        if(qr > mid) ans = min(ans, query(rc, mid + 1, r, ql, qr));
        return ans;
    }
}t;

int main() {
    scanf("%d%d", &n, &k);
    Nn = n * k;
    init();
    t.make(1, Nn);
    scanf("%d", &q);
    while(q--) {
        int mode, l, r; scanf("%d%d%d", &mode, &l, &r);
        if(mode == 1) {
            int a; scanf("%d", &a);
            t.modify(1, 1, Nn, l, r, a);
        } else printf("%d\n", t.query(1, 1, Nn, l, r));
    }
    return 0;
}
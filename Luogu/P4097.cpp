#include <bits/stdc++.h>
#define db double
using namespace std;

const int N = 40100;
const db eps = 1e-9;

int n, idx;

struct Line {db k, b; int l, r, id;};
int cmp(const Line &a, const Line &b, int x) { // a 优先级更高
    db ya = a.k * x + a.b, yb = b.k * x + b.b;
    if(ya - yb > eps) return 1;
    if(yb - ya > eps) return 0;
    return a.id < b.id;
}
struct LC_Seg_T {
    vector<Line> L;
    void cl() {L.resize(0), L.resize(N << 2);}
    void add(int rt, int l, int r, Line x) {
        if(!L[rt].id) {L[rt] = x; return;}
        int mid = l + r >> 1;
        if(cmp(x, L[rt], mid)) swap(x, L[rt]);
        if(l == r) return;
        if(cmp(x, L[rt], l)) add(rt << 1, l, mid, x);
        if(cmp(x, L[rt], r)) add(rt << 1 | 1, mid + 1, r, x);
    }
    void modify(int rt, int l, int r, Line x) {
        if(x.l <= l && x.r >= r) {
            add(rt, l, r, x);
            return;
        }
        int mid = l + r >> 1;
        if(x.l <= mid) modify(rt << 1, l, mid, x);
        if(x.r > mid) modify(rt << 1 | 1, mid + 1, r, x);
    }
    Line query(int rt, int l, int r, int x) {
        if(l == r) return L[rt];
        int mid = l + r >> 1;
        Line ans;
        if(x <= mid) ans = query(rt << 1, l, mid, x);
        else ans = query(rt << 1 | 1, mid + 1, r, x);
        if(!ans.id) return L[rt];
        if(!L[rt].id) return ans;
        return cmp(L[rt], ans, x) ? L[rt] : ans;
    }
}t;

int main() {
    t.cl();
    scanf("%d", &n);
    int Lans = 0;
    while(n--) {
        int mode; scanf("%d", &mode);
        if(mode) {
            int x, y, X, Y; scanf("%d%d%d%d", &x, &y, &X, &Y);
            x = (x + Lans - 1) % 39989 + 1, X = (X + Lans - 1) % 39989 + 1;
            y = (y + Lans - 1) % (int)1e9 + 1, Y = (Y + Lans - 1) % (int)1e9 + 1;
            db k = (x == X ? 0 : (db)(y - Y) / (x - X)), b = (x == X ? max(y, Y) : (db)y - k * x);
            Line tmp = {k, b, min(x, X), max(x, X), ++idx};
            t.modify(1, 1, N - 1, tmp);
        } else {
            int x; scanf("%d", &x); x = (x + Lans - 1) % 39989 + 1;
            printf("%d\n", Lans = t.query(1, 1, N - 1, x).id);
        }
    }
    return 0;
}
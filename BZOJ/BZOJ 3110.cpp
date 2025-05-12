#include <bits/stdc++.h>
#define Lb(x) (x & -x)
using namespace std;

const int N = 50100;

int n, m, Q, ans[N];

struct Ope {int mode, l, r, k, id;};//0修改 1询问
struct TR {
    vector<int> sum, ly;
    void cl(int n) {
        n <<= 2;
        sum.resize(0); sum.resize(n);
        ly.resize(0); ly.resize(n);
    }
    void push_up(int rt) {sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];}
    void push_down(int rt, int l, int r) {
        if(!ly[rt]) return;
        int mid = l + r >> 1;
        sum[rt << 1] += ly[rt] * (mid - l + 1);
        sum[rt << 1 | 1] += ly[rt] * (r - mid);
        ly[rt << 1] = ly[rt << 1 | 1] = ly[rt];
        ly[rt] = 0;
    }
    void modify(int rt, int l, int r, int ql, int qr, int x) {
        if(ql <= l && qr >= r) {
            sum[rt] += x * (r - l + 1);
            ly[rt] += x;
            return;
        }
        push_down(rt, l, r);
        int mid = l + r >> 1;
        if(ql <= mid) modify(rt << 1, l, mid, ql, qr, x);
        if(qr > mid) modify(rt << 1 | 1, mid + 1, r, ql, qr, x);
        push_up(rt);
    }
    int query(int rt, int l, int r, int ql, int qr) {
        if(ql <= l && qr >= r) return sum[rt];
        push_down(rt, l, r);
        int mid = l + r >> 1, ans = 0;
        if(ql <= mid) ans += query(rt << 1, l, mid, ql, qr);
        if(qr > mid) ans += query(rt << 1 | 1, mid + 1, r, ql, qr);
        return ans;
    }
    void debug(int rt, int l, int r) {
        if(l == r) {
            printf("%d ", sum[rt]);
            return;
        }
        push_down(rt, l, r);
        int mid = l + r >> 1;
        debug(rt << 1, l, mid);
        debug(rt << 1 | 1, mid + 1, r);
    }
}tr;

void solve(int l, int r, const vector<Ope> & q) {
    if(l == r || q.empty()) {
        for(Ope i : q) if(i.mode) ans[i.id] = l;
        return;
    }
    int mid = l + r >> 1;
    vector<Ope> ql, qr;
    for(Ope i : q) {
        if(i.mode) {
            int tmp = tr.query(1, 1, n, i.l, i.r);
            if(tmp >= i.k) qr.push_back(i);
            else i.k -= tmp, ql.push_back(i);
        } else {
            if(i.k > mid) tr.modify(1, 1, n, i.l, i.r, 1), qr.push_back(i);
            else ql.push_back(i);
        }
    }
    for(Ope i : qr) if(!i.mode) tr.modify(1, 1, n, i.l, i.r, -1);
    solve(l, mid, ql); solve(mid + 1, r, qr);
}

int main() {
    scanf("%d%d", &n, &m);
    tr.cl(n);
    vector<Ope> q;
    for(int i = 1; i <= m; i++) {
        int mode, a, b, c; scanf("%d%d%d%d", &mode, &a, &b, &c);
        q.push_back({mode - 1, a, b, c, (mode - 1) ? ++Q : i});
    }
    solve(-50100, 50100, q);
    for(int i = 1; i <= Q; i++) printf("%d\n", ans[i]);
    return 0;
}
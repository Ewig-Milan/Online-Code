#include <bits/stdc++.h>
#define int long long
#define real(x) dc[x - 1]
using namespace std;

const int N = 100100;

vector<int> dc;
int n, m, k, d, Nn;
struct Tasks {int x, y, v;} Q[N];
bool cmp(const Tasks &a, const Tasks &b) {return a.y < b.y;}

int f[N << 1];

// 线段树记得加一个 判 l r 合法
struct TR { // 区间加 max
    vector<int> ma, ly;
    void cl(int n) {
        ma.resize(0), ma.resize(n << 2);
        ly.resize(0), ly.resize(n << 2);
    }
    void push_up(int rt) {ma[rt] = max(ma[rt << 1], ma[rt << 1 | 1]);}
    void push_down(int rt) {
        if(!ly[rt]) return;
        ly[rt << 1] += ly[rt], ly[rt << 1 | 1] += ly[rt];
        ma[rt << 1] += ly[rt], ma[rt << 1 | 1] += ly[rt];
        ly[rt] = 0;
    }
    void modify(int rt, int l, int r, int ql, int qr, int x) {
        if(ql <= l && qr >= r) {
            ly[rt] += x, ma[rt] += x;
            return;
        }
        push_down(rt);
        int mid = l + r >> 1;
        if(ql <= mid) modify(rt << 1, l, mid, ql, qr, x);
        if(qr > mid) modify(rt << 1 | 1, mid + 1, r, ql, qr, x);
        push_up(rt);
    }
    int query(int rt, int l, int r, int ql, int qr) {
        if(ql > qr) return 0;
        if(ql <= l && qr >= r) return ma[rt];
        push_down(rt);
        int mid = l + r >> 1, ans = 0;
        if(ql <= mid) ans = query(rt << 1, l, mid, ql, qr);
        if(qr > mid) ans = max(ans, query(rt << 1 | 1, mid + 1, r, ql, qr));
        return ans;
    }
}t;

void cl() {
    dc.resize(0);
    memset(f, 0, sizeof f);
}

int nothing, T;

signed main() {
    scanf("%d%d", &nothing, &T);
    while(T--) {
        cl();
        scanf("%lld%lld%lld%lld", &n, &m, &k, &d);
        for(int i = 1; i <= m; i++) {
            scanf("%lld%lld%lld", &Q[i].x, &Q[i].y, &Q[i].v);
            dc.push_back(Q[i].x), dc.push_back(Q[i].x - Q[i].y - 1);
        }
        
        sort(dc.begin(), dc.end());
        Nn = unique(dc.begin(), dc.end()) - dc.begin();
        dc.resize(Nn), t.cl(Nn);
        for(int i = 1; i <= m; i++) {
            int tmp = lower_bound(dc.begin(), dc.end(), Q[i].x) - dc.begin() + 1;
            Q[i].x = lower_bound(dc.begin(), dc.end(), Q[i].x - Q[i].y - 1) - dc.begin() + 1;
            Q[i].y = tmp;
        }
        sort(Q + 1, Q + m + 1, cmp);

        for(int i = 1, pos = 1; i <= Nn; i++) {
            if(real(i) < 0) continue;
            while(pos <= m && Q[pos].y <= i) t.modify(1, 1, Nn, 1, Q[pos].x, Q[pos].v), pos++;

            int l = lower_bound(dc.begin(), dc.end(), real(i) - k - 1) - dc.begin() + 1;
            int r = upper_bound(dc.begin(), dc.end(), real(i) - 2) - dc.begin();
            int best = t.query(1, 1, Nn, l, r); // 回传 值

            f[i] = max(f[i - 1], best - real(i) * d);
            t.modify(1, 1, Nn, i, i, f[i] + (real(i) + 1) * d); // 区间加
        }
        printf("%lld\n", f[Nn]);
    }
    return 0;
}
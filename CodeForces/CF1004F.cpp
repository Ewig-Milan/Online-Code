#include <bits/stdc++.h>
#define ll long long
#define fi first
#define se second
using namespace std;

const int N = 100100;

int n, m, X;

struct Seg_T {
    vector<pair<int, int>> pre[N << 2], suf[N << 2]; // fi -> OR和; se -> id; 均为从中间开始（0开始）计录第一个改变的地方
    ll sum[N << 2];
    ll calc(int l, int r, vector<pair<int, int>> &pre_l, vector<pair<int, int>> &suf_l, vector<pair<int, int>> &pre_r, 
    vector<pair<int, int>> &suf_r, vector<pair<int, int>> &pre_ans, vector<pair<int, int>> &suf_ans) {
        ll res = 0;
        int pl = suf_l.size() - 1, pr = -1;
        while(pr + 1 < pre_r.size() && (suf_l[pl].fi | pre_r[pr + 1].fi) < X) pr++;
        if(pr + 1 < pre_r.size()) res += (ll)(suf_l[pl].se - l + 1) * (r - pre_r[pr + 1].se + 1);
        pl--;
        while(pl >= 0) {
            while(pr + 1 < pre_r.size() && (suf_l[pl].fi | pre_r[pr + 1].fi) < X) pr++;
            if(pr + 1 == pre_r.size()) break;
            res += (ll)(suf_l[pl].se - suf_l[pl + 1].se) * (r - pre_r[pr + 1].se + 1);
            pl--;
        }
        pre_ans = pre_l, suf_ans = suf_r;
        int tmp = pre_l.back().fi;
        for(int i = 0; i < pre_r.size(); i++) {
            if((tmp | pre_r[i].fi) != tmp)
                pre_ans.push_back({tmp |= pre_r[i].fi, pre_r[i].se});
        }
        tmp = suf_r.back().fi;
        for(int i = 0; i < suf_l.size(); i++) {
            if((tmp | suf_l[i].fi) != tmp)
                suf_ans.push_back({tmp |= suf_l[i].fi, suf_l[i].se});
        }
        return res;
    }
    void push_up(int rt, int l, int r) {
        sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
        sum[rt] += calc(l, r, pre[rt << 1], suf[rt << 1], pre[rt << 1 | 1], suf[rt << 1 | 1], pre[rt], suf[rt]);
    }
    void build(int rt, int l, int r) {
        if(l == r) {
            int a; scanf("%d", &a);
            pre[rt].clear(), pre[rt].push_back({a, l});
            suf[rt].clear(), suf[rt].push_back({a, l});
            sum[rt] = (a >= X);
            return;
        }
        int mid = l + r >> 1;
        build(rt << 1, l, mid);
        build(rt << 1 | 1, mid + 1, r);
        push_up(rt, l, r);
    }
    void modify(int rt, int l, int r, int a, int x) {
        if(l == r) {
            pre[rt].clear(), pre[rt].push_back({x, l});
            suf[rt].clear(), suf[rt].push_back({x, l});
            sum[rt] = (x >= X);
            return;
        }
        int mid = l + r >> 1;
        if(a <= mid) modify(rt << 1, l, mid, a, x);
        else modify(rt << 1 | 1, mid + 1, r, a, x);
        push_up(rt, l, r);
    }
    ll query(int rt, int l, int r, int ql, int qr, vector<pair<int, int>> &_pre, vector<pair<int, int>> &_suf, int &_l, int &_r) {
        if(ql <= l && qr >= r) {
            _l = min(_l, l), _r = max(_r, r);
            _pre = pre[rt], _suf = suf[rt];
            return sum[rt];
        }
        int mid = l + r >> 1; ll ans = 0;
        vector<pair<int, int>> pre_l, suf_l, pre_r, suf_r;
        int l_l = 1e9, l_r = 0, r_l = 1e9, r_r = 0;
        if(ql <= mid) ans += query(rt << 1, l, mid, ql, qr, pre_l, suf_l, l_l, l_r);
        if(qr > mid) ans += query(rt << 1 | 1, mid + 1, r, ql, qr, pre_r, suf_r, r_l, r_r);
        _l = min(l_l, r_l), _r = max(r_r, l_r);
        if(ql <= mid && qr > mid) ans += calc(_l, _r, pre_l, suf_l, pre_r, suf_r, _pre, _suf);
        else if(ql <= mid) _pre = pre_l, _suf = suf_l;
        else _pre = pre_r, _suf = suf_r;
        return ans;
    }
}t;

int main() {
    scanf("%d%d%d", &n, &m, &X);
    t.build(1, 1, n);
    while(m--) {
        int mode, a, b; scanf("%d%d%d", &mode, &a, &b);
        if(mode == 1) t.modify(1, 1, n, a, b);
        else {
            vector<pair<int, int>> nl, nr;
            int INFl = 1e9, INFr = 0;
            printf("%lld\n", t.query(1, 1, n, a, b, nl, nr, INFl, INFr));
        }
    }
    return 0;
}
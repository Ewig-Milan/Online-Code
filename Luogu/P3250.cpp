//
// 二分答案 >mid 的计算 然后看每个点权值是否 == 计算的所有 -> 放到左边 : 放到右边
//
#include <bits/stdc++.h>
#define Lb(x) (x & -x)
using namespace std;

const int N = 100100, M = 200100;

int n, m, q_cnt, ans[M];

int h[N], e[N << 1], ne[N << 1], idx;
void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++;}

struct Ope {bool mode; int a, b, v, k, id;} Q[M]; // 1询问 0修改

struct Bit_T {
    int sum[N];
    void chg(int x, int delta) {
        if(!x) x = 1;
        while(x <= n) sum[x] += delta, x += Lb(x);
    }

    void modify(int l, int r, int x) {chg(l, x); chg(r + 1, -x);}

    int query(int x) {
        int res = 0;
        while(x) res += sum[x], x -= Lb(x);
        return res;
    }
}t;

int cnt, L[N], R[N], tp[N], siz[N], ma_s[N], dep[N], fa[N];

void dfs_pre(int x, int l) {
    siz[x] = 1, dep[x] = dep[l] + 1, fa[x] = l;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        dfs_pre(j, x);
        siz[x] += siz[j];
        if(siz[ma_s[x]] < siz[j]) ma_s[x] = j;
    }
}

void get_tp(int x, int l, int top) {
    tp[x] = top, L[x] = ++cnt;
    if(ma_s[x]) get_tp(ma_s[x], x, top);
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l || j == ma_s[x]) continue;
        get_tp(j, x, j);
    }
    R[x] = cnt;
}

void modify(int x, int y, int a) {
    while(tp[x] != tp[y]) {
        if(dep[tp[x]] < dep[tp[y]]) swap(x, y);
        t.modify(L[tp[x]], L[x], a);
        x = fa[tp[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    t.modify(L[y], L[x], a);
}

int query(int x) {return t.query(L[x]);}

void solve(int l, int r, vector<int> & q) {
    if(l == r || q.empty()) {
        for(int i : q) if(Q[i].mode) ans[Q[i].id] = l;
        return;
    }
    int mid = l + r >> 1, tmp_cnt = 0;
    vector<int> ql, qr;
    for(int i : q) {
        if(Q[i].mode) {
            int tmp = query(Q[i].a);
            if(tmp == tmp_cnt) ql.push_back(i);
            else qr.push_back(i);
        } else {
            if(Q[i].v <= mid) ql.push_back(i);
            else modify(Q[i].a, Q[i].b, Q[i].k), qr.push_back(i), tmp_cnt += Q[i].k;
        }
    }
    for(int i : qr) if(!Q[i].mode) modify(Q[i].a, Q[i].b, -Q[i].k);
    solve(l, mid, ql); solve(mid + 1, r, qr);
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for(int i = 1; i < n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        add(a, b); add(b, a);
    }
    dfs_pre(1, 0);
    get_tp(1, 0, 1);
    vector<int> q;
    for(int i = 1; i <= m; i++) {
        q.push_back(i);
        int mode; scanf("%d", &mode);
        if(mode == 2) {
            int a; scanf("%d", &a);
            Q[i] = {1, a, 0, 0, 0, ++q_cnt};
        } else if(!mode) {
            int a, b, c; scanf("%d%d%d", &a, &b, &c);
            Q[i] = {0, a, b, c, 1, 0};
        } else {
            int a; scanf("%d", &a);
            Q[i] = Q[a];
            Q[i].k = -1;
        }
    }
    solve(0, 1e9, q);
    for(int i = 1; i <= q_cnt; i++) printf("%d\n", ans[i] ? ans[i] : -1);
    return 0;
}
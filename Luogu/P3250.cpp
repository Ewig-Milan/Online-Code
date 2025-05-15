//
// 之前可悲地跑了2.3s 所以我愤怒地卡了个常
//
// 二分答案 >mid 的计算 然后看每个点权值是否 == 计算的所有 -> 放到左边 : 放到右边
//
#include <bits/stdc++.h>
#define Lb(x) (x & -x)
using namespace std;

inline int rd() {
    int x = 0; char ch = getchar();
    while(ch < 48 || ch > 57) ch = getchar();
    while(ch >= 48 && ch <= 57) x = x * 10 + ch - 48, ch = getchar();
    return x;
}

const int N = 100100, M = 200100;

vector<int> dc;

int n, m, q_cnt, ans[M];

int h[N], e[N << 1], ne[N << 1], idx;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ne[idx] = h[b], h[b] = idx++;
}

struct Ope {bool mode; int a, b, v, k, id;} Q[M]; // 1询问 0修改

struct Bit_T {
    int sum[N];
    void modify(int x, int delta) {while(x && x <= n) sum[x] += delta, x += Lb(x);}
    int presum(int x) {
        int res = 0;
        while(x) res += sum[x], x -= Lb(x);
        return res;
    }
    int query(int l, int r) {return presum(r) - presum(l - 1);}
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

int LCA(int x, int y) {
    while(tp[x] != tp[y]) {
        if(dep[tp[x]] < dep[tp[y]]) swap(x, y);
        x = fa[tp[x]];
    }
    return dep[x] >= dep[y] ? y : x;
}

void modify(int x, int y, int a) {
    int lca = LCA(x, y);
    t.modify(L[x], a); t.modify(L[y], a);
    t.modify(L[lca], -a); t.modify(L[fa[lca]], -a);
}

int query(int x) {return t.query(L[x], R[x]);}

void solve(int l, int r, vector<int> & q) {
    if(l == r || q.empty()) {
        for(int i : q) if(Q[i].mode) ans[Q[i].id] = dc[l];
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
            if(Q[i].v <= dc[mid]) ql.push_back(i);
            else modify(Q[i].a, Q[i].b, Q[i].k), qr.push_back(i), tmp_cnt += Q[i].k;
        }
    }
    for(int i : qr) if(!Q[i].mode) modify(Q[i].a, Q[i].b, -Q[i].k);
    solve(l, mid, ql); solve(mid + 1, r, qr);
}

int main() {
    memset(h, -1, sizeof h);
    n = rd(), m = rd();
    for(int i = 1; i < n; i++) add(rd(), rd());
    dfs_pre(1, 0);
    get_tp(1, 0, 1);
    vector<int> q;
    for(int i = 1; i <= m; i++) {
        q.push_back(i);
        int mode = rd();
        if(mode == 2) Q[i] = {1, rd(), 0, 0, 0, ++q_cnt};
        else if(!mode) Q[i] = {0, rd(), rd(), rd(), 1, 0}, dc.push_back(Q[i].v);
        else Q[i] = Q[rd()], Q[i].k = -1;
    }
    dc.push_back(0);
    sort(dc.begin(), dc.end());
    dc.resize(unique(dc.begin(), dc.end()) - dc.begin());
    solve(0, dc.size() - 1, q);
    for(int i = 1; i <= q_cnt; i++) printf("%d\n", ans[i] ? ans[i] : -1);
    return 0;
}
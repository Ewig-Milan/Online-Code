#include <bits/stdc++.h>
#define M(x) ((x) % n + 1)
#define PII pair<int, int>
#define fi first
#define se second
using namespace std;

const int N = 200100;

int n, m;
void solve() {bool ans = 0; while(m--) {int a, b, c; scanf("%d%d%d", &a, &b, &c); if(a == 1) ans ^= 1; else printf("%d", ans);}}

map<PII, vector<PII>> cut; // 时间点 / 为()时启用
int idx;
bool start[N << 2]; // 是否第一个
bool op[N << 2]; // last_ans 为()时启用
int use[N << 2]; // 是否已经启用

struct Qu {int a, b;} Q[N];

int fa[N], siz[N];
stack<int> S;
int find(int x) {return x == fa[x] ? x : find(fa[x]);}
void merge(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) {S.push(0); return;}
    if(siz[a] > siz[b]) swap(a, b);
    fa[a] = b, siz[b] += siz[a], S.push(a);
}
void undo() {
    if(!S.top()) {S.pop(); return;}
    siz[fa[S.top()]] -= siz[S.top()];
    fa[S.top()] = S.top(), S.pop();
}

struct Seg_T {
    struct Edge {int a, b, id;};
    vector<Edge> E[N << 2];
    void add(int rt, int l, int r, int ql, int qr, Edge x) {
        if(ql <= l && qr >= r) {
            E[rt].push_back(x);
            return;
        }
        int mid = l + r >> 1;
        if(ql <= mid) add(rt << 1, l, mid, ql, qr, x);
        if(qr > mid) add(rt << 1 | 1, mid + 1, r, ql, qr, x);
    }
    void dfs(int rt, int l, int r, int &lst) {
        for(auto &x : E[rt]) {
            if(use[x.id] == -1) {
                if(start[x.id] || !use[x.id - 1]) use[x.id] = (op[x.id] == lst);
                else use[x.id] = (op[x.id] != lst);
            }
            if(use[x.id]) merge(x.a, x.b);
        }
        if(l == r) {
            if(Q[l].a) {
                int a = Q[l].a, b = Q[l].b;
                if(lst) a = M(a), b = M(b);
                lst = (find(a) == find(b));
                printf("%d", lst);
            }
        } else {
            int mid = l + r >> 1;
            dfs(rt << 1, l, mid, lst);
            dfs(rt << 1 | 1, mid + 1, r, lst);
        }
        for(auto &x : E[rt]) if(use[x.id]) undo();
    }
}t;

int main() {
    scanf("%d%d", &n, &m);
    if(n == 2) {solve(); return 0;}
    for(int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
    memset(use, -1, sizeof use);

    for(int i = 1; i <= m; i++) {
        int mode, a, b; scanf("%d%d%d", &mode, &a, &b);
        int a_ = M(a), b_ = M(b);
        if(a > b) swap(a, b);
        if(a_ > b_) swap(a_, b_);
        if(mode == 1) {
            cut[{a, b}].push_back({i, 0});
            cut[{a_, b_}].push_back({i, 1});
        } else Q[i] = {a, b};
    }
    for(auto x : cut) {
        int a = x.fi.fi, b = x.fi.se;
        x.se.push_back({m + 1, 0});
        for(int l = 0, r = 1; r < x.se.size(); l++, r++) {
            idx++, op[idx] = x.se[l].se;
            t.add(1, 1, m, x.se[l].fi, x.se[r].fi - 1, {a, b, idx});
            if(l == 0) start[idx] = 1;
        }
    }
    int lst_ans = 0;
    t.dfs(1, 1, m, lst_ans);
    return 0;
}
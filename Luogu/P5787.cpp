#include <bits/stdc++.h>
using namespace std;

const int N = 100100;

int n, m, k;
struct Edge {int a, b;};

int fa[N << 1], siz[N << 1];
stack<int> S;
int find(int x) {return x == fa[x] ? x : find(fa[x]);}
void merge(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) {S.push(0); return;}
    if(siz[a] > siz[b]) swap(a, b);
    fa[a] = b, S.push(a), siz[b] += siz[a];
}
void undo() {
    if(!S.top()) {S.pop(); return;}
    siz[fa[S.top()]] -= siz[S.top()];
    fa[S.top()] = S.top(), S.pop();
}

struct Seg_T {
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
    void dfs(int rt, int l, int r, bool ans) {
        for(auto x : E[rt]) {
            merge(x.a, x.b + n);
            merge(x.a + n, x.b);
            ans &= (find(x.a) != find(x.a + n));
        }
        if(l == r) puts(ans ? "Yes" : "No");
        else {
            int mid = l + r >> 1;
            dfs(rt << 1, l, mid, ans);
            dfs(rt << 1 | 1, mid + 1, r, ans);
        }
        int cnt = (int)E[rt].size() * 2;
        while(cnt--) undo();
    }
}t;

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= (n << 1); i++) fa[i] = i, siz[i] = 1;
    while(m--) {
        int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);
        if(c == d) continue;
        t.add(1, 1, k, c + 1, d, {a, b});
    }
    t.dfs(1, 1, k, 1);
    return 0;
}
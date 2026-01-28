#include <bits/stdc++.h>
using namespace std;

const int N = 500100;

int seed = 0xABC3DD;
int rnd() {return seed = seed * 3 % 11762797;}

int n;

int root[N];
struct Node {int l, r, x, siz, key;} t[N * 60];
int tot;
int make(int x) {
    t[++tot] = {0, 0, x, 1, rnd()};
    return tot;
}
int clone(int rt) {
    t[++tot] = t[rt];
    return tot;
}
void push_up(int rt) {
    int &lc = t[rt].l, &rc = t[rt].r;
    t[rt].siz = 1 + t[lc].siz + t[rc].siz;
}
void split(int rt, int k, int &x, int &y) {
    if(!rt) {x = y = 0; return;}
    rt = clone(rt);
    int &lc = t[rt].l, &rc = t[rt].r;
    if(t[rt].x <= k) x = rt, split(rc, k, rc, y);
    else y = rt, split(lc, k, x, lc);
    push_up(rt);
}
int merge(int x, int y) {
    if(!x || !y) return max(x, y);
    if(t[x].key <= t[y].key) {
        x = clone(x);
        t[x].r = merge(t[x].r, y);
        push_up(x);
        return x;
    } else {
        y = clone(y);
        t[y].l = merge(x, t[y].l);
        push_up(y);
        return y;
    }
}
int find(int rt, int k) {
    int &lc = t[rt].l, &rc = t[rt].r;
    if(t[lc].siz + 1 == k) return rt;
    if(t[lc].siz + 1 > k) return find(lc, k);
    return find(rc, k - t[lc].siz - 1);
}

int ins(int rt, int x) {
    int t1, t2;
    split(rt, x - 1, t1, t2);
    return merge(merge(t1, make(x)), t2);
}
int del(int rt, int x) {
    int t1, t2, t3;
    split(rt, x - 1, t1, t2);
    split(t2, x, t2, t3);
    t2 = merge(t[t2].l, t[t2].r);
    return merge(merge(t1, t2), t3);
}
int get_rk(int rt, int x) {
    int t1, t2;
    split(rt, x - 1, t1, t2);
    int res = t[t1].siz;
    merge(t1, t2);
    return res;
}
int get_kth(int rt, int k) {return t[find(rt, k + 1)].x;}
int pre(int rt, int x) {
    int t1, t2;
    split(rt, x - 1, t1, t2);
    int res = t[find(t1, t[t1].siz)].x;
    merge(t1, t2);
    return res;
}
int nxt(int rt, int x) {
    int t1, t2;
    split(rt, x, t1, t2);
    int res = t[find(t2, 1)].x;
    merge(t1, t2);
    return res;
}

int main() {
    scanf("%d", &n);
    root[0] = merge(make(-(1ll << 31 - 1)), make((1ll << 31) - 1));
    for(int i = 1; i <= n; i++) {
        int v, mode, a, ans; scanf("%d%d%d", &v, &mode, &a);
        root[i] = v = root[v];
        if(mode == 1) root[i] = ins(v, a);
        if(mode == 2) root[i] = del(v, a);
        if(mode == 3) ans = get_rk(v, a);
        if(mode == 4) ans = get_kth(v, a);
        if(mode == 5) ans = pre(v, a);
        if(mode == 6) ans = nxt(v, a);
        if(mode > 2) printf("%d\n", ans);
    }
    return 0;
}
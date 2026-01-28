#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 200100;

int anywhere_with_xh=24/7*365;
int rnd() {return anywhere_with_xh = anywhere_with_xh * 97 % 11762797;}

int n;

int root[N];
struct Node {
    int l, r, x, key;
    ll sum; int siz;
    bool rev;
}t[N * 100];
int tot;
int make(int x) {
    t[++tot] = {0, 0, x, rnd(), x, 1, 0};
    return tot;
}
int clone(int rt) {
    t[++tot] = t[rt];
    return tot;
}
void push_up(int rt) {
    int &lc = t[rt].l, &rc = t[rt].r;
    t[rt].sum = t[lc].sum + t[rc].sum + t[rt].x;
    t[rt].siz = t[lc].siz + t[rc].siz + 1;
}
void push_down(int rt) {
    if(!t[rt].rev) return;
    int &lc = t[rt].l, &rc = t[rt].r;
    if(lc) lc = clone(lc), t[lc].rev ^= 1, swap(t[lc].l, t[lc].r);
    if(rc) rc = clone(rc), t[rc].rev ^= 1, swap(t[rc].l, t[rc].r);
    t[rt].rev = 0;
}
void split(int rt, int k, int &x, int &y) {
    if(!rt) {x = y = 0; return;}
    rt = clone(rt), push_down(rt);
    int &lc = t[rt].l, &rc = t[rt].r;
    if(t[lc].siz + 1 <= k) x = rt, split(rc, k - t[lc].siz - 1, rc, y);
    else y = rt, split(lc, k, x, lc);
    push_up(rt);
}
int merge(int x, int y) {
    if(!x || !y) return max(x, y);
    if(t[x].key <= t[y].key) {
        x = clone(x), push_down(x);
        t[x].r = merge(t[x].r, y);
        push_up(x);
        return x;
    } else {
        y = clone(y), push_down(y);
        t[y].l = merge(x, t[y].l);
        push_up(y);
        return y;
    }
}

int ins(int rt, int a, int x) {
    int t1, t2;
    split(rt, a, t1, t2);
    return merge(merge(t1, make(x)), t2);
}
int del(int rt, int a) {
    int t1, t2, t3;
    split(rt, a - 1, t1, t2);
    split(t2, 1, t2, t3);
    return merge(t1, t3);
}
int rev(int rt, int l, int r) {
    int t1, t2, t3;
    split(rt, l - 1, t1, t2);
    split(t2, r - l + 1, t2, t3);
    swap(t[t2].l, t[t2].r), t[t2].rev ^= 1;
    return merge(merge(t1, t2), t3);
}
ll query(int rt, int l, int r) {
    int t1, t2, t3;
    split(rt, l - 1, t1, t2);
    split(t2, r - l + 1, t2, t3);
    ll res = t[t2].sum;
    merge(merge(t1, t2), t3);
    return res;
}

int main() {
    scanf("%d", &n);
    ll Lans = 0;
    for(int i = 1; i <= n; i++) {
        int v, mode; scanf("%d%d", &v, &mode);
        root[i] = v = root[v];
        if(mode == 2) {
            int a; scanf("%d", &a), a ^= Lans;
            root[i] = del(v, a);
        } else {
            int a, b; scanf("%d%d", &a, &b), a ^= Lans, b ^= Lans;
            if(mode == 1) root[i] = ins(v, a, b);
            else if(mode == 3) root[i] = rev(v, a, b);
            else printf("%lld\n", Lans = query(v, a, b));
        }
    }
    return 0;
}
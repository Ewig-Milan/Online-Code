#include <bits/stdc++.h>
using namespace std;

int seed = 0xABCDEF;
int rnd() {return seed = seed * 97 % 11762797;}

const int N = 300100;

int n, L[N], R[N];

int root, tot;
struct Node {int l, r, x, siz, key, add;} t[N * 30];
int make(int x) {
    t[++tot] = {0, 0, x, 1, rnd(), 0};
    return tot;
}
void D_add(int rt, int x) {
    if(!rt) return;
    t[rt].add += x, t[rt].x += x;
}
void push_up(int rt) {
    int &lc = t[rt].l, &rc = t[rt].r;
    t[rt].siz = t[lc].siz + t[rc].siz + 1;
}
void push_down(int rt) {
    int &lc = t[rt].l, &rc = t[rt].r;
    if(!t[rt].add) return;
    D_add(lc, t[rt].add), D_add(rc, t[rt].add);
    t[rt].add = 0;
}
void split(int rt, int k, int &x, int &y) {
    int &lc = t[rt].l, &rc = t[rt].r;
    if(!rt) {x = y = 0; return;}
    push_down(rt);
    if(t[rt].x <= k) x = rt, split(rc, k, rc, y);
    else y = rt, split(lc, k, x, lc);
    push_up(rt);
}
void split_(int rt, int k, int &x, int &y) {
    if(!rt) {x = y = 0; return;}
    push_down(rt);
    int &lc = t[rt].l, &rc = t[rt].r;
    if(t[lc].siz + 1 <= k) x = rt, split_(rc, k - t[lc].siz - 1, rc, y);
    else y = rt, split_(lc, k, x, lc);
    push_up(rt);
}
int merge(int x, int y) {
    if(!x || !y) return max(x, y);
    if(t[x].key <= t[y].key) {
        push_down(x);
        t[x].r = merge(t[x].r, y);
        push_up(x);
        return x;
    } else {
        push_down(y);
        t[y].l = merge(x, t[y].l);
        push_up(y);
        return y;
    }
}

void work(int l, int r) {
    int t1, t2, t3, t4;
    split(root, l - 1, t1, t2);
    split(t2, r - 1, t2, t3);
    split_(t3, 1, t3, t4);
    D_add(t2, 1);
    root = merge(merge(t1, make(l)), merge(t2, t4));
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d%d", &L[i], &R[i]);
    for(int i = 1; i <= n; i++) work(L[i], R[i]);
    printf("%d", t[root].siz);
    return 0;
}
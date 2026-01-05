#include <bits/stdc++.h>
#define db double
using namespace std;

const db eps = 1e-10;

int n, m;

struct TR {
    vector<db> ma;
    vector<int> up;
    void cl(int x) {
        ma.resize(x << 2), up.resize(x << 2);
        for(int i = 0; i < (x << 2); i++) ma[i] = up[i] = 0;
    }
    int D(db rma, int rt) {
        if(up[rt] <= 1) return ma[rt] > rma + eps;
        if(ma[rt << 1] > rma + eps) return D(rma, rt << 1) + up[rt] - up[rt << 1];
        else return D(rma, rt << 1 | 1);
    }
    void push_up(int rt) {
        ma[rt] = max(ma[rt << 1], ma[rt << 1 | 1]);
        up[rt] = up[rt << 1] + D(ma[rt << 1], rt << 1 | 1);
    }
    void modify(int rt, int l, int r, int a, db x) {
        if(l == r) {
            ma[rt] = x, up[rt] = 1;
            return;
        }
        int mid = l + r >> 1;
        if(a <= mid) modify(rt << 1, l, mid, a, x);
        else modify(rt << 1 | 1, mid + 1, r, a, x);
        push_up(rt);
    }
}t;

int main() {
    scanf("%d%d", &n, &m);
    t.cl(n);
    while(m--) {
        int a, b; scanf("%d%d", &a, &b);
        t.modify(1, 1, n, a, (db)b / a);
        printf("%d\n", t.up[1]);
    }
    return 0;
}
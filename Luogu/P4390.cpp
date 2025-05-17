#include <bits/stdc++.h>
#define Lb(x) (x & -x)
using namespace std;

const int N = 2400100;

int n, m, q, ans[N];
struct Node {bool mode; int x, y, k, id;} Q[N], tmp[N]; // 0修改 1询问
int tmp_cnt;

struct Bit_T {
    int sum[2000100];
    void modify(int x, int delta) {x++; while(x - 1 <= n) sum[x] += delta, x += Lb(x);}
    int query(int x) {
        x++;
        int res = 0;
        while(x) res += sum[x], x -= Lb(x);
        return res;
    }
}t;

void solve(int l, int r) {
    if(l == r) return;
    int mid = l + r >> 1;
    solve(l, mid); solve(mid + 1, r); // 按 x 排好序了
    int i = l, j = mid + 1; // 左边修改 右边加
    tmp_cnt = 0;
    while(i <= mid && j <= r)
        if(Q[i].x <= Q[j].x) {
            if(!Q[i].mode) t.modify(Q[i].y, Q[i].k);
            tmp[++tmp_cnt] = Q[i++];
        } else {
            if(Q[j].mode) ans[Q[j].id] += Q[j].k * t.query(Q[j].y);
            tmp[++tmp_cnt] = Q[j++];
        }
    while(i <= mid) {
        if(!Q[i].mode) t.modify(Q[i].y, Q[i].k);
        tmp[++tmp_cnt] = Q[i++];
    }
    while(j <= r) {
        if(Q[j].mode) ans[Q[j].id] += Q[j].k * t.query(Q[j].y);
        tmp[++tmp_cnt] = Q[j++];
    }
    for(int i = l; i <= mid; i++) if(!Q[i].mode) t.modify(Q[i].y, -Q[i].k);
    for(int i = 1; i <= tmp_cnt; i++) Q[i + l - 1] = tmp[i];
}

int main() {
    int nothing;
    scanf("%d%d", &nothing, &n);
    while(true) {
        int mode; scanf("%d", &mode);
        if(mode == 3) break;
        int x, y; scanf("%d%d", &x, &y);
        if(mode == 1) {
            int a; scanf("%d", &a);
            Q[++m] = {0, x, y, a, 0};
        } else {
            int X, Y; scanf("%d%d", &X, &Y);
            Q[++m] = {1, x - 1, y - 1, 1, ++q};
            Q[++m] = {1, X, Y, 1, q};
            Q[++m] = {1, X, y - 1, -1, q};
            Q[++m] = {1, x - 1, Y, -1, q};
        }
    }
    solve(1, m);
    for(int i = 1; i <= q; i++) printf("%d\n", ans[i]);
    return 0;
}
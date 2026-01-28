#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 50100, M = 21, mod = 19940417;

int n, q;
int C[N][M];
void pre() {
    C[0][0] = 1;
    for(int i = 1; i < N; i++) {
        C[i][0] = 1;
        if(i < M) C[i][i] = 1;
        for(int j = 1; j < M && j < i; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }
}

struct TR {
    vector<int> S[N << 2], add, rev;
    void cl() {
        add.resize(N << 2), rev.resize(N << 2);
        for(int i = 0; i < (N << 2); i++) S[i].resize(M, 0), add[i] = rev[i] = 0;
    }
    void push_up(const vector<int> &A, const vector<int> &B, vector<int> &C) {
        for(int c = 0; c < M; c++) {
            int res = 0;
            for(int i = 0; i <= c; i++) res += A[i] * B[c - i] % mod, res %= mod;
            C[c] = res;
        }
    }
    void build(int rt, int l, int r) {
        if(l == r) {
            scanf("%lld", &S[rt][1]), S[rt][1] %= mod;
            S[rt][0] = 1;
            return;
        }
        int mid = l + r >> 1;
        build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
        push_up(S[rt << 1], S[rt << 1 | 1], S[rt]);
    }
    void D_add(int rt, int L, int x) {
        add[rt] += x, add[rt] %= mod;
        for(int c = M - 1; c >= 0; c--) {
            int res = 0, tmp = 1;
            for(int i = 0; i <= c; i++) {
                res += tmp * S[rt][c - i] % mod * C[L - c + i][i] % mod;
                res %= mod;
                tmp = tmp * x % mod;
            }
            S[rt][c] = res;
        }
    }
    void D_rev(int rt) {
        rev[rt] ^= 1, add[rt] *= -1;
        for(int i = 1; i < M; i += 2) S[rt][i] *= -1;
    }
    void push_down(int rt, int l, int r) {
        if(!rev[rt] && !add[rt]) return;
        if(rev[rt]) D_rev(rt << 1), D_rev(rt << 1 | 1), rev[rt] = 0;
        int mid = l + r >> 1;
        D_add(rt << 1, mid - l + 1, add[rt]), D_add(rt << 1 | 1, r - mid, add[rt]);
        add[rt] = 0;
    }
    void modify_I(int rt, int l, int r, int ql, int qr, int x) {
        if(ql <= l && qr >= r) {
            D_add(rt, r - l + 1, x);
            return;
        }
        push_down(rt, l, r);
        int mid = l + r >> 1;
        if(ql <= mid) modify_I(rt << 1, l, mid, ql, qr, x);
        if(qr > mid) modify_I(rt << 1 | 1, mid + 1, r, ql, qr, x);
        push_up(S[rt << 1], S[rt << 1 | 1], S[rt]);
    }
    void modify_R(int rt, int l, int r, int ql, int qr) {
        if(ql <= l && qr >= r) {
            D_rev(rt);
            return;
        }
        push_down(rt, l, r);
        int mid = l + r >> 1;
        if(ql <= mid) modify_R(rt << 1, l, mid, ql, qr);
        if(qr > mid) modify_R(rt << 1 | 1, mid + 1, r, ql, qr);
        push_up(S[rt << 1], S[rt << 1 | 1], S[rt]);
    }
    void query(int rt, int l, int r, int ql, int qr, vector<int> &ans) {
        if(ql <= l && qr >= r) {
            ans = S[rt];
            return;
        }
        push_down(rt, l, r);
        int mid = l + r >> 1;
        vector<int> t1(M), t2(M); t1[0] = t2[0] = 1;
        if(ql <= mid) query(rt << 1, l, mid, ql, qr, t1);
        if(qr > mid) query(rt << 1 | 1, mid + 1, r, ql, qr, t2);
        push_up(t1, t2, ans);
    }
}t;

signed main() {
    pre();
    scanf("%lld%lld", &n, &q);
    t.cl(), t.build(1, 1, n);
    while(q--) {
        char mode[5]; scanf("%s", mode);
        int a, b; scanf("%lld%lld", &a, &b);
        if(mode[0] == 'I') {
            int c; scanf("%lld", &c);
            t.modify_I(1, 1, n, a, b, c);
        } else if(mode[0] == 'Q') {
            int c; scanf("%lld", &c);
            vector<int> ans(M);
            t.query(1, 1, n, a, b, ans);
            printf("%lld\n", (ans[c] + mod) % mod);
        } else t.modify_R(1, 1, n, a, b);
    }
    return 0;
}
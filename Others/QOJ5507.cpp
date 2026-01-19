#include <bits/stdc++.h>
#define Lb(x) (x) & (-(x))
using namespace std;

const int N = 6100;

int n, K;
int A[N];
int q[N][N];
int f[N][N];

struct Bit_T {
    int sum[N];
    void cl() {memset(sum, 0, sizeof sum);}
    void modify(int x, int delta) {
        while(x < N) sum[x] += delta, x += Lb(x);
    }
    int query(int x) {
        int res = 0;
        while(x) res += sum[x], x -= Lb(x);
        return res;
    }

}t;

void solve(int ql, int qr, int l, int r, int j) {
    if(ql > qr) return;
    int mi = 1e9, mi_id = 0;
    int mid = ql + qr >> 1;
    for(int i = l; i <= min(r, mid - 1); i++)
        if(f[i][j - 1] + q[i + 1][mid] < mi) mi = f[i][j - 1] + q[i + 1][mid], mi_id = i;
    f[mid][j] = mi;
    solve(ql, mid - 1, l, mi_id, j), solve(mid + 1, qr, mi_id, r, j);
}

int main() {
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &K);
        K = min(n, K + 1);
        vector<int> dc;
        for(int i = 1; i <= n; i++) scanf("%d", &A[i]), dc.push_back(A[i]);
        sort(dc.begin(), dc.end());
        dc.resize(unique(dc.begin(), dc.end()) - dc.begin());
        for(int i = 1; i <= n; i++) {
            A[i] = lower_bound(dc.begin(), dc.end(), A[i]) - dc.begin() + 1;
            t.cl();
            for(int j = i; j; j--) q[j][i] = 0;
            for(int j = i; j; j--) q[j][i] = q[j + 1][i] + t.query(A[j]), t.modify(A[j] + 1, 1);
        }
        for(int i = 1; i <= n; i++) f[i][1] = q[1][i];
        for(int j = 2; j <= K; j++) solve(1, n, 1, n, j);
        printf("%d\n", f[n][K]);
    }
    return 0;
}
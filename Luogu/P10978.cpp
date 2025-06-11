#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 32100, K = 110;

struct Node {
	int s, l, p;
	friend bool operator < (const Node & a, const Node & b) {
		return a.s < b.s;
	}
}Q[K];

int k, n;
int S[K], L[K], P[K];
int f[K][N];

signed main() {
    scanf("%lld%lld", &n, &k);
    for(int i = 1; i <= k; i++) scanf("%lld%lld%lld", &Q[i].l, &Q[i].p, &Q[i].s);
	sort(Q + 1, Q + k + 1);	
	for(int i = 1; i <= k; i++) L[i] = Q[i].l, P[i] = Q[i].p, S[i] = Q[i].s;

    for(int i = 0; i <= k; i++) for(int j = 0; j <= n; j++) f[i][j] = -2e9;
    f[0][0] = 0;
    for(int i = 1; i <= k; i++) {
        f[i][0] = 0;
        for(int j = S[i] + L[i] - 1, ma = -2e9; j >= S[i]; j--) {
            if(j >= L[i]) ma = max(ma, f[i - 1][j - L[i]] - P[i] * (j - L[i]));
            f[i][j] = max(P[i] * j + ma, f[i - 1][j]);
            printf("f[%lld][%lld] = %lld\n", i, j, f[i][j]);
        }
    }
    printf("%lld", f[k][n]);
    return 0;
}
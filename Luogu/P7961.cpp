#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 32, M = 102, mod = 998244353;

int n, m, K;
int v[M];
int f[M][N][N][N >> 1];

int po[M][N], C[N][N];
void prepare() {
    for(int i = 0; i <= m; i++) {
        po[i][0] = 1;
        for(int j = 1; j <= n; j++) po[i][j] = po[i][j - 1] * v[i] % mod;
    }
    for(int i = 0; i < N; i++) C[i][0] = 1;
    for(int i = 1; i < N; i++)
    for(int j = 1; j <= i; j++)
        C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
}

int overflow(int p) {
    int res = 0;
    while(p) res += (p & 1), p >>= 1;
    return res;
}

signed main() {
    scanf("%lld%lld%lld", &n, &m, &K);
    for(int i = 0; i <= m; i++) scanf("%lld", &v[i]);
    prepare();
    f[0][0][0][0] = 1;
    for(int i = 0; i <= m; i++)
    for(int j = 0; j <= n; j++)
    for(int k = 0; k <= K; k++)
    for(int p = 0; p <= (n >> 1); p++)
    for(int t = 0; j + t <= n; t++)
        f[i + 1][j + t][k + (t + p & 1)][(t + p) >> 1]
        += f[i][j][k][p] * po[i][t] % mod * C[n - j][t] % mod, 
        f[i + 1][j + t][k + (t + p & 1)][(t + p) >> 1] %= mod;
    
    int ans = 0;
    for(int k = 0; k <= K; k++) for(int p = 0; p <= (n >> 1); p++)
        if(k + overflow(p) <= K) ans += f[m + 1][n][k][p], ans %= mod;

    printf("%lld", ans);
    return 0;
}
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 51, mod = 1e9 + 7;

int n, m, ans;
int h[N], f[N][N], g[N][N][N];
int C[N][N], pw[N][N], pw2[N * N];

void pre() {
    memset(f, -1, sizeof f);
    memset(g, -1, sizeof g);
    memset(h, -1, sizeof h);
    for(int i = 0; i < N; i++)
    for(int j = 0; j <= i; j++)
        if(!j || i == j) C[i][j] = 1;
        else C[i][j] = C[i - 1][j] + C[i - 1][j - 1], C[i][j] %= mod;
    for(int i = 1; i < N; i++) {
        pw[i][0] = 1;
        for(int j = 1; j < N; j++) pw[i][j] = pw[i][j - 1] * i, pw[i][j] %= mod;
    }
    pw2[0] = 1;
    for(int i = 1; i < N * N; i++) pw2[i] = pw2[i - 1] * 2, pw2[i] %= mod;
}

int F(int i, int j);
int H(int i);
int G(int i, int j, int k);

int F(int i, int j) {
    if(j >= i) return 0;
    if(i <= 1) return 1;
    if(f[i][j] != -1) return f[i][j];
    if(!j) {
        int tmp = H(i);
        for(int k = 1; k <= i - 1; k++) tmp -= F(i, k), tmp %= mod;
        f[i][j] = (tmp + mod) % mod;
        return f[i][j];
    }
    int res = 0;
    for(int k = 1; k <= i - 1; k++) {
        int tmp = 0;
        for(int x = 1; x <= min(i - k, j); x++)
            tmp += G(i - k, j - x, x) * pw[k][x], tmp %= mod;
        tmp *= C[i - 1][k - 1] * F(k, 0) % mod, tmp %= mod;
        res += tmp, res %= mod;
    }
    f[i][j] = res;
    return f[i][j];
}

int G(int i, int j, int k) {
    if(j > i - k || i < k || k < 0) return 0;
    if(i == k) return 1;
    if(g[i][j][k] != -1) return g[i][j][k];
    int res = 0;
    for(int p = 1; p <= i - k + 1; p++) {
        int tmp = 0;
        for(int q = 0; q <= j; q++) {
            int t1 = F(p, q) * C[i - 1][p - 1] % mod;
            t1 *= p, t1 %= mod, t1 *= G(i - p, j - q, k - 1), t1 %= mod;
            tmp += t1, tmp %= mod;
        }
        res += tmp, res %= mod;
    }
    g[i][j][k] = res;
    return g[i][j][k];
}

int H(int i) {
    if(h[i] != -1) return h[i];
    int res = pw2[i * (i - 1) / 2];
    for(int k = 1; k <= i - 1; k++) {
        int tmp = H(k) * C[i - 1][k - 1] % mod;
        tmp *= pw2[(i - k) * (i - k - 1) / 2], tmp %= mod;
        res -= tmp, res %= mod;
    }
    h[i] = (res + mod) % mod;
    return h[i];
}

signed main() {
    pre();
    scanf("%lld%lld", &n, &m);
    m = min(m, n - 1);
    for(int i = 0; i <= m; i++) ans += F(n, i), ans %= mod;
    printf("%lld", ans);
    return 0;
}
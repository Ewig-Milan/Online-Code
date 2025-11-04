#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 600, mod = 998244353;

int n, m;
char s[N];
int c[N], rm[N];

int f[2][N][N];
int ans;

int fac[N], C[N][N], P[N][N];
void prepare() {
    fac[0] = 1;
    for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
    for(int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for(int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
        for(int j = 0; j <= i; j++) P[i][j] = C[i][j] * fac[j] % mod;
    }
}

signed main() {
    scanf("%lld%lld", &n, &m);
    prepare();
    scanf("%s", s + 1);
    for(int i = 1; i <= n; i++) {
        int a; scanf("%lld", &a);
        c[a]++;
        for(int j = 0; j < a; j++) rm[j]++;
    }
    f[0][0][0] = 1;
    for(int i = 1; i <= n; i++) {
        memset(f[i & 1], 0, sizeof f[i & 1]);
        bool now = s[i] == '1';
        
        for(int j = 0; j < i; j++) if(j <= n - m) {
            for(int k = 0; k < i; k++) {
                if(!f[i & 1 ^ 1][j][k]) continue;

                if(now) f[i & 1][j][k + 1] += f[i & 1 ^ 1][j][k], f[i & 1][j][k + 1] %= mod;

                if(n - rm[j] - i + 1 + k != 0) for(int g = min(k, c[j + 1]); ~g; g--) {
                    f[i & 1][j + 1][k - g] += f[i & 1 ^ 1][j][k] * (n - rm[j] - i + 1 + k) % mod
                        * C[k][g] % mod * P[c[j + 1]][g] % mod;
                    f[i & 1][j + 1][k - g] %= mod;
                }
                if(!now) for(int g = min(k + 1, c[j + 1]); ~g; g--){
                    f[i & 1][j + 1][k + 1 - g] += f[i & 1 ^ 1][j][k] * C[k + 1][g] % mod * P[c[j + 1]][g] % mod;
                    f[i & 1][j + 1][k + 1 - g] %= mod;
                }
            }
        }
    }
    for(int i = 0; i <= n - m; i++) ans += f[n & 1][i][rm[i]] * fac[rm[i]] % mod, ans %= mod;
    printf("%lld", ans);
    return 0;
}
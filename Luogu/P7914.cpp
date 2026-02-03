#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 510, mod = 1e9 + 7;

int n, K;
char s[N];
ll f[N][N], g[N][N], A[N][N], B[N][N];

void pre() {
    for(int i = 1; i <= n; i++) for(int j = i; j <= n; j++) {
        B[i][j] = ((s[i] == '?' | s[i] == '(') & (s[j] == '?' | s[j] == ')'));
        int tmp = 1;
        for(int k = i; k <= j; k++) tmp &= (s[k] == '*' | s[k] == '?');
        A[i][j] = (tmp & (j - i + 1 <= K));
    }
    for(int i = 0; i < n; i++) A[i + 1][i] = 1;
}

int main() {
    scanf("%d%d", &n, &K);
    scanf("%s", s + 1);
    pre();
    for(int len = 2; len <= n; len++) {
        for(int i = 1, j = i + len - 1; j <= n; i++, j++) {
            if(B[i][j] && A[i + 1][j - 1]) f[i][j]++, g[i][j]++;
            ll sum = 0; int pos = 0;
            for(int l = i; l <= j - 1; l++) {
                pos = max(pos, l);
                while(pos <= j - 1 && A[l + 1][pos]) sum += g[pos + 1][j], sum %= mod, pos++;
                g[i][j] += sum * f[i][l] % mod, g[i][j] %= mod;
                sum -= g[l + 1][j], sum = (sum % mod + mod) % mod;
            }
            if(B[i][j]) {
                for(int k = i + 1; k < j - 1; k++) {
                    ll tmp = g[i + 1][k] * A[k + 1][j - 1] % mod + A[i + 1][k] * g[k + 1][j - 1] % mod;
                    tmp %= mod;
                    f[i][j] += tmp, g[i][j] += tmp, f[i][j] %= mod, g[i][j] %= mod;
                }
                f[i][j] += g[i + 1][j - 1], g[i][j] += g[i + 1][j - 1];
                f[i][j] %= mod, g[i][j] %= mod;
            }
        }
    }
    printf("%lld", g[1][n]);
}
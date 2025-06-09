#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 310, mod = 1e9;

char c[N];
int n;
int f[N][N];

signed main() {
    scanf("%s", c + 1);
    n = strlen(c + 1);
    for (int i = 1; i <= n; i++) f[i][i] = 1;

    for (int len = 2; len <= n; len++)
    for (int i = 1; i + len - 1 <= n; i++) {
        int j = i + len - 1;
        if (c[i] == c[j]) {
            for (int k = i + 1; k < j; k++) if (c[k] == c[i])
                f[i][j] += f[i][k] * f[k + 1][j - 1], f[i][j] %= mod;
            
            f[i][j] += f[i + 1][j - 1], f[i][j] %= mod;
        }
    }
    cout << f[1][n] << '\n';
    return 0;
}
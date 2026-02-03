#include <bits/stdc++.h>
using namespace std;

const int N = 310, M = 90100;

int n, m;
int g[N][N][N], f[N][N];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        for(int j = b; j <= c; j++) g[j][b][c] = max(a, g[j][b][c]);
    }
    for(int len = 2; len <= n; len++)
    for(int l = 1, r = l + len - 1; r <= n; l++, r++)
    for(int i = l; i <= r; i++) {
        if(i > l) g[i][l][r] = max(g[i][l][r], g[i][l + 1][r]);
        if(i < r) g[i][l][r] = max(g[i][l][r], g[i][l][r - 1]);
    }
    for(int len = 1; len <= n; len++)
    for(int l = 1, r = l + len - 1; r <= n; l++, r++)
    for(int i = l; i <= r; i++) {
        f[l][r] = max(f[l][r], f[l][i - 1] + f[i + 1][r] + g[i][l][r]);
    }
    printf("%d", f[1][n]);
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

const int N = 2100;

int n, m, w[N];
int f[N][N], F[N][N];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &w[i]);
    f[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        f[i][0] = 1;
        for(int j = 1; j <= m; j++)
            f[i][j] = (f[i - 1][j] + (j >= w[i] ? f[i - 1][j - w[i]] : 0)) % 10;
    }
    for(int i = 1; i <= n; i++) for(int j = 0; j <= m; j++)
        F[i][j] = (f[n][j] - (j >= w[i] ? F[i][j - w[i]] % 10 : 0) + 10) % 10;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) printf("%d", F[i][j]);
        putchar('\n');
    }
    return 0;
}
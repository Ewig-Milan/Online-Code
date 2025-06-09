#include <bits/stdc++.h>
using namespace std;

const int N = 3900;

int f[N][N][2], n, b, u[N], ans;

int main() {
    memset(f, 128, sizeof(f));
    scanf("%d%d", &n, &b);

    for(int i = 1; i <= n; i++) scanf("%d", u + i);

    f[1][1][1] = f[1][0][0] = 0;

    for(int i = 2; i <= n; i++) {
        f[i][0][0] = f[i - 1][0][0];
        for(int j = 1; j <= b; j++) {
            f[i][j][0] = max(f[i - 1][j][0], f[i - 1][j][1]);
            f[i][j][1] = max(f[i - 1][j - 1][0], f[i - 1][j - 1][1] + u[i]);
        }
    }
    ans = max(f[n][b][0], f[n][b][1]);

    memset(f, 128, sizeof(f));
    f[1][1][1] = u[1], f[1][0][0] = 0;

    for(int i = 2; i <= n; i++) {
        f[i][0][0] = f[i - 1][0][0];
        for(int j = 1; j <= b; j++) {
            f[i][j][0] = max(f[i - 1][j][0], f[i - 1][j][1]);
            f[i][j][1] = max(f[i - 1][j - 1][0], f[i - 1][j - 1][1] + u[i]);
        }
    }
    ans = max(ans, f[n][b][1]);
    printf("%d\n", ans);
    return 0;
}
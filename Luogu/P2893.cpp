#include <bits/stdc++.h>
using namespace std;

const int N = 2100;

int a[N], b[N], n, ans;
int f[N][N], mi[N][N];

bool cmp(int a, int b) {return a > b;}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++) {
        mi[i][0] = 1e9;
        for (int j = 1; j <= n; j++) {
            f[i][j] = mi[i - 1][j] + abs(a[i] - b[j]);
            mi[i][j] = min(mi[i][j - 1], f[i][j]);
        }
    }
    ans = mi[n][n];
    memset(mi, 0, sizeof(mi));
    memset(f, 0, sizeof(f));
    sort(b + 1, b + n + 1, cmp);
    for (int i = 1; i <= n; i++) {
        mi[i][0] = 1e9;
        for (int j = 1; j <= n; j++) {
            f[i][j] = mi[i - 1][j] + abs(a[i] - b[j]);
            mi[i][j] = min(mi[i][j - 1], f[i][j]);
        }
    }
    ans = min(ans, mi[n][n]);
    printf("%d\n", ans);
    return 0;
}
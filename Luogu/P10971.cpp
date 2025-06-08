#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 40, M = 5100;

int f[N][M];
int n, m, b[N][M], ans[N];

struct node {int x, id;} e[N];
bool cmp(node x, node y) {return x.x > y.x;}

void print(int x, int y) {
    if (x == 0) return;
    for (int i = 1; i <= x; i++) e[i].x++;
    print(b[x][y], y - x);
}

signed main() {
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &e[i].x), e[i].id = i;

    sort(e + 1, e + n + 1, cmp);
    memset(f, 127, sizeof(f));

    f[0][0] = 0;
    for (int i = 1; i <= n; i++)
    for (int j = 0; j <= m; j++) {
        if (j - i < 0) continue;
        int minn = 1e9;
        for (int k = 0; k <= i; k++) {
            int sum = 0;
            for (int p = k + 1; p <= i; p++) sum += e[p].x;
            if (f[k][j - i] + k * sum < minn) {
                minn = f[k][j - i] + k * sum;
                b[i][j] = k;
            }
            minn = min(minn, f[k][j - (i - k)] + k * sum);
        }
        f[i][j] = (f[i][j - i], minn);
    }
    for (int i = 1; i <= n; i++) e[i].x = 0;
    print(n, m);
    for (int i = 1; i <= n; i++) ans[e[i].id] = e[i].x;
    printf("%lld\n", f[n][m]);
    for (int i = 1; i <= n; i++) printf("%lld ", ans[i]);
    return 0;
}
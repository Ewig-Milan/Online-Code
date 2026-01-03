#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1100, M = 200100;

int n, m;
int f[N][N];
ll ans[M];

void floyd_() {
    for(int i = 1; i <= n; i++) f[i][i] = m + 1;
    for(int k = n; k >= 1; k--)
    for(int i = 1; i < k; i++)
    for(int j = i + 1; j <= n; j++) {
        f[i][j] = max(f[i][j], min(f[i][k], f[k][j]));
        f[j][i] = max(f[j][i], min(f[j][k], f[k][i]));
    }
}

int main() {
    memset(f, -1, sizeof f);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        f[a][b] = i;
    }
    floyd_();
    for(int i = 1; i <= n; i++) for(int j = i; j <= n; j++) {
        if(f[i][j] == -1 || f[j][i] == -1) continue;
        int tmp = min(f[i][j], f[j][i]);
        ans[tmp - 1]++;
    }
    for(int i = m; i >= 0; i--) ans[i] += ans[i + 1];
    for(int i = 0; i <= m; i++) printf("%lld ", ans[i]);
    return 0;
}
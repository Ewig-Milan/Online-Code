#include <bits/stdc++.h>
#define int long long 
using namespace std;

const int N = 3e3 + 5;

int n, m, ans;
int a[N], b[N], f[N][N];

signed main() {
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
    for(int i = 1; i <= n; i++) {
        int ma = 0;
        for(int j = 1; j <= n; j++) {
            if(a[i] != b[j]) f[i][j] = f[i - 1][j];
            else f[i][j] = ma + 1;
            if(b[j] < a[i]) ma = max(ma, f[i - 1][j]);
        }
    }
    for(int i = 1; i <= n; i++) ans = max(ans, f[n][i]);
    printf("%lld\n", ans);
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

const int N = 1000100;

int n, m;
int a[N], c[N], dp[N], g[N];

int main() {
    while(~scanf("%d%d", &n, &m) && n && m) {
        memset(dp, 0, sizeof(dp));
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for(int i = 1; i <= n; i++) scanf("%d", &c[i]);
        dp[0] = 1;
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j <= m; j++) g[j] = 0;
            for(int j = a[i]; j <= m; j++)
                if(!dp[j] && dp[j - a[i]] && g[j - a[i]] < c[i])
                    dp[j] = 1, g[j] = g[j - a[i]] + 1;
        }
        int ans = 0;
        for(int i = 1; i <= m; i++) if(dp[i]) ans++;
        printf("%d\n", ans);
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

const int N = 30;

#define int long long
int f[N][N][2], n, m, T;
bool vis[N];

void pre() {
    f[1][1][1] = f[1][1][0] = 1;
    for(int i = 2; i <= 20; i++)
        for(int j = 1; j <= i; j++) {
            for(int k = 1; k < j; k++) f[i][j][1] += f[i - 1][k][0];
            for(int k = j; k < i; k++) f[i][j][0] += f[i - 1][k][1];
        }
}

signed main() {
    pre();
    scanf("%lld", &T);
    while(T--) {
        scanf("%lld%lld", &n, &m);
        memset(vis, 0, sizeof(vis));
        int last, k;
        for(int i = 1; i <= n; i++) {
            if(f[n][i][1] >= m) {
                last = i, k = 1;
                break;
            } else m -= f[n][i][1];
            if(f[n][i][0] >= m) {
                last = i, k = 0;
                break;
            } else m -= f[n][i][0];
        }
        printf("%lld", last);
        vis[last] = true;
        for(int i = 2; i <= n; i++) {
            k ^= 1;
            int rank = 0;
            for(int len = 1; len <= n; len++) {
                if(vis[len]) continue;
                rank++;
                if((k == 0 && len < last) || (k == 1 && len > last)) {
                    if(f[n - i + 1][rank][k] >= m) {
                        last = len;
                        break;
                    } else m -= f[n - i + 1][rank][k];
                }
            }
            vis[last] = true;
            printf(" %lld", last);
        }
        putchar('\n');
    }
    return 0;
}
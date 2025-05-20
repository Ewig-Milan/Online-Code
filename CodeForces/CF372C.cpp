#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 150100;
const int M = 310;
ll f[2][N];
ll a[M], b[M], t[M];
int n, m, d;

void solve() {
    memset(f, 127, sizeof(f));
    for(int i = 1; i <= n; i++) f[0][i] = 0;
    int tmp = 1;
    for(int i = 1; i <= m; i++) {
        deque<int> q;
        int k = 1;
        for(int j = 1; j <= n; j++) {
            while(k <= min((ll)n, j + d * (t[i] - t[i - 1]))) {
                while(!q.empty() && f[tmp ^ 1][q.back()] <= f[tmp ^ 1][k]) q.pop_back();
                q.push_back(k), k++;
            }
            while(!q.empty() && q.front() < j - d * (t[i] - t[i - 1])) q.pop_front();
            f[tmp][j] = f[tmp ^ 1][q.front()] - abs(a[i] - j) + b[i];
        }
        tmp = !tmp;
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &d);
    for(int i = 1; i <= m; i++) scanf("%lld%lld%lld", &a[i], &b[i], &t[i]);
    solve();
    ll ans = -1e18;
    int tmp = m & 1;
    for(int i = 1; i <= n; i++) ans = max(ans, f[tmp][i]);
    printf("%lld\n", ans);
    return 0;
}
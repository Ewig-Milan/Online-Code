#include <bits/stdc++.h>
using namespace std;

const int N = 600;

int n, k, ans;
bool edg[N][N], vis[N];

int mt[N];
bool match(int x) {
    for(int i = 1; i <= n; i++) {
        if(!edg[x][i] || vis[i]) continue;
        vis[i] = true;
        if(!mt[i] || match(mt[i])) {
            mt[i] = x;
            return true;
        }
    }
    return false;
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= k; i++) {
        int a, b; scanf("%d%d", &a, &b);
        edg[a][b] = true;
    }
    for(int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof vis);
        if(match(i)) ans++;
    }
    printf("%d", ans);
    return 0;
}
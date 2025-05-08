#include <bits/stdc++.h>
#define PI pair<int, int>
#define fi first
#define se second
using namespace std;

const int N = 200;

int n, t, ans;
bool ban[N][N], vis[N][N];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

PI mt[N][N];
bool match(PI x) {
    for(int i = 0; i < 4; i++) {
        int nx = x.fi + dx[i], ny = x.se + dy[i];
        if(nx < 1 || nx > n || ny < 1 || ny > n) continue;
        if(vis[nx][ny] || ban[nx][ny]) continue;
        vis[nx][ny] = true;
        if(!mt[nx][ny].fi || match(mt[nx][ny])) {
            mt[nx][ny] = x;
            return true;
        }
    }
    return false;
}

int main() {
    scanf("%d%d", &n, &t);
    for(int i = 1; i <= t; i++) {
        int a, b; scanf("%d%d", &a, &b);
        ban[a][b] = true;
    }
    for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++) {
        if(ban[i][j] || i + j & 1) continue;
        memset(vis, 0, sizeof vis);
        if(match({i, j})) ans++;
    }
    printf("%d", ans);
    return 0;
}
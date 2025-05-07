#include <bits/stdc++.h>
#define PI pair<int, int>
#define fi first
#define se second
using namespace std;
const int N = 200;

int n, m, t, ans;
bool ban[N][N], vis[N][N];
int dx[8]/*行数*/ = {-2, -2, -1, 1, 2, 2, 1, -1},
    dy[8]/*列数*/ = {-1, 1, 2, 2, 1, -1, -2, -2};

PI mt[N][N];
bool match(PI x) {
    for(int i = 0; i < 8; i++) {
        int nx = x.fi + dx[i], ny = x.se + dy[i];
        if(nx < 1 || nx > n || ny < 1 || ny > m) continue;
        if(ban[nx][ny] || vis[nx][ny]) continue;
        vis[nx][ny] = true;
        if(!mt[nx][ny].fi || match(mt[nx][ny])) {
            mt[nx][ny] = x;
            return true;
        }
    }
    return false;
}

int main() {
    scanf("%d%d%d", &n, &m, &t);
    for(int i = 1; i <= t; i++) {
        int a, b; scanf("%d%d", &a, &b);
        ban[a][b] = true;
    }
    for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++) {
        if(ban[i][j] || i + j & 1) continue;
        memset(vis, 0, sizeof vis);
        if(match({i, j})) ans++;
    }
    printf("%d", n * m - ans - t);
    return 0;
}
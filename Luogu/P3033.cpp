#include <bits/stdc++.h>
using namespace std;

const int N = 300;

int n, cnt_x/*与x轴平行*/, cnt_y, ans;
bool edg[N][N];

struct Line {
    int x, y, X, Y;//前小后大
}L[N][2];//0横1竖

bool intersect(Line a/*横*/, Line b/*竖*/) {
    if(a.y < b.y || a.y > b.Y) return false;
    if(b.x < a.x || b.x > a.X) return false;
    return true;
}

int mt[N];
bool vis[N];
bool match(int x) {
    for(int i = 1; i <= cnt_y; i++) {
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
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        int x, y, X, Y; scanf("%d%d%d%d", &x, &y, &X, &Y);
        if(x > X || y > Y) swap(x, X), swap(y, Y);
        if(y == Y) L[++cnt_x][0] = {x, y, X, Y};
        else L[++cnt_y][1] = {x, y, X, Y};
    }
    for(int i = 1; i <= cnt_x; i++)
    for(int j = 1; j <= cnt_y; j++)
        if(intersect(L[i][0], L[j][1])) edg[i][j] = true;

    for(int i = 1; i <= cnt_x; i++) {
        memset(vis, 0, sizeof vis);
        if(match(i)) ans++;
    }
    printf("%d", n - ans);
    return 0;
}
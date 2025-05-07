#include <bits/stdc++.h>
using namespace std;

int f[9][310][310];
int n, m, ans;

int main() {
    scanf("%d%d", &n, &m);
    memset(f, 0x3f, sizeof(f));
    for(int i = 1; i <= n; i++) f[0][i][i] = 0;
    for(int i = 1; i <= m; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        f[0][a][b] = c;
    }
    for(int i = 1; i <= 8; i++) {
        for(int a = 1; a <= n; a++)
        for(int b = 1; b <= n; b++)
        for(int c = 1; c <= n; c++)
            f[i][a][c] = min(f[i][a][c], f[i - 1][a][b] + f[i - 1][b][c]);
    }
    int now[310][310], last[310][310];
    bool tot = false;
    memset(last, 0x3f, sizeof(last));
    for(int i = 1; i <= n; i++) last[i][i] = 0;
    for(int i = 8; i >= 0; i--) {
        memset(now, 0x3f, sizeof(now));
        for(int a = 1; a <= n; a++)
        for(int b = 1; b <= n; b++)
        for(int c = 1; c <= n; c++)
            now[a][c] = min(now[a][c], f[i][a][b] + last[b][c]);
        bool flag = false;
        for(int j = 1; j <= n; j++) if(now[j][j] < 0) flag = true, tot = true;
        if(!flag) {
            ans += 1 << i;
            memcpy(last, now, sizeof(last));
        }
    }
    if(tot) printf("%d", ans + 1);
    else printf("0");
    return 0;
}
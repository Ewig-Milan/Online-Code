#include <bits/stdc++.h>
using namespace std;

const int N = 16;

int n, m, k, a[N][N], f[N][N * N][N][N][2][2];

struct Node {
    int i, j, l, r, x, y;
} pre[N][N * N][N][N][2][2], st;

void print(Node st) {
    if(st.j == 0)
        return;
    print(pre[st.i][st.j][st.l][st.r][st.x][st.y]);
    for(int j = st.l; j <= st.r; j++)
        printf("%d %d\n", st.i, j);
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++)
        scanf("%d", &a[i][j]);

    for(int i = 1; i <= n; i++)
    for(int j = 1; j <= k; j++)
    for(int l = 1; l <= m; l++)
    for(int r = l; r <= m; r++) {
        int val = 0, add = 0;
        for(int p = l; p <= r; p++) val += a[i][p];
        if(j < r - l + 1) continue;
        for(int p = l; p <= r; p++)
        for(int q = p; q <= r; q++) {                
            int t = f[i - 1][j -(r - l + 1)][p][q][1][0];
            if(t > add)
                add = t, pre[i][j][l][r][1][0] = {i - 1, j -(r - l + 1), p, q, 1, 0};
        }
        f[i][j][l][r][1][0] = val + add;
        add = 0;
        for(int p = l; p <= r; p++)
        for(int q = r; q <= m; q++)
        for(int y = 0; y <= 1; y++) {
            int t = f[i - 1][j -(r - l + 1)][p][q][1][y];
            if(t > add)
            add = t, pre[i][j][l][r][1][1] = {i - 1, j -(r - l + 1), p, q, 1, y};
        }
        f[i][j][l][r][1][1] = val + add;
        add = 0;
        for(int p = 1; p <= l; p++) 
        for(int q = l; q <= r; q++)
        for(int x = 0; x <= 1; x++) {
            int t = f[i - 1][j -(r - l + 1)][p][q][x][0];
            if(t > add)
                add = t, pre[i][j][l][r][0][0] = {i - 1, j -(r - l + 1), p, q, x, 0};
        }
        f[i][j][l][r][0][0] = val + add;
        add = 0;
        for(int p = 1; p <= l; p++)
        for(int q = r; q <= m; q++)
        for(int x = 0; x <= 1; x++)
        for(int y = 0; y <= 1; y++) {
            int t = f[i - 1][j -(r - l + 1)][p][q][x][y];
            if(t > add)
                add = t, pre[i][j][l][r][0][1] = {i - 1, j -(r - l + 1), p, q, x, y};
        }
        f[i][j][l][r][0][1] = val + add;
    }
    int ans = 0;
    for(int i = 1; i <= n; i++)
    for(int l = 1; l <= m; l++)
    for(int r = l; r <= m; r++)
    for(int x = 0; x <= 1; x++)
    for(int y = 0; y <= 1; y++) {
        int t = f[i][k][l][r][x][y];
        if(t > ans)
        ans = t, st = {i, k, l, r, x, y};
    }
    printf("Oil : %d\n", ans);
    print(st);
    return 0;
}
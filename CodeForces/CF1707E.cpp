#include <bits/stdc++.h>
using namespace std;

const int N = 100100;

int stmi[20][20][N], stma[20][20][N];
//st[i][j][k] 从k开始的2^j个数做2^i次得到的最大/小值

int n, q;

int get_mi(int times, int l, int r) {//传入 l~r 做2^times次
    for(int k = 19; k >= 0; k--)
        if(1 << k <= r - l + 1)
            return min(stmi[times][k][l], stmi[times][k][r - (1 << k) + 1]);
    return 0;
}

int get_ma(int times, int l, int r) {//传入 l~r 做2^times次
    for(int k = 19; k >= 0; k--)
        if(1 << k <= r - l + 1)
            return max(stma[times][k][l], stma[times][k][r - (1 << k) + 1]);
    return 0;
}

int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) {
        int a; scanf("%d", &a);
        stmi[0][0][i] = stma[0][0][i] = a;
    }
    for(int i = 1; i <= 19; i++)
        for(int j = 1; j + (1 << i) - 1 <= n; j++) {
            stmi[0][i][j] = min(stmi[0][i - 1][j], stmi[0][i - 1][j + (1 << (i - 1))]);
            stma[0][i][j] = max(stma[0][i - 1][j], stma[0][i - 1][j + (1 << (i - 1))]);
        }

    for(int i = 1; i <= 19; i++)
        for(int j = 0; j <= 19; j++)
            for(int k = 1; k + (1 << j) - 1 <= n; k++) {
                stmi[i][j][k] = get_mi(i - 1, stmi[i - 1][j][k], stma[i - 1][j][k]);
                stma[i][j][k] = get_ma(i - 1, stmi[i - 1][j][k], stma[i - 1][j][k]);
            }
    
    while(q--) {
        int l, r; scanf("%d%d", &l, &r);
        if(l == 1 && r == n) {
            printf("0\n");
            continue;
        }
        int ans = 1;
        for(int i = 19; i >= 0; i--) {
            int tl = get_mi(i, l, r), tr = get_ma(i, l, r);
            if(tl != 1 || tr != n) l = tl, r = tr, ans += 1 << i;
        }
        if(get_mi(0, l, r) != 1 || get_ma(0, l, r) != n) ans = -1;
        printf("%d\n", ans);
    }
    return 0;
}
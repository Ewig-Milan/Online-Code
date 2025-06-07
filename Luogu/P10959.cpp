#include <bits/stdc++.h>
using namespace std;

int l, r;
int f[12][90][90][90], s[90][10], num[12];

int val(int pos, int sum, int mod, int x, bool flag) {
    if(x < sum) return 0;
    if(!flag) return f[pos + 1][x][x - sum][(x - mod) % x];
    if(pos == -1) return (mod == 0 && sum == x);
    int tmp = 0;
    for(int d = 0; d <= num[pos]; d++)
        tmp += val(pos - 1, sum + d, (mod + s[x][pos] * d) % x, x, d == num[pos]);
    return tmp;
}

int work(int x) {
    int p = 0, tmp = 0;
    while(x) num[p++] = x % 10, x /= 10;
    for(int i = 1; i <= 81; i++) tmp += val(p - 1, 0, 0, i, true);
    return tmp;
}

void pre() {
    for(int i = 1; i <= 81; i++) {
        memset(f[0][i], 0, sizeof(f[0][i]));
        f[0][i][0][0] = 1, s[i][0] = 1 % i;
        for(int j = 1; j <= 9; j++) s[i][j] = (s[i][j - 1] * 10) % i;
        for(int j = 1; j <= 9; j++)
        for(int k = 0; k <= j * 9; k++)
        for(int p = 0; p <= i; p++)
        for(int q = 0; q <= 9 && k >= q; q++)
            f[j][i][k][p] += f[j - 1][i][k - q][((p - s[i][j - 1] * q) % i + i) % i];
    }
}

int main() {
    pre();
    while(~scanf("%d%d", &l, &r)) printf("%d\n", work(r) - work(l - 1));
    return 0;
}

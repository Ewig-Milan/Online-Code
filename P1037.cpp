#include <bits/stdc++.h>
#define LL __int128
using namespace std;

const int N = 20;

char c[40];
int n, k;
LL ans = 1LL;
int d[N][N], chose[N];
bool chose0[N];

void floyd() {
    for(int k = 0; k <= 9; k++)
    for(int i = 0; i <= 9; i++)
    for(int j = 0; j <= 9; j++)
        d[i][j] |= d[i][k] & d[k][j];
}

void print(LL x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int main() {
    scanf("%s %d", c + 1, &k);
    n = strlen(c + 1);
    for(int i = 0; i <= 9; i++) d[i][i] = 1;
    for(int i = 1; i <= k; i++) {
        int a, b; scanf("%d%d", &a, &b);
        d[a][b] = 1;
    }
    floyd();
    for(int i = 0; i <= 9; i++) {
        if(d[i][0]) chose0[i] = 1, chose[i]++;;
        for(int j = 1; j <= 9; j++) if(d[i][j]) chose[i]++;
    }
    ans = chose[c[1] - '0'] - chose0[c[1] - '0'];
    for(int i = 2; i <= n; i++) ans *= (LL)chose[c[i] - '0'];
    print(ans);
    return 0;
}
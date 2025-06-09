#include <bits/stdc++.h>
using namespace std;

const int N = 2100;

int n;
int a[N], sum[N];
int f1[N][N], f2[N][N], s[N][N];

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        a[i + n] = a[i], s[i][i] = i;
        sum[i] = sum[i - 1] + a[i];
    }
    for(int i = 1 + n; i <= (n << 1); i++)
        sum[i] = sum[i - 1] + a[i], s[i][i] = i;

    for(int i = (n << 1) - 1; i; i--)
    for(int j = i + 1; j <= (n << 1); j++) {
        int jc = 0, tmp = 1e9;
        f2[i][j] = max(f2[i][j - 1], f2[i + 1][j]) + sum[j] - sum[i - 1];
        for(int k = s[i][j - 1]; k <= s[i + 1][j]; k++)
        {
            int tt = f1[i][k] + f1[k + 1][j] + sum[j] - sum[i - 1];
            if(tt < tmp) tmp = tt, jc = k;
        }
        s[i][j] = jc, f1[i][j] = tmp;
    }
    int tma = 0, tmi = 0x3f3f3f3f;
    for(int i = 1; i <= n; i++) {
        tma = max(tma, f2[i][i + n - 1]);
        tmi = min(tmi, f1[i][i + n - 1]);
    }
    printf("%d\n%d", tmi, tma);
    return 0;
}
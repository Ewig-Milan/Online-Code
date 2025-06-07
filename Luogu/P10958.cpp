#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll f[30][4];
int T, n;

void pre() {
    f[0][0] = 1;
    for(int i = 1; i < 20; i++) {
        f[i][0] = 9 * (f[i - 1][0] + f[i - 1][1] + f[i - 1][2]);
        f[i][1] = f[i - 1][0], f[i][2] = f[i - 1][1];
        f[i][3] = 10 * f[i - 1][3] + f[i - 1][2];
    }
}

int main() {
    pre();
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        int tmp = 3;
        while(f[tmp][3] < n) tmp++;
        for(int i = tmp, k = 0; i; i--) for(int j = 0; j <= 9; j++) {
            ll cnt = f[i - 1][3];
            if(j == 6 || k == 3)
                for(int t = max(3 - k - (j == 6), 0); t < 3; t++)
                    cnt += f[i - 1][t];
            if(cnt < n) n -= cnt;
            else {
                if(k < 3) {
                    if(j == 6) k++;
                    else k = 0;
                }
                printf("%d", j);
                break;
            }
        }
        putchar('\n');
    }
    return 0;
}
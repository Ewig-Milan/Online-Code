#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 13;
const ll mod = 1e9 + 7;

int n, m;
ll f[110][1 << N];

int main() {
    while(~scanf("%d%d", &n, &m) && n && m) {
        if(n > m) swap(n, m);
        memset(f, 0, sizeof f);
        f[0][0] = 1;
        for(int i = 1; i <= m; i++) {
            for(int s1 = 0; s1 < (1 << n); s1++) // 上行 
            for(int s2 = 0; s2 < (1 << n); s2++)  { // 本行 
                if(s1 & s2) continue;
                int tmp = s1 | s2, cnt = 0;
                for(int j = 0; j < n; j++) {
                    if((tmp >> j) & 1) {
                        if(cnt & 1) break;
                        cnt = 0;
                    } else cnt++;
                }
                if(cnt & 1) continue;
                f[i][s2] += f[i - 1][s1], f[i][s2] %= mod;
            }
        }
        printf("%lld\n", f[m][0]);
    }
    return 0;
}